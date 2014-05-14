/*
 * IndexedCorpus.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: zhemin
 */

#include <iostream>
#include <vector>
#include <cstdio>

#include "IndexedCorpus.h"

using namespace std;

IndexedToken::IndexedToken(Token* pToken, Indices* const ic){
	int colNum = pToken->getColumnNum();
	for(int i = 0; i < colNum; ++ i){
		MyString* col = pToken->getColumn(i);
		int index = ic->getIntCol(i, col->getString());
		m_vecColumn.push_back(index);
	}
	MyString* tag = pToken->getTag();
	m_iTag = ic->getIntTag(tag->getString());
}

string IndexedToken::toString(){
	MyString mystr;
	char buffer [50];
	for(int i : m_vecColumn){
		int n = sprintf (buffer, "%d", i);
		MyString str(buffer, buffer + n, true);
		mystr.join(&str);
		mystr.join("\t");
	}
	int n = sprintf (buffer, "%d", m_iTag);
	MyString str(buffer, buffer + n, true);
	mystr.join(&str);
	return mystr.getString();
}

void IndexedToken::print(){
	cout << toString() << endl << std::flush;
}

int IndexedToken::getColNum(){
	return m_vecColumn.size();
}

int IndexedToken::getCol(int i){
	return m_vecColumn[i];
}

int IndexedToken::getTag(){
	return m_iTag;
}

IndexedSentence::IndexedSentence(Sentence* pSentence,  Indices* const ic){
	m_vecIndexedTokens = new MyVector<IndexedToken>;
	int tokenNum = pSentence->getTokenNum();
	for(int i = 0; i < tokenNum; ++ i){
		IndexedToken* it = new IndexedToken(pSentence->getToken(i), ic);
		m_vecIndexedTokens->push_back(it);
	}
}

MyString* IndexedSentence::getTagString(){
	MyString* pStr = new MyString;
	int tokenNum = getTokenNum();
	for(int i = 0; i < tokenNum; ++ i){
		IndexedToken* it = getToken(i);
		MyString strTag(it->getTag());
		pStr->join(&strTag);
		pStr->join(" ");
	}
	return pStr;
}

string IndexedSentence::toString(){
	string str;
	int tokenNum = getTokenNum();
	for(int i = 0; i < tokenNum; ++ i){
		IndexedToken* pToken = m_vecIndexedTokens->getItem(i);
		str += pToken->toString() + "\n";
	}
	str += "\n";
	return str;
}

void IndexedSentence::print(){
	cout << toString() << endl << std::flush;
}

IndexedSentence::~IndexedSentence(){
	delete m_vecIndexedTokens;
}

int IndexedSentence::getTokenNum(){
	return m_vecIndexedTokens->length();
}

IndexedToken* IndexedSentence::getToken(int i){
	return m_vecIndexedTokens->getItem(i);
}


Indices::Indices(Corpus* pCorpus){
	m_corpusFile = pCorpus->getCorpusFile();
	buildIndices(pCorpus);
}


IndexedCorpus::~IndexedCorpus(){
	delete m_pVecSentences;
}

int IndexedCorpus::getSentenceNum(){
	return m_pVecSentences->length();
}

IndexedSentence* IndexedCorpus::getSentence(int i){
	return m_pVecSentences->getItem(i);
}

string Indices::getStringCol(int col, int index){
	return m_vecMapInt2StringCol->getItem(col)->at(index);
}

string Indices::getStringTag(int index){
	return m_mapInt2StringTag[index];
}

int Indices::getUnigramTagNum(){
	return m_mapInt2StringTag.size();
}

int Indices::getBigramTagNum(){
	return m_mapInt2StringBiTag.size();
}

IndexedCorpus::IndexedCorpus(const char* corpusFile){
	m_pVecSentences = new MyVector<IndexedSentence>;
	m_corpusFile = corpusFile;
}

string IndexedCorpus::toString(){
	string str;
	int sentenceNum = getSentenceNum();
	for(int i = 0; i < sentenceNum; ++ i){
		IndexedSentence* pIS = m_pVecSentences->getItem(i);
		str += pIS->toString() + "\n";
	}
	return str;
}

void IndexedCorpus::print(){
	cout << toString() << endl << std::flush;
}

void IndexedCorpus::addIndexedSentence(IndexedSentence* pIS){
	m_pVecSentences->push_back(pIS);
}

int IndexedCorpus::getColNum(){
	return m_pVecSentences->getFirst()->getToken(0)->getColNum();
}

const char* IndexedCorpus::getCorpusFile(){
	return m_corpusFile;
}

int Indices::getIntCol(int col, string str){
	vector<string>* vec = m_vecMapInt2StringCol->getItem(col);
	unordered_map <string, int>* map = m_vecMapString2IntCol->getItem(col);
	auto got = map->find(str);
	if(got == m_vecMapString2IntCol->getItem(col)->end()){// not found
		int index = vec->size();
		map->insert(std::make_pair(str, index));
		vec->push_back(str);
		return index;
	}else{ // found
		return got->second;
	}
}

int Indices::getUnigramFeatureNum(){
	return m_vecUnigramFeatures->length();
}

int Indices::getBigramFeatureNum(){
	return m_vecBigramFeatures->length();
}

void Indices::printColCardinalities(){
	int colNum = m_vecMapInt2StringCol->length();
	cout << "#Column: " << colNum << endl << std::flush;
	MyString str;
	int sum = 0;
	for(int i = 0; i < colNum; ++ i){
		int cardinality = m_vecMapInt2StringCol->getItem(i)->size();
		sum += cardinality;
		MyString strCard(cardinality);
		str.join(&strCard);
		str.join(" ");
	}
	str.println();
	cout << "Total: " << sum << endl << std::flush;
}

int Indices::getIntTag(string str){
	unordered_map <string, int>::const_iterator got = m_mapString2IntTag.find(str);
	if(got == m_mapString2IntTag.end()){// not found
		return -1;
	}else{ // found
		return got->second;
	}
}
