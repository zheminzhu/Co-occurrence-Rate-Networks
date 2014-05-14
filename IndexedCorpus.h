/*
 * IndexedCorpus.h
 *
 *  Created on: Feb 28, 2014
 *      Author: zhemin
 */

#ifndef INDEXEDCORPUS_H_
#define INDEXEDCORPUS_H_

#include <vector>
#include <tr1/unordered_map>
#include <string>

#include "Corpus.h"
#include "Utils.h"
#include "CPT.h"
#include "Indices.h"

using std::tr1::unordered_map;
using namespace std;

class IndexedCorpus;
class Feature;
class Indices;

class IndexedToken{
public:
	IndexedToken(Token* pToken, Indices* const ic);
	int getColNum();
	int getCol(int pos);
	int getTag();
	string toString();
	void print();
private:
	vector<int> m_vecColumn;
	int m_iTag;
};

class IndexedSentence{
public:
	IndexedSentence(Sentence* pSentence,  Indices* const ic);
	~IndexedSentence();
	int getTokenNum();
	IndexedToken* getToken(int i);
	string toString();
	void print();
	MyString* getTagString();
private:
	MyVector<IndexedToken>* m_vecIndexedTokens;
};


//an instance of IndexedCorpus is built by Indices::buildIndexedCorpus
class IndexedCorpus{
public:
	IndexedCorpus(const char* corpusFile);
	~IndexedCorpus();
	int getSentenceNum();
	IndexedSentence* getSentence(int i);
	string toString();
	void print();
	void addIndexedSentence(IndexedSentence* pIS);
	int getColNum();
	const char* getCorpusFile();
private:
	MyVector<IndexedSentence>* m_pVecSentences;
	const char* m_corpusFile;
};

#endif /* INDEXEDCORPUS_H_ */
