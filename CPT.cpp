/*
 * CPT.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: zhemin
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

#include "CPT.h"

using namespace std;

Item::Item(int pos, int col, int value){
	m_iPos = pos;
	m_iCol = col;
	m_iVal = value;
}

string Item::toString(){
	char buffer [50];
	int size = sprintf(buffer, "%d %d %d", m_iPos, m_iCol, m_iVal);
	MyString str(buffer, buffer + size, true);
	return str.getString();
}

Feature::Feature(){
	m_items = new MyVector<Item>;
}

void Feature::addItem(Item* pit){
	m_items->push_back(pit);
}

string Feature::toString(){
	int itemNum = m_items->length();
	string str;
	for(int i = 0; i < itemNum; ++ i){
		Item* pItem = m_items->getItem(i);
		str += pItem->toString() + "|";
	}
	return str;
}

void Feature::setIndex(int index){
	m_index = index;
}

int Feature::getIndex(){
	return m_index;
}

Feature::~Feature(){
	delete m_items;
}

CPT::CPT() {
	m_sumCNT = 0;
	m_sumProb = 0.0;
	m_mapTagProb = NULL;
}

void CPT::addFeature(int fe){
	m_features.push_back(fe);
}

void CPT::addProb(int tag, double prob){
	if(m_mapTagProb == NULL)
		m_mapTagProb = new std::tr1::unordered_map <int, double>;
	/*if(prob < 0.0)
		prob = 0.0;*/
	std::pair<int,double> newTagProb (tag,prob);
	m_mapTagProb->insert(newTagProb);
	m_sumProb += prob;
	m_tags.push_back(tag);
}

void CPT::normalizeProb(){
	for(int i : m_tags){
		auto it = m_mapTagProb->find(i);
		double prob = it->second;
		it->second = prob / m_sumProb;
	}
}

void CPT::sortFeatures(){
	std::sort (m_features.begin(), m_features.end());
}

void CPT::printProbs(Indices* pInd, bool bBigram){
	cout << "#feature: " << m_features.size() << endl << std::flush;
	if(!bBigram){
		MyString str;
		for(int fe : m_features){
			char buff[64];
			sprintf(buff, "%d ", fe);
			str.join(buff);
		}
		str.join("\n");
		for(int tag : m_tags){
			double prob = getProb(tag);
			char buff[16];
			sprintf(buff, "%d:%f\n", tag, prob);
			str.join(buff);
		}
		str.println();
	}else{
		MyString str;
		for(int fe : m_features){
			char buff[64];
			sprintf(buff, "%d ", fe);
			str.join(buff);
		}
		str.join("\n");
		for(int tag : m_tags){
			string strTag = pInd->getStringBiTag(tag);
			double prob = getProb(tag);
			char buff[16];
			sprintf(buff, "%s:%f\n", strTag.c_str(), prob);
			str.join(buff);
		}
		str.println();
	}
}

string CPT::toString(){
	MyString str;
	int feNum = m_features.size();
	for(int i = 0; i < feNum; ++ i){
		MyString strFe(m_features[i]);
		str.join(&strFe);
		str.join(":");
	}
	return str.getString();
}

double CPT::getProb(int tag){
	if(m_mapTagProb != NULL){
		int size = m_tags.size();
		auto it = m_mapTagProb->find(tag);
		if(it != m_mapTagProb->end()){ //found
			if(it->second <= 0.0)
				return 0.000001;
			return it->second;
		}else{// not found
			return 0.000001;
		}
	}else{
		std::tr1::unordered_map <int, int>::const_iterator iter = m_mapTagCNT.find(tag);
		if(iter != m_mapTagCNT.end()){ //found
			return iter->second * 1.0 / m_sumCNT;
		}else{//not found
			return 0.000001;
		}
	}
}

int CPT::getFeatureNum(){
	return m_features.size();
}

int CPT::getFeature(int i){
	return m_features[i];
}

void CPT::addTag(int tag){
	++ m_sumCNT;
	std::tr1::unordered_map <int, int>::const_iterator iter = m_mapTagCNT.find(tag);
	if(iter == m_mapTagCNT.end()){ //not found
		std::pair<int, int> newPair (tag, 1);
		m_mapTagCNT.insert(newPair);
		m_tags.push_back(tag);
	}else{ //found
		m_mapTagCNT[tag] = iter->second + 1;
	}
}

CPT::~CPT() {
	if(m_mapTagProb != NULL)
		delete m_mapTagProb;
}

void CPT::print(){
	MyString strPrint;
	for(int fe : m_features){
		MyString strFe(fe);
		strPrint.join(&strFe);
		strPrint.join("\t");
	}
	strPrint.join("\n");
	for(int tag : m_tags){
		MyString strTag(tag);
		strPrint.join(&strTag);
		strPrint.join(":");
		MyString strProb(getProb(tag));
		strPrint.join(&strProb);
		strPrint.join("\n");
	}
	strPrint.print();
}

vector<int>* CPT::getPromisingTags(){
	return &m_tags;
}

CPTConstuctor::CPTConstuctor(
		IndexedCorpus* pCorpus,
		Template* pTemplate,
		Indices* pIndices,
		bool bCR)
{
	m_bCR = bCR;
	m_vecUnigramCPTs = new MyVector<CPT>;
	constructUnigramCPTs(pCorpus, pTemplate, pIndices);
	if(!bCR){
		m_vecBigramCPTs = new MyVector<CPT>;
		constructBigramCPTs(pCorpus, pTemplate, pIndices);
	}else{
		m_vecCRs = new MyVector<CR>;
		constructCRs(pCorpus, pTemplate, pIndices);
	}
}

void CPTConstuctor::constructUnigramCPTs(IndexedCorpus* pCorpus, Template* pTemplate, Indices* pIndices){
	cout << "Constructing Unigram CPTs:  " << pCorpus->getCorpusFile() << endl << std::flush;
	int uniTagNum = pIndices->getUnigramTagNum();
	for(int i = 0; i < uniTagNum; ++ i)
		m_uniTagCNT.push_back(0);
	m_uniTagSum = 0;

	std::tr1::unordered_map <string, CPT*>* map = new std::tr1::unordered_map <string, CPT*>;
	int sentenceNum = pCorpus->getSentenceNum();
	for(int i = 0; i < sentenceNum; ++ i){
		IndexedSentence* pIS = pCorpus->getSentence(i);
		int tokenNum = pIS->getTokenNum();
		for(int j = 0; j < tokenNum; ++ j){
			IndexedToken* pToken = pIS->getToken(j);
			int uniTag = pToken->getTag();
			m_uniTagCNT[uniTag] = m_uniTagCNT[uniTag] + 1;
			++ m_uniTagSum;
			CPT* pCPT = pTemplate->extractUnigramCPT(pIS, j, pIndices);
			//pCPT->sortFeatures();
			string key = pCPT->toString();
			std::tr1::unordered_map <string, CPT*>::const_iterator iter = map->find(key);
			if(iter == map->end()){ //not found
				std::pair<string, CPT*> newCPT (key, pCPT);
				map->insert(newCPT);
				pCPT->addTag(pToken->getTag());
			}else{//found
				iter->second->addTag(pToken->getTag());
				delete pCPT;
			}

		}

	}

	for(auto kv : *map)
		m_vecUnigramCPTs->push_back(kv.second);

	m_mapUnigramCPTs = map;


	cout << "Constructing Unigram CPTs finished!\n" << std::flush;
	cout << "#Unigram CPTs:\t" << m_vecUnigramCPTs->length() << endl << std::flush;
	cout << "#Unigram Features:\t" << pIndices->getUnigramFeatureNum() << endl << endl << std::flush;
}


void CPTConstuctor::constructBigramCPTs(IndexedCorpus* pCorpus, Template* pTemplate, Indices* pIndices){
	cout << "Constructing Bigram CPTs:  " << pCorpus->getCorpusFile() << endl << std::flush;
	int biTagNum = pIndices->getBigramTagNum();
	for(int i = 0; i < biTagNum; ++ i)
		m_biTagCNT.push_back(0);
	m_biTagSum = 0;

	std::tr1::unordered_map <string, CPT*>* map = new std::tr1::unordered_map <string, CPT*>;
	int sentenceNum = pCorpus->getSentenceNum();
	for(int i = 0; i < sentenceNum; ++ i){
		IndexedSentence* pIS = pCorpus->getSentence(i);
		int tokenNum = pIS->getTokenNum();
		for(int j = 1; j < tokenNum; ++ j){
			IndexedToken* pPreToken = pIS->getToken(j - 1);
			IndexedToken* pCurToken = pIS->getToken(j);
			string strBitag = BiTag::mergeTag(pPreToken->getTag(), pCurToken->getTag());
			int bitag = pIndices->getIntBiTag(strBitag);
			m_biTagCNT[bitag] = m_biTagCNT[bitag] + 1;
			++ m_biTagSum;

			CPT* pCPT = pTemplate->extractBigramCPT(pIS, j, pIndices);
			//pCPT->sortFeatures();
			string key = pCPT->toString();

			std::tr1::unordered_map <string, CPT*>::const_iterator iter = map->find(key);
			if(iter == map->end()){ //not found
				std::pair<string, CPT*> newCPT (key, pCPT);
				map->insert(newCPT);
				pCPT->addTag(bitag);
			}else{//found
				iter->second->addTag(bitag);
				delete pCPT;
			}
		}

	}

	for(auto kv : *map)
		m_vecBigramCPTs->push_back(kv.second);

	m_mapBigramCPTs = map;
	cout << "Constructing Bigram CPTs finished!\n" << std::flush;
	cout << "#Bigram CPTs:\t" << m_vecBigramCPTs->length() << endl << std::flush;
	cout << "#Bigram Features:\t" << pIndices->getBigramFeatureNum() << endl << endl << std::flush;
	cout << "#Total Features:\t" << pIndices->getUnigramFeatureNum() + pIndices->getBigramFeatureNum()
			<< endl << endl << std::flush;
}

void CPTConstuctor::constructCRs(IndexedCorpus* pCorpus, Template* pTemplate, Indices* pIndices){
	cout << "Constructing CRs:  " << pCorpus->getCorpusFile() << endl << std::flush;

	std::tr1::unordered_map <string, CR*>* map = new std::tr1::unordered_map <string, CR*>;
	int sentenceNum = pCorpus->getSentenceNum();
	for(int i = 0; i < sentenceNum; ++ i){
		IndexedSentence* pIS = pCorpus->getSentence(i);
		int tokenNum = pIS->getTokenNum();
		for(int j = 1; j < tokenNum; ++ j){
			IndexedToken* pPreToken = pIS->getToken(j - 1);
			IndexedToken* pCurToken = pIS->getToken(j);
			string strBitag = BiTag::mergeTag(pPreToken->getTag(), pCurToken->getTag());
			int bitag = pIndices->getIntBiTag(strBitag);

			CR* pCR = pTemplate->extractCR(pIS, j, pIndices);
			//pCPT->sortFeatures();
			string key = pCR->toString();

			auto iter = map->find(key);
			if(iter == map->end()){ //not found
				map->insert(make_pair(key, pCR));
				pCR->addTag(bitag);
				CPT* pCPT1 = pTemplate->extractUnigramCPT(pIS, j-1, pIndices);
				CPT* pCPT2 = pTemplate->extractUnigramCPT(pIS, j, pIndices);
				pCR->setCPT1(m_mapUnigramCPTs->find(pCPT1->toString())->second);
				pCR->setCPT2(m_mapUnigramCPTs->find(pCPT2->toString())->second);
			}else{//found
				iter->second->addTag(bitag);
				delete pCR;
			}
		}

	}

	for(auto kv : *map)
		m_vecCRs->push_back(kv.second);

	m_mapCRs = map;
	cout << "Constructing CRs finished!\n" << std::flush;
	cout << "#CR:\t" << m_vecCRs->length() << endl << std::flush;
	cout << "#Bigram Features:\t" << pIndices->getBigramFeatureNum() << endl << endl << std::flush;
	cout << "#Total Features:\t" << pIndices->getUnigramFeatureNum() + pIndices->getBigramFeatureNum()
			<< endl << endl << std::flush;
}

MyVector<CPT>* CPTConstuctor::getUnigramCPTs(){
	return m_vecUnigramCPTs;
}

MyVector<CPT>* CPTConstuctor::getBigramCPTs(){
	return m_vecBigramCPTs;
}

MyVector<CR>* CPTConstuctor::getCRs(){
	return m_vecCRs;
}

double CPTConstuctor::getUniTagEmpProb(int tag){
	return m_uniTagCNT[tag] * 1.0 / m_uniTagSum;
}

double CPTConstuctor::getBiTagEmpProb(int tag){
	return m_biTagCNT[tag] * 1.0 / m_biTagSum;
}

CPT* CPTConstuctor::getUnigramCPT(CPT* pCPT){
	string key = pCPT->toString();
	std::tr1::unordered_map <string, CPT*>::const_iterator iter = m_mapUnigramCPTs->find(key);
	if(iter == m_mapUnigramCPTs->end()){ //not found
		return NULL;
	}else{//found
		return iter->second;
	}
}

void CPTConstuctor::insertUnigramCPT(CPT* pCPT){
	m_mapUnigramCPTs->insert(make_pair(pCPT->toString(), pCPT));
}

void CPTConstuctor::insertBigramCPT(CPT* pCPT){
	m_mapBigramCPTs->insert(make_pair(pCPT->toString(), pCPT));
}

void CPTConstuctor::insertCR(CR* pCR){
	m_mapCRs->insert(make_pair(pCR->toString(), pCR));
}

CPT* CPTConstuctor::getBigramCPT(CPT* pCPT){
	string key = pCPT->toString();
	std::tr1::unordered_map <string, CPT*>::const_iterator iter = m_mapBigramCPTs->find(key);
	if(iter == m_mapUnigramCPTs->end()){ //not found
		return NULL;
	}else{//found
		return iter->second;
	}
}

CR* CPTConstuctor::getCR(CR* pCR){
	string key = pCR->toString();
	auto iter = m_mapCRs->find(key);
	if(iter == m_mapCRs->end()){ //not found
		return NULL;
	}else{//found
		return iter->second;
	}
}

CPTConstuctor::~CPTConstuctor(){
	delete m_vecUnigramCPTs;
	delete m_mapUnigramCPTs;
	if(!m_bCR){
		delete m_vecBigramCPTs;
		delete m_mapBigramCPTs;
	}else{
		delete m_vecCRs;
		delete m_mapCRs;
	}
}
