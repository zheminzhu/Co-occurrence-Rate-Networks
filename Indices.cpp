/*
 * Indices.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: zhemin
 */

#include <iostream>

#include "Indices.h"

using namespace std;

Indices::~Indices(){
	delete 	m_vecMapString2IntCol;
	delete m_vecMapInt2StringCol;

	//unigram feature index
	delete m_mapUnigramFeature;
	delete m_vecUnigramFeatures;

	//bigram feature index
	delete m_mapBigramFeature;
	delete m_vecBigramFeatures;
}

IndexedCorpus* Indices::index(Corpus* pCorpus){
	cout << "Indexing corpus: " << pCorpus->getCorpusFile() << endl << std::flush;
	IndexedCorpus* pIndexedCorpus = new IndexedCorpus(pCorpus->getCorpusFile());
	int sentNum = pCorpus->getSentenceNum();
	for(int i = 0; i < sentNum; ++ i){
		Sentence* pSentence = pCorpus->getSentence(i);
		IndexedSentence* pIS = new IndexedSentence(pSentence, this);
		pIndexedCorpus->addIndexedSentence(pIS);
	}
	cout << "Indexing corpus finished!" << endl << endl << std::flush;
	return pIndexedCorpus;
}

void Indices::buildIndices(Corpus* pCorpus){
	cout << "Building indices using: " << pCorpus->getCorpusFile() << endl << std::flush;
	int sentenceNum = pCorpus->getSentenceNum();
	int colNum = pCorpus->getSentence(0)->getToken(0)->getColumnNum();
	m_vecMapString2IntCol = new MyVector<unordered_map <string, int>>;
	m_vecMapInt2StringCol = new MyVector<vector<string>>;
	for(int i = 0; i < colNum; ++ i){
		unordered_map <string, int>* p = new unordered_map <string, int>;
		m_vecMapString2IntCol->push_back(p);
		vector<string>* pv = new vector<string>;
		m_vecMapInt2StringCol->push_back(pv);
	}

	for(int i = 0; i < sentenceNum; ++ i){
		Sentence* pSentence = pCorpus->getSentence(i);
		int tokenNum = pSentence->getTokenNum();
		for(int j = 0; j < tokenNum; ++ j){
			Token* pToken = pSentence->getToken(j);

			//column
			for(int k = 0; k < colNum; ++ k){
				MyString* pCol = pToken->getColumn(k);

				unordered_map <string, int>* string2int = m_vecMapString2IntCol->getItem(k);
				vector<string>* int2string = m_vecMapInt2StringCol->getItem(k);

				unordered_map <string, int>::const_iterator got = string2int->find(pCol->getString());
				if(got == string2int->end()){// not found
					std::pair<string, int> newIndex (pCol->getString(), int2string->size());
					string2int->insert(newIndex);
					int2string->push_back(pCol->getString());
				}
			}

			//unigram tag
			MyString* pTag = pToken->getTag();
			unordered_map <string, int>::const_iterator got = m_mapString2IntTag.find(pTag->getString());
			if(got == m_mapString2IntTag.end()){// not found
					std::pair<string, int> newIndex (pTag->getString(), m_mapInt2StringTag.size());
					m_mapString2IntTag.insert(newIndex);
					m_mapInt2StringTag.push_back(pTag->getString());
			}

		}

	}

	for(int i = 0; i < sentenceNum; ++ i){
			Sentence* pSentence = pCorpus->getSentence(i);
			int tokenNum = pSentence->getTokenNum();
			for(int j = 1; j < tokenNum; ++ j){
				Token* pPreToken = pSentence->getToken(j - 1);
				Token* pCurrToken = pSentence->getToken(j);
				int preTag = m_mapString2IntTag.find(pPreToken->getTag()->getString())->second;
				int curTag = m_mapString2IntTag.find(pCurrToken->getTag()->getString())->second;
				string strBitag = BiTag::mergeTag(preTag, curTag);
				unordered_map <string, int>::const_iterator got = m_mapString2IntBiTag.find(strBitag);
				if(got == m_mapString2IntBiTag.end()){// not found
					std::pair<string, int> newIndex (strBitag, m_mapInt2StringBiTag.size());
					m_mapString2IntBiTag.insert(newIndex);
					m_mapInt2StringBiTag.push_back(strBitag);
				}
			}
	}

	//unigram feature index
	m_mapUnigramFeature = new std::tr1::unordered_map<string, Feature*>;
	m_vecUnigramFeatures = new MyVector<Feature>;

	//bigram feature index
	m_mapBigramFeature = new std::tr1::unordered_map<string, Feature*>;
	m_vecBigramFeatures = new MyVector<Feature>;
	printColCardinalities();
	cout << "Building indices finished!" << endl << endl << std::flush;
}

string Indices::getStringBiTag(int index){
	return m_mapInt2StringBiTag[index];
}

int Indices::getIntBiTag(string str){
	unordered_map <string, int>::const_iterator got = m_mapString2IntBiTag.find(str);
	if(got == m_mapString2IntBiTag.end()){// not found
		return -1;
	}else{ // found
		return got->second;
	}
}
