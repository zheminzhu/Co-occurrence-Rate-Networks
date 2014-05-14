/*
 * Result.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: zhemin
 */

#include <iostream>
#include <string>
#include <cstdio>

#include "Result.h"

using namespace std;

ResultCorpus::ResultCorpus(){
	m_rs = new MyVector<ResultSentence>;
}

void ResultCorpus::addResultSentence(ResultSentence* pRS){
	m_rs->push_back(pRS);
}

void ResultCorpus::save2File(const char* resultFile, Indices* pIndices){
	cout << "Saving the results ... " << endl << std::flush;
	int sentenceNum = getSentenceNum();
	MyString strSave;
	for(int i = 0; i < sentenceNum; ++ i){
		ResultSentence* pRS = getResultSentence(i);
		MyString* strSentence = pRS->toSaveString(pIndices);
		strSave.join(strSentence);
		strSave.join("\n");
		delete strSentence;
	}

	MyFile::writeFile(&strSave, resultFile);
	cout << "Results saved to: " << resultFile << endl << std::flush;
}

ResultSentence* ResultCorpus::getResultSentence(int pos){
	return m_rs->getItem(pos);
}

int ResultCorpus::getSentenceNum(){
	return m_rs->length();
}

ResultCorpus::~ResultCorpus(){
	delete m_rs;
}

ResultSentence::ResultSentence(IndexedSentence* pIS){
	m_pIS = pIS;
	int size = getTagNum();
	m_annTags = new int[size];
}

MyString* ResultSentence::toSaveString(Indices* pIndices){
	int tagNum = getTagNum();
	MyString* pStr = new MyString();
	for(int i = 0; i < tagNum; ++ i){
		MyString mystrToken;
		int annTag = getAnnTag(i);
		string strAnnTag = pIndices->getStringTag(annTag);
		MyString mystrAnnTag(strAnnTag.c_str());

		mystrToken.join(&mystrAnnTag);
		mystrToken.join("\n");

		pStr->join(&mystrToken);
	}
	return pStr;
}

MyString* ResultSentence::toStringHorizontal(){
	MyString* pStr = new MyString();
	int size = getTagNum();
	for(int i = 0; i < size; ++ i){
		int tag = m_annTags[i];
		MyString strTag(tag);
		pStr->join(&strTag);
		pStr->join(" ");
	}
	return pStr;
}

MyString* ResultSentence::toStringVertical(){
	MyString* pStr = new MyString();
	int size = getTagNum();
	for(int i = 0; i < size; ++ i){
		int tag = m_annTags[i];
		MyString strTag(tag);
		pStr->join(&strTag);
		pStr->join("\n");
	}
	return pStr;
}

void ResultSentence::print(){
	MyString* strPrint = toStringHorizontal();
	strPrint->join("\n");
	MyString* pStrCorrTags = m_pIS->getTagString();
	strPrint->join(pStrCorrTags);
	strPrint->join("\nSentence accuracy: ");
	double accuracy = Evaluation::accuracy(this);
	char buff[128];
	sprintf(buff, "%f\n\n", accuracy);
	strPrint->join(buff);
	strPrint->print();

	delete pStrCorrTags;
	delete strPrint;
}

ResultSentence::~ResultSentence(){
	delete[] m_annTags;
}

void ResultSentence::setAnnTag(int tag, int pos){
	m_annTags[pos] = tag;
}

int ResultSentence::getCorrTag(int i){
	return m_pIS->getToken(i)->getTag();
}

int ResultSentence::getAnnTag(int i){
	return m_annTags[i];
}

int ResultSentence::getTagNum(){
	return m_pIS->getTokenNum();
}

bool ResultSentence::isOOV(int i){
	if(m_pIS->getToken(i)->getCol(0) == -1)
		return true;
	return false;
}

IndexedSentence* ResultSentence::getIS(){
	return m_pIS;
}

double Evaluation::accuracy(ResultSentence* pRS){
	return getCorrTagNum(pRS) * 1.0 / pRS->getTagNum();
}

int Evaluation::getCorrTagNum(ResultSentence* pRS){
	int corr = 0;
	int size = pRS->getTagNum();
	for(int i = 0; i < size; ++ i){
		int corrTag = pRS->getCorrTag(i);
		int annTag = pRS->getAnnTag(i);
		if(corrTag == annTag)
			++ corr;
	}
	return corr;
}

void Evaluation::accuracy(ResultCorpus* pRC, DecodeModel* pModel){
	int corr = 0;
	int total = 0;
	int corr_oov = 0;
	int total_oov = 0;

	int sentenceNum = pRC->getSentenceNum();
	for(int sent = 0; sent < sentenceNum; ++ sent){
		ResultSentence* pRS = pRC->getResultSentence(sent);
		int tokenNum = pRS->getTagNum();
		int start = 0;
		int end = tokenNum;
		if(MyGlobal::g_bStartEnd){
			start = 1;
			end = tokenNum - 1;
		}
		for(int  i = start; i < end; ++ i){
			int corrTag = pRS->getCorrTag(i);
			int annTag = pRS->getAnnTag(i);
			++ total;
			if(corrTag == annTag)
				++ corr;
			if(pModel->isOOV(pRS->getIS(), i)){
				++ total_oov;
				if(corrTag == annTag)
					++ corr_oov;
			}
		}
	}

	char buff[100];
	sprintf(buff, "#Total Accuracy: %d/%d = %f", corr, total, corr * 1.0 / total);
	MyString str1(buff);
	str1.println();

	sprintf(buff, "#OOV Accuracy: %d/%d = %f", corr_oov, total_oov, corr_oov * 1.0 / total_oov);
	MyString str2(buff);
	str2.println();

	sprintf(buff, "#non-OOV Accuracy: %d/%d = %f", corr-corr_oov, total-total_oov,
			(corr-corr_oov) * 1.0 / (total-total_oov));
	MyString str3(buff);
	str3.println();
}
