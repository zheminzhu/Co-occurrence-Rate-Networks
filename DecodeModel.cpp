/*
 * DecodeModel.cpp
 *
 *  Created on: Mar 5, 2014
 *      Author: zhemin
 */
#include <iostream>

#include "DecodeModel.h"

using namespace std;

Indices* DecodeModel::getIndices(){
	return m_pIndices;
}

DecodeModel:: ~DecodeModel(){
	delete m_pIndices;
	delete m_pTemplate;
	delete m_pCTPs;
}

IndexedCorpus* DecodeModel::index(const char* testCorpusFile){
	Corpus* pTestCorpus = new Corpus(testCorpusFile);
	IndexedCorpus* ic = m_pIndices->index(pTestCorpus);
	delete pTestCorpus;
	return ic;
}
