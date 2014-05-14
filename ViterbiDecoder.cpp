/*
 * ViterbiDecoder.cpp
 *
 *  Created on: Mar 5, 2014
 *      Author: zhemin
 */
#include <cmath>
#include <float.h>
#include <iostream>

#include "ViterbiDecoder.h"

using namespace std;

ViterbiDecoder::ViterbiDecoder(DecodeModel* decodeModel){
	m_decodeModel = decodeModel;
}

ViterbiDecoder::~ViterbiDecoder(){
	delete m_decodeModel;
}

TagGainPre::TagGainPre(int tag){
	m_tag = tag;
	m_gain = -DBL_MAX;
	m_pre = NULL;
}

void TagGainPre::setPre(TagGainPre* pre){
	m_pre = pre;
}

void TagGainPre::setGain(double gain){
	m_gain = gain;
}

void TagGainPre::setUnigramLogProb(double logProb){
	m_unigramLogProb = logProb;
}

int TagGainPre::getTag(){
	return m_tag;
}

MyString* TagGainPre::toString(){
	char buffer[128];
	if(m_pre == NULL){
		if(m_gain < -10000000){
			sprintf(buffer, "%d -inf NULL", m_tag);
		}else{
			sprintf(buffer, "%d %.3f NULL", m_tag, m_gain);
		}
	}else{
		if(m_gain < -10000000){
			sprintf(buffer, "%d -inf %d", m_tag, m_pre->m_tag);
		}else{
			sprintf(buffer, "%d %.3f %d", m_tag, m_gain, m_pre->m_tag);
		}
	}
	MyString* str = new MyString(buffer);
	return str;
}

void TagGainPre::print(){
	MyString* str = toString();
	str->print();
	delete str;
}

double TagGainPre::getGain(){
	return m_gain;
}

TagGainPre* TagGainPre::getPre(){
	return m_pre;
}

MatrixTGP::MatrixTGP(IndexedSentence* pIS, DecodeModel* pModel){
	m_pIS = pIS;
	int tokenNum = pIS->getTokenNum();
	m_pMatrix = new MyVector<MyVector<TagGainPre>>;
	for(int i = 0; i < tokenNum; ++ i){
		MyVector<TagGainPre>* pColumn = new MyVector<TagGainPre>;
		vector<int> promisingTags = pModel->getPromisingTags(pIS, i);
		for(int tag : promisingTags){
			TagGainPre* tgp = new TagGainPre(tag);
			double unigramLogProb = log(pModel->getUnigramProb(pIS, i, tag));
			tgp->setUnigramLogProb(unigramLogProb);
			pColumn->push_back(tgp);
		}
		m_pMatrix->push_back(pColumn);
	}
}

MyString* MatrixTGP::toString(){
	MyString* str = new MyString();
	int colNum = getColumNum();
	for(int col = 0; col < colNum; ++ col){
		MyVector<TagGainPre>* pCol = getColumn(col);
		int tgpNum = pCol->length();
		IndexedToken* pIT = m_pIS->getToken(col);
		char buff[50];
		sprintf(buff, "%d:%d\t", pIT->getCol(0), pIT->getTag());
		str->join(buff);
		for(int i = 0; i < tgpNum; ++i){
			TagGainPre* pTGP = pCol->getItem(i);
			MyString* pStrTGP = pTGP->toString();
			str->join(pStrTGP);
			str->join(" | ");
			delete pStrTGP;
		}
		str->join("\n");
	}
	return str;
}

void MatrixTGP::print(){
	MyString* str = toString();
	str->println();
	delete str;
}

MatrixTGP::~MatrixTGP(){
	delete m_pMatrix;
}

int MatrixTGP::getColumNum(){
	return m_pMatrix->length();
}

MyVector<TagGainPre>* MatrixTGP::getColumn(int i){
	return m_pMatrix->getItem(i);
}

MyVector<TagGainPre>* MatrixTGP::getLastColumn(){
	return m_pMatrix->getItem(getColumNum() - 1);
}

ResultSentence* ViterbiDecoder::decode(IndexedSentence* pSentence){
	ResultSentence* result = new ResultSentence(pSentence);
	MatrixTGP matrix(pSentence, m_decodeModel);

	//matrix.print();
	//cout << endl << endl << std::flush;


	int tokenNum = matrix.getColumNum();
	if(tokenNum <= 0) return NULL;


	//the first token
	MyVector<TagGainPre>* firstCol = matrix.getColumn(0);
	int tagNum = firstCol->length();
	for(int i = 0; i < tagNum; ++ i){
		TagGainPre* pTGP = firstCol->getItem(i);
		int tag = pTGP->getTag();
		double prob = m_decodeModel->getUnigramProb(pSentence, 0, tag);
		double gain = log(prob);
		pTGP->setGain(gain);
		pTGP->setPre(NULL);
	}

	//matrix.print();
	//cout << endl << endl << std::flush;

	//1 ... n-1 tokens
	for(int pos = 1; pos < tokenNum; ++ pos){
		MyVector<TagGainPre>* curCol = matrix.getColumn(pos);
		MyVector<TagGainPre>* preCol = matrix.getColumn(pos - 1);
		int tagNum = curCol->length();
		for(int i = 0; i < tagNum; ++ i){
			TagGainPre* pTGP = curCol->getItem(i);
			calcMaximumPre(pSentence, pos, pTGP, preCol);
			//matrix.print();
			//cout << endl << endl << std::flush;
		}
	}

	getMaxPath(result, &matrix);
	return result;
}

void ViterbiDecoder::calcMaximumPre(
		IndexedSentence* pIS,
		int pos,
		TagGainPre* pTGP,
		MyVector<TagGainPre>* preCol)
{
	double maxGain = -DBL_MAX;
	TagGainPre* maxPreTGP = NULL;
	int numPreTGP = preCol->length();
	for(int i = 0; i < numPreTGP; ++ i){
		TagGainPre* pre = preCol->getItem(i);
		double gain = calcGain(pIS, pos, pre, pTGP);
		if(gain >= maxGain){
			maxGain = gain;
			maxPreTGP = pre;
		}
	}

	pTGP->setPre(maxPreTGP);
	pTGP->setGain(maxGain);
}

double TagGainPre::getUnigramLogProb(){
	return m_unigramLogProb;
}

double ViterbiDecoder::calcGain(
		IndexedSentence* pIS,
		int pos,
		TagGainPre* pre,
		TagGainPre* cur)
{
	double preGain = pre->getGain();
	double uniProb = cur->getUnigramLogProb();
	double cr = log(m_decodeModel->getCR(pIS, pos, pre->getTag(), cur->getTag()));
	double gain = preGain + uniProb + cr;
	return gain;
}

void ViterbiDecoder::getMaxPath(ResultSentence* result, MatrixTGP* matrix){
	//matrix->print();
	MyVector<TagGainPre>* lastCol = matrix->getLastColumn();
	TagGainPre* maxTGP = selectMax(lastCol);

	int colNum = matrix->getColumNum();

	for(int i = colNum - 1; i >= 0; -- i){
		result->setAnnTag(maxTGP->getTag(), i);
		maxTGP = maxTGP->getPre();
		if(maxTGP == NULL && i != 0)
			maxTGP = selectMax(matrix->getColumn(i - 1));
	}
}

TagGainPre* ViterbiDecoder::selectMax(MyVector<TagGainPre>* col){
	TagGainPre* pMaxGrain = col->getFirst();
	TagGainPre* pMaxUniProb = col->getFirst();
	int num = col->length();
	for(int i = 1; i < num; ++ i){
		TagGainPre* pTGP = col->getItem(i);
		if(pTGP->getGain() > pMaxGrain->getGain())
			pMaxGrain = pTGP;
		if(pTGP->getUnigramLogProb() > pMaxGrain->getUnigramLogProb())
			pMaxUniProb = pTGP;
	}

	if(pMaxGrain->getGain() < -10000000)
		return pMaxUniProb;
	return pMaxGrain;
}
