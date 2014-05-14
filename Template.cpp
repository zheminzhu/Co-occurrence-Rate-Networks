/*
 * Template.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: zhemin
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "Template.h"

using namespace std;

//example: -1:0
ItemTemplate::ItemTemplate(MyString* pStr){
	MyVector<MyString>* pStrs = pStr->split(':');
	if(pStrs->length() != 2){
		MyGlobal::printError("Error in template file: ItemTemplate::ItemTemplate(MyString* pStr).");
		exit(1);
	}
	m_iPos = atoi(pStrs->getItem(0)->getCString());
	m_iCol = atoi(pStrs->getItem(1)->getCString());
}

MyString* ItemTemplate::toString(){
	char buffer [50];
	int n = sprintf (buffer, "%d:%d", m_iPos, m_iCol);
	MyString* pStr = new MyString(buffer, buffer + n, true);
	return pStr;
}

void ItemTemplate::print(){
	MyString* pStr = toString();
	pStr->print();
	delete pStr;
}

Item* ItemTemplate::extractItem(IndexedSentence* pIS, int currPos){
	int upperLimit = pIS->getTokenNum() - 1;
	int tokenPos = currPos + m_iPos;
	if(tokenPos > upperLimit || tokenPos < 0)
		return 0;
	IndexedToken* pToken = pIS->getToken(tokenPos);
	int value = pToken->getCol(m_iCol);
	Item* pItem = new Item(m_iPos, m_iCol, value);
	return pItem;
}

FeatureTemplate::FeatureTemplate(MyString* pLine){
	m_vecIT = new MyVector<ItemTemplate>;
	MyVector<MyString>* pItems = pLine->splitBySpace();
	int size = pItems->length();
	m_ID = new MyString(pItems->getItem(0));
	if(m_ID->getChar(0) == 'U'){
		m_bUnigram = true;
	}else{
		m_bUnigram = false;
	}

	for(int i = 1; i < size; ++ i){
		MyString* pStr = pItems->getItem(i);
		ItemTemplate* pItemTemplate = new ItemTemplate(pStr);
		m_vecIT->push_back(pItemTemplate);
	}

	delete pItems;
}

int FeatureTemplate::getItemTemplateNum(){
	return m_vecIT->length();
}

Feature* FeatureTemplate::extractFeature(IndexedSentence* pIS, int pos){
	int itNum = getItemTemplateNum();
	Feature* fe = new Feature;
	for(int i = 0; i < itNum; ++ i){
		ItemTemplate* pIt = m_vecIT->getItem(i);
		Item* pItem = pIt->extractItem(pIS, pos);
		fe->addItem(pItem);
	}
	return fe;
}

FeatureTemplate::~FeatureTemplate(){
	delete m_vecIT;
	delete m_ID;
}

MyString* FeatureTemplate::toString(){
	MyString* myStr = new MyString();
	myStr->join(m_ID);
	for(int i = 0; i < m_vecIT->length(); ++ i){
		MyString* pItem = m_vecIT->getItem(i)->toString();
		myStr->join("\t");
		myStr->join(pItem);
	}

	return myStr;
}

void FeatureTemplate::print(){
	MyString* theString = toString();
	theString->println();
	delete theString;
}

Template::Template(const char* pTemplateFilePath){
	cout << "Reading the template file: " << pTemplateFilePath << endl << std::flush;

	MyString* fileBuffer = MyFile::readFile(pTemplateFilePath);
	MyVector<MyString>* pVecLines = fileBuffer->split('\n');
	m_vecUnigramFT = new MyVector<FeatureTemplate>;
	m_vecBigramFT = new MyVector<FeatureTemplate>;
	for(int i = 0; i < pVecLines->length(); ++ i){
		MyString* pLine = pVecLines->getItem(i);
		char ch0 = pLine->getChar(0);
		if(ch0 == 'U'){
			FeatureTemplate* ft = new FeatureTemplate(pLine);
			m_vecUnigramFT->push_back(ft);
		}else if(ch0 == 'B'){
			FeatureTemplate* ft = new FeatureTemplate(pLine);
			m_vecBigramFT->push_back(ft);
		}
	}
	delete fileBuffer;
	delete pVecLines;
	cout << "Reading the template file finished!\n\n" << std::flush;
}

Template::~Template(){
	delete m_vecUnigramFT;
	delete m_vecBigramFT;
}

MyString* Template::toString(){
	MyString* theStr = new MyString();
	for(int i = 0; i < m_vecUnigramFT->length(); ++ i){
		MyString* pLine = m_vecUnigramFT->getItem(i)->toString();
		theStr->join(pLine);
		theStr->join("\n");
		delete pLine;
	}

	for(int i = 0; i < m_vecBigramFT->length(); ++ i){
		MyString* pLine = m_vecBigramFT->getItem(i)->toString();
		theStr->join("\n");
		theStr->join(pLine);
		delete pLine;
	}

	return theStr;
}

void Template::print(){
	MyString* p = toString();
	p->println();

}

CPT* Template::extractUnigramCPT(IndexedSentence* pIS, int pos, Indices* ind)
{
	std::tr1::unordered_map<string, Feature*>* mapUnigramFeature = ind->m_mapUnigramFeature;
	MyVector<Feature>* vecUnigramFeatures = ind->m_vecUnigramFeatures;
	CPT* pCPT = new CPT;
	int feNum = m_vecUnigramFT->length();
	for(int i = 0; i < feNum; ++ i){
		FeatureTemplate* ft = m_vecUnigramFT->getItem(i);
		Feature* pFe = ft->extractFeature(pIS, pos);
		string strFe = pFe->toString();
		int feIndex;

		std::tr1::unordered_map <string, Feature*>::const_iterator iter = mapUnigramFeature->find(strFe);

		if(iter == mapUnigramFeature->end()){ //not found
			std::pair<string, Feature*> newFeature (strFe, pFe);
			mapUnigramFeature->insert(newFeature);
			pFe->setIndex(vecUnigramFeatures->length());
			vecUnigramFeatures->push_back(pFe);
			feIndex = pFe->getIndex();
		}else{//found
			feIndex = iter->second->getIndex();
			delete pFe;
		}

		pCPT->addFeature(feIndex);
	}
	return pCPT;
}

CPT* Template::extractBigramCPT(IndexedSentence* pIS, int pos, Indices* ind)
{

	std::tr1::unordered_map<string, Feature*>* mapBigramFeature = ind->m_mapBigramFeature;
	MyVector<Feature>* vecBigramFeatures = ind->m_vecBigramFeatures;

	CPT* pCPT = new CPT;
	int feNum = m_vecBigramFT->length();
	for(int i = 0; i < feNum; ++ i){
		FeatureTemplate* ft = m_vecBigramFT->getItem(i);
		Feature* pFe = ft->extractFeature(pIS, pos);
		string strFe = pFe->toString();
		int feIndex;
		std::tr1::unordered_map <string, Feature*>::const_iterator iter = mapBigramFeature->find(strFe);
		if(iter == mapBigramFeature->end()){ //not found
			std::pair<string, Feature*> newFeature (strFe, pFe);
			mapBigramFeature->insert(newFeature);
			pFe->setIndex(vecBigramFeatures->length());
			vecBigramFeatures->push_back(pFe);
			feIndex = pFe->getIndex();
		}else{//found
			feIndex = iter->second->getIndex();
			delete pFe;
		}

		pCPT->addFeature(feIndex);
	}
	return pCPT;
}

CR* Template::extractCR(IndexedSentence* pIS, int pos, Indices* ind)
{
	std::tr1::unordered_map<string, Feature*>* mapBigramFeature = ind->m_mapBigramFeature;
	MyVector<Feature>* vecBigramFeatures = ind->m_vecBigramFeatures;

	CR* pCR = new CR;
	int feNum = m_vecBigramFT->length();
	for(int i = 0; i < feNum; ++ i){
		FeatureTemplate* ft = m_vecBigramFT->getItem(i);
		Feature* pFe = ft->extractFeature(pIS, pos);
		string strFe = pFe->toString();
		int feIndex;
		std::tr1::unordered_map <string, Feature*>::const_iterator iter = mapBigramFeature->find(strFe);
		if(iter == mapBigramFeature->end()){ //not found
			std::pair<string, Feature*> newFeature (strFe, pFe);
			mapBigramFeature->insert(newFeature);
			pFe->setIndex(vecBigramFeatures->length());
			vecBigramFeatures->push_back(pFe);
			feIndex = pFe->getIndex();
		}else{//found
			feIndex = iter->second->getIndex();
			delete pFe;
		}

		pCR->addFeature(feIndex);
	}
	return pCR;
}

