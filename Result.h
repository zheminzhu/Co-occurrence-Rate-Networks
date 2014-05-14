/*
 * Result.h
 *
 *  Created on: Mar 11, 2014
 *      Author: zhemin
 */

#ifndef RESULT_H_
#define RESULT_H_

#include "Utils.h"
#include "IndexedCorpus.h"
#include "DecodeModel.h"

using namespace std;

class ResultSentence;
class ResultCorpus;
class Evaluation;

class ResultCorpus{
public:
	ResultCorpus();
	virtual ~ResultCorpus();
	void addResultSentence(ResultSentence* pRS);
	void save2File(const char* resultFile, Indices* pIndices);
	int getSentenceNum();
	ResultSentence* getResultSentence(int pos);
private:
	MyVector<ResultSentence>* m_rs;
};

class ResultSentence{
public:
	ResultSentence(IndexedSentence* pIS);
	void setAnnTag(int tag, int pos);
	~ResultSentence();
	MyString* toStringHorizontal();
	MyString* toStringVertical();
	MyString* toSaveString(Indices* pIndices);
	void print();
	void println();
	int getCorrTag(int i);
	int getAnnTag(int i);
	int getTagNum();
	bool isOOV(int i);
	IndexedSentence* getIS();
private:
	IndexedSentence* m_pIS;
	int* m_annTags;
};

class Evaluation{
public:
	static double accuracy(ResultSentence* pRS);
	static void accuracy(ResultCorpus* pRC, DecodeModel* pModel);
private:
	static int getCorrTagNum(ResultSentence* pRS);
};

#endif /* RESULT_H_ */
