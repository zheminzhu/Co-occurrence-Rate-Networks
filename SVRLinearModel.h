/*
 * SVRLinearModel.h
 *
 *  Created on: Apr 7, 2014
 *      Author: zhemin
 */

#ifndef SVRLINEARMODEL_H_
#define SVRLINEARMODEL_H_

#include "liblinear.h"
#include "TrainModel.h"
#include "DecodeModel.h"
#include "IndexedCorpus.h"
#include "Template.h"
#include "CPT.h"
#include "Utils.h"

using namespace std;

class SVRLinearTrainModel: public TrainModel{
public:
	SVRLinearTrainModel(const char* corpusFile, const char* templateFile, const char* modelFolder);
	~SVRLinearTrainModel();
	void trainModel();
	static void printFeatureNode(feature_node* pfn);
	void outputProblem2File(problem* problem, const char* filePath);
protected:
	void trainTag(int tag, bool bUnigram, int* numThread, model** models);
	void constructParamter();
	char* genModelFileName(int tag, bool bUnigram);
	void deleteProblem(problem* problem);
	void printProblem(problem* pProblem, int numLines);
	virtual void constructCPTs() = 0;
	virtual problem* constructProblem(int tag, bool bUnigram) = 0;
	problem* constructProblem_uniProb(int tag);
protected:
	Indices* m_indices;
	IndexedCorpus* m_indexedCorpus;
	Template* m_template;
	CPTConstuctor* m_CPTs;
	struct parameter m_param;
	const char* m_modelFolder;
};

class SVRLinearBiProbTrainModel: public SVRLinearTrainModel {
public:
	SVRLinearBiProbTrainModel(const char* corpusFile, const char* templateFile, const char* modelFolder);
protected:
	problem* constructProblem(int tag, bool bUnigram);
	void constructCPTs();
private:
	problem* constructProblem_BiProb(int tag);
};

class SVRLinearCRTrainModel: public SVRLinearTrainModel {
public:
	SVRLinearCRTrainModel(const char* corpusFile, const char* templateFile, const char* modelFolder);
protected:
	problem* constructProblem(int tag, bool bUnigram);
	void constructCPTs();
private:
	problem* constructProblem_CR(int tag);
};













class SVRLinearDecodeModel: public DecodeModel{
public:
	SVRLinearDecodeModel(const char* modelFolder);
	virtual ~SVRLinearDecodeModel();
	vector<int> getPromisingTags(IndexedSentence* pSent, int pos);
	bool isOOV(IndexedSentence* pIS, int pos);
protected:
	void loadModels(const char* modelFolder);
	feature_node* constructFeatureNode(CPT* pCPT);
	MyVector<model>* m_unigramModels;
	MyVector<model>* m_bigramModels;
	std::tr1::unordered_map<string, CPT*> m_mapOOVUnigramCPT;
};

class SVRLinearBiProbDecodeModel: public SVRLinearDecodeModel{
public:
	SVRLinearBiProbDecodeModel(const char* modelFolder);
	double getUnigramProb(IndexedSentence* pSent, int pos, int tag);
	double getCR(IndexedSentence* pSent, int pos, int preTag, int curTag);
private:
	void predictUnigramCPT(CPT* pCPT);
	void predictBigramCPT(CPT* pCPT);
	std::tr1::unordered_map<string, CPT*> m_mapOOVBigramCPT;
};

class SVRLinearCRDecodeModel: public SVRLinearDecodeModel{
public:
	SVRLinearCRDecodeModel(const char* modelFolder);
	double getUnigramProb(IndexedSentence* pSent, int pos, int tag);
	double getCR(IndexedSentence* pSent, int pos, int preTag, int curTag);
private:
	void predictUnigramCPT(CPT* pCPT);
	void predictCR(CR* pCR);
	feature_node* constructFeatureNodeCR(CR* pCR);
	std::tr1::unordered_map<string, CR*> m_mapOOVCR;
};

#endif /* SVRLINEARMODEL_H_ */
