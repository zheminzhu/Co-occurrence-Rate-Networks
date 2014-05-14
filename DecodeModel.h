/*
 * DecodeModel.h
 *
 *  Created on: Mar 5, 2014
 *      Author: zhemin
 */

#ifndef DECODEMODEL_H_
#define DECODEMODEL_H_

#include <vector>

#include "IndexedCorpus.h"
#include "CPT.h"

using namespace std;

class DecodeModel {
public:
	IndexedCorpus* index(const char* testCorpusFile);
	virtual double getUnigramProb(IndexedSentence* pSent, int pos, int tag) = 0;
	virtual double getCR(IndexedSentence* pSent, int pos, int preTag, int curTag) = 0;
	virtual vector<int> getPromisingTags(IndexedSentence* pSent, int pos) = 0;
	virtual bool isOOV(IndexedSentence* pIS, int pos) = 0;
	virtual ~DecodeModel();
	Indices* getIndices();
protected:
	Indices* m_pIndices;
	Template* m_pTemplate;
	CPTConstuctor* m_pCTPs;
};

#endif /* DECODEMODEL_H_ */
