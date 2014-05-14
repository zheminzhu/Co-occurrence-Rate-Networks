/*
 * ViterbiDecoder.h
 *
 *  Created on: Mar 5, 2014
 *      Author: zhemin
 */

#ifndef VITERBIDECODER_H_
#define VITERBIDECODER_H_


#include "DecodeModel.h"
#include "Utils.h"
#include "IndexedCorpus.h"
#include "Result.h"

using namespace std;

class TagGainPre;
class MatrixTGP;

class ViterbiDecoder {
public:
	ViterbiDecoder(DecodeModel* decodeModel);
	~ViterbiDecoder();
	ResultSentence* decode(IndexedSentence* pIS);
private:
	DecodeModel* m_decodeModel;
	void calcMaximumPre(IndexedSentence* pIS, int pos, TagGainPre* pTGP, MyVector<TagGainPre>* preCol);
	void getMaxPath(ResultSentence* result, MatrixTGP* matrix);
	double calcGain(IndexedSentence* pIS, int pos, TagGainPre* pre, TagGainPre* cur);
	TagGainPre* selectMax(MyVector<TagGainPre>* col);
};

class MatrixTGP{
public:
	MatrixTGP(IndexedSentence* pIS, DecodeModel* pModel);
	int getColumNum();
	int getTGPNum();
	MyVector<TagGainPre>* getColumn(int i);
	MyVector<TagGainPre>* getLastColumn();
	TagGainPre* getTGP();
	~MatrixTGP();
	MyString* toString();
	void print();
	MyVector<MyVector<TagGainPre>>* m_pMatrix;
private:
	IndexedSentence* m_pIS;
};

class TagGainPre{
public:
	TagGainPre(int tag);
	void setPre(TagGainPre* pre);
	void setGain(double gain);
	void setUnigramLogProb(double logProb);
	int getTag();
	double getGain();
	TagGainPre* getPre();
	MyString* toString();
	void print();
	double getUnigramLogProb();
private:
	int m_tag;
	double m_unigramLogProb;
	double m_gain;
	TagGainPre* m_pre;
};

#endif /* VITERBIDECODER_H_ */
