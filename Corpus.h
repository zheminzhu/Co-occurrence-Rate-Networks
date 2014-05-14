/*
 * Corpus.h
 *
 *  Created on: Feb 27, 2014
 *      Author: zhemin
 */

#ifndef CORPUS_H_
#define CORPUS_H_

#include "Utils.h"

using namespace std;

class Token{
public:
	Token(MyString* pLine);
	Token();
	~Token();
	int getColumnNum();
	MyString* getColumn(int i);
	MyString* toString();
	void println();
	MyString* getTag();
	void addCol(MyString* col);
	void setTag(MyString* pTag);
private:
	MyVector<MyString>* m_pVecColums;
	MyString* m_pTag;
};

class Sentence{
public:
	Sentence(MyString* pBlock);
	~Sentence();
	int getTokenNum();
	Token* getToken(int i);
	MyString* toString();
	void println();
private:
	Token* genStartToken(int itemNum);
	Token* genEndToken(int itemNum);
	MyVector<Token>* m_pVecTokens;
};

class Corpus {
public:
	Corpus(const char* pCorpusFile);
	Corpus(const char* pCorpusFile, int num);
	~Corpus();
	int getSentenceNum();
	int getTokenNum();
	int getColumnNum();
	Sentence* getSentence(int i);
	MyString* toString();
	void print();
	const char* getCorpusFile();
private:
	MyVector<Sentence>* m_pVecSentences;
	const char* m_pCorpusFile;
};

#endif /* CORPUS_H_ */
