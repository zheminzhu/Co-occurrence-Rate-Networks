/*
 * Corpus.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: zhemin
 */

#include <iostream>

#include "Corpus.h"

using namespace std;

Token::Token(MyString* pLine){
	MyVector<MyString>* pItems = pLine->splitBySpace();
	m_pTag = pItems->getLast();
	m_pVecColums = new MyVector<MyString>;
	for(int i = 0; i < pItems->length() - 1; ++ i){
		MyString* pColumn =  pItems->getItem(i);
		m_pVecColums->push_back(pColumn);
	}
}

Token::Token(){
	m_pVecColums = new MyVector<MyString>;
}

Token::~Token(){
	delete m_pTag;
	delete m_pVecColums;
}

MyString* Token::getTag(){
	return m_pTag;
}

int Token::getColumnNum(){
	return m_pVecColums->length();
}

MyString* Token::getColumn(int i){
	return m_pVecColums->getItem(i);
}

void Token::addCol(MyString* col){
	m_pVecColums->push_back(col);
}

void Token::setTag(MyString* tag){
	m_pTag = tag;
}

MyString* Token::toString(){
	MyString* str = new MyString();
	for(int i = 0; i < getColumnNum(); ++ i){
		MyString* pCol = getColumn(i);
		str->join(pCol);
		str->join("\t");
	}
	str->join(m_pTag);
	return str;
}

void Token::println(){
	MyString* str = toString();
	str->println();
	delete str;
}

Sentence::Sentence(MyString* pBlock){
	MyVector<MyString>* pLines = pBlock->split('\n');
	int colNum = pLines->getFirst()->splitBySpace()->length() - 1;
	m_pVecTokens = new MyVector<Token>;
	if(MyGlobal::g_bStartEnd)
		m_pVecTokens->push_back(genStartToken(colNum));
	for(int i = 0; i < pLines->length(); ++ i){
		MyString* pLine = pLines->getItem(i);
		Token* token = new Token(pLine);
		m_pVecTokens->push_back(token);
	}
	if(MyGlobal::g_bStartEnd)
		m_pVecTokens->push_back(genEndToken(colNum));
}

Token* Sentence::genStartToken(int itemNum){
	Token* token = new Token();
	for(int i = 0; i < itemNum; ++ i){
		MyString* str = new MyString("Start");
		str->join(new MyString(i));
		token->addCol(str);
	}
	MyString* strTag = new MyString("StartTag");
	token->setTag(strTag);
	return token;
}

Token* Sentence::genEndToken(int itemNum){
	Token* token = new Token();
	for(int i = 0; i < itemNum; ++ i){
		MyString* str = new MyString("End");
		str->join(new MyString(i));
		token->addCol(str);
	}
	MyString* strTag = new MyString("EndTag");
	token->setTag(strTag);
	return token;
}

Sentence::~Sentence(){
	delete m_pVecTokens;
}

int Sentence::getTokenNum(){
	return m_pVecTokens->length();
}

Token* Sentence::getToken(int i){
	return m_pVecTokens->getItem(i);
}

MyString* Sentence::toString(){
	MyString* pStr = new MyString();
	for(int i = 0; i < m_pVecTokens->length(); ++ i){
		Token* pToken = m_pVecTokens->getItem(i);
		MyString* pLine = pToken->toString();
		pStr->join(pLine);
		pStr->join("\n");
		delete pLine;
	}
	return pStr;
}

void Sentence::println(){
	MyString* pStr = toString();
	pStr->println();
	delete pStr;
}

Corpus::Corpus(const char* pCorpusFile): m_pCorpusFile(pCorpusFile){
	cout << "Reading corpus: " << pCorpusFile <<endl << std::flush;

	m_pVecSentences = new MyVector<Sentence>;
	MyString* pFileBuffer = MyFile::readFile(pCorpusFile);
	MyString sentence_seperator ("\n\n");
	MyVector<MyString>* pSentenceStrs = pFileBuffer->split(&sentence_seperator);
	for(int i = 0; i < pSentenceStrs->length(); ++ i){
		MyString* pSentenceStr = pSentenceStrs->getItem(i);
		Sentence* pSentence = new Sentence(pSentenceStr);
		m_pVecSentences->push_back(pSentence);
	}

	cout << "Reading training dataset finished!\n" << std::flush;
	cout << "#Sentence:\t" << getSentenceNum() << endl << std::flush;
	cout << "#Token:\t" << getTokenNum() << endl << endl << std::flush;

	delete pFileBuffer;
	delete pSentenceStrs;
}

int Corpus::getColumnNum(){
	return m_pVecSentences->getFirst()->getToken(0)->getColumnNum();

}

int Corpus::getTokenNum(){
	int tokenNum = 0;
	int sentenceNum = getSentenceNum();
	for(int i = 0; i < sentenceNum; ++ i){
		Sentence* pSent = m_pVecSentences->getItem(i);
		tokenNum += pSent->getTokenNum();
	}
	return tokenNum;
}

Corpus::Corpus(const char* pCorpusFile, int num){
	cout << "Reading training dataset ...\n" << std::flush;
	m_pVecSentences = new MyVector<Sentence>;
	MyString* pFileBuffer = MyFile::readFile(pCorpusFile);
	MyString sentence_seperator ("\n\n");
	MyVector<MyString>* pSentenceStrs = pFileBuffer->split(&sentence_seperator);
	for(int i = 0; i < num; ++ i){
		MyString* pSentenceStr = pSentenceStrs->getItem(i);
		Sentence* pSentence = new Sentence(pSentenceStr);
		m_pVecSentences->push_back(pSentence);
	}
	cout << "Reading training dataset finished!\n" << std::flush;
	cout << "#Sentence:\t" << getSentenceNum() << endl << std::flush;
	cout << "#Token:\t" << getTokenNum() << endl << endl << std::flush;

	delete pFileBuffer;
	delete pSentenceStrs;
}

Corpus::~Corpus(){
	delete m_pVecSentences;
}

Sentence* Corpus::getSentence(int i){
	return m_pVecSentences->getItem(i);
}

int Corpus::getSentenceNum(){
	return m_pVecSentences->length();
}

MyString* Corpus::toString(){
	MyString* str = new MyString();
	int sentenceNum = getSentenceNum();
	for(int i = 0; i < sentenceNum; ++ i){
		Sentence* pSentence = m_pVecSentences->getItem(i);
		MyString* pStr = pSentence->toString();
		str->join(pStr);
		str->join("\n");
		delete pStr;
	}
	return str;
}

const char* Corpus::getCorpusFile(){
	return m_pCorpusFile;
}

void Corpus::print(){
	MyString* pStr = toString();
	pStr->print();
	delete pStr;
}
