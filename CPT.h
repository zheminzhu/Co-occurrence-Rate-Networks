/*
 * CPT.h
 *
 *  Created on: Feb 28, 2014
 *      Author: zhemin
 */

#ifndef CPT_H_
#define CPT_H_

#include "IndexedCorpus.h"
#include "Utils.h"
#include "Template.h"
#include "CR.h"

using namespace std;

class IndexedCorpus;
class Template;
class CR;

class Item{
public:
	Item(int iPos, int iCol, int iVal);
	string toString();
private:
	int m_iPos;
	int m_iCol;
	int m_iVal;
};

class Feature{
public:
	Feature();
	~Feature();
	string toString();
	void addItem(Item* it);
	void setIndex(int index);
	int getIndex();
private:
	int m_index;
	MyVector<Item>* m_items;
};

class CPT{
public:
	CPT();
	~CPT();
	void addFeature(int fe);
	string toString();
	void addTag(int tag);
	double getProb(int tag);
	int getFeatureNum();
	int getFeature(int i);
	void print();
	vector<int>* getPromisingTags();
	void addProb(int tag, double prob);
	void normalizeProb();
	void sortFeatures();
	void printProbs(Indices* pInd, bool bBigram);
private:
	vector<int> m_features;
	std::tr1::unordered_map <int, int> m_mapTagCNT;
	std::tr1::unordered_map <int, double>* m_mapTagProb;
	int m_sumCNT;
	double m_sumProb;
	vector<int> m_tags;
};

class CPTConstuctor {
public:
	CPTConstuctor(IndexedCorpus* pCorpus, Template* pTemplate, Indices* pIndices, bool bCR);
	~CPTConstuctor();
	MyVector<CPT>* getUnigramCPTs();
	MyVector<CPT>* getBigramCPTs();
	MyVector<CR>* getCRs();
	CPT* getUnigramCPT(CPT* pCPT);
	CPT* getBigramCPT(CPT* pCPT);
	CR* getCR(CR* pCR);
	void insertUnigramCPT(CPT* pCPT);
	void insertBigramCPT(CPT* pCPT);
	void insertCR(CR* pCR);
	double getUniTagEmpProb(int tag);
	double getBiTagEmpProb(int tag);

private:
	void constructUnigramCPTs(IndexedCorpus* pCorpus, Template* pTemplate, Indices* pIndices);
	void constructBigramCPTs(IndexedCorpus* pCorpus, Template* pTemplate, Indices* pIndices);
	void constructCRs(IndexedCorpus* pCorpus, Template* pTemplate, Indices* pIndices);
	MyVector<CPT>* m_vecUnigramCPTs;
	std::tr1::unordered_map <string, CPT*>* m_mapUnigramCPTs;
	MyVector<CPT>* m_vecBigramCPTs;
	std::tr1::unordered_map <string, CPT*>* m_mapBigramCPTs;
	MyVector<CR>* m_vecCRs;
	std::tr1::unordered_map <string, CR*>* m_mapCRs;
	bool m_bCR;

	vector<int> m_uniTagCNT;
	int m_uniTagSum;
	vector<int> m_biTagCNT;
	int m_biTagSum;
};

#endif /* CPT_H_ */
