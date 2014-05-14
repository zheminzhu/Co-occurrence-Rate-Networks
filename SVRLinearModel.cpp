/*
 * SVRLinearModel.cpp
 *
 *  Created on: Apr 7, 2014
 *      Author: zhemin
 */

#include <iostream>
#include <cmath>
#include <thread>
#include <cstdio>
#include <unistd.h>

#include "SVRLinearModel.h"

using namespace std;

SVRLinearTrainModel::SVRLinearTrainModel(
		const char* trainCorpus,
		const char* templateFile,
		const char* modelFolder):TrainModel(trainCorpus, templateFile, modelFolder)
{
	Corpus courpus = Corpus(trainCorpus);
	m_indices = new Indices(&courpus);
	m_indexedCorpus = m_indices->index(&courpus);
	m_template = new Template(templateFile);
	m_modelFolder = modelFolder;
	constructParamter();
}


/*
-s type : set type of solver (default 1)
  for multi-class classification
	 0 -- L2-regularized logistic regression (primal)
	 1 -- L2-regularized L2-loss support vector classification (dual)
	 2 -- L2-regularized L2-loss support vector classification (primal)
	 3 -- L2-regularized L1-loss support vector classification (dual)
	 4 -- support vector classification by Crammer and Singer
	 5 -- L1-regularized L2-loss support vector classification
	 6 -- L1-regularized logistic regression
	 7 -- L2-regularized logistic regression (dual)
  for regression
	11 -- L2-regularized L2-loss support vector regression (primal)
	12 -- L2-regularized L2-loss support vector regression (dual)
	13 -- L2-regularized L1-loss support vector regression (dual)
-c cost : set the parameter C (default 1)
-p epsilon : set the epsilon in loss function of epsilon-SVR (default 0.1)
-e epsilon : set tolerance of termination criterion
	-s 0 and 2
		|f'(w)|_2 <= eps*min(pos,neg)/l*|f'(w0)|_2,
		where f is the primal function and pos/neg are # of
		positive/negative data (default 0.01)
	-s 11
		|f'(w)|_2 <= eps*|f'(w0)|_2 (default 0.001)
	-s 1, 3, 4 and 7
		Dual maximal violation <= eps; similar to libsvm (default 0.1)
	-s 5 and 6
		|f'(w)|_inf <= eps*min(pos,neg)/l*|f'(w0)|_inf,
		where f is the primal function (default 0.01)
	-s 12 and 13\n"
		|f'(alpha)|_1 <= eps |f'(alpha0)|,
		where f is the dual function (default 0.1)
-B bias : if bias >= 0, instance x becomes [x; bias]; if < 0, no bias term added (default -1)
-wi weight: weights adjust the parameter C of different classes (see README for details)
-v n: n-fold cross validation mode
-q : quiet mode (no outputs)

*/
//int solver_type;

/* these are for training only */
//double eps;	        /* stopping criteria */
//double C;
//int nr_weight;
//int *weight_label;
//double* weight;
//double p;

/*
#Total Accuracy: 44579/46666 = 0.955278
#OOV Accuracy: 5391/6697 = 0.804987
#non-OOV Accuracy: 39188/39969 = 0.980460
*/

//return the default parameters
void SVRLinearTrainModel::constructParamter(){
	m_param.solver_type = 12;
	m_param.C = 1.0;
	m_param.p = 0.05;
	m_param.eps = 0.0005;
	m_param.nr_weight = 0;
}

void SVRLinearBiProbTrainModel::constructCPTs(){
	m_CPTs = new CPTConstuctor(m_indexedCorpus, m_template, m_indices, false);
}

void SVRLinearCRTrainModel::constructCPTs(){
	m_CPTs = new CPTConstuctor(m_indexedCorpus, m_template, m_indices, true);
}


SVRLinearBiProbTrainModel::SVRLinearBiProbTrainModel(
		const char* trainCorpus,
		const char* templateFile,
		const char* modelFolder):SVRLinearTrainModel(trainCorpus, templateFile, modelFolder)
{
	constructCPTs();
}

SVRLinearCRTrainModel::SVRLinearCRTrainModel(
		const char* trainCorpus,
		const char* templateFile,
		const char* modelFolder):SVRLinearTrainModel(trainCorpus, templateFile, modelFolder)
{
	constructCPTs();
}

SVRLinearTrainModel::~SVRLinearTrainModel()
{
	delete m_indexedCorpus;
	delete m_template;
	delete m_CPTs;
}

void SVRLinearTrainModel::printFeatureNode(feature_node* pfn){
	int n = 0;
	MyString strPrint;
	while(true){
		int index = pfn[n].index;
		int value = pfn[n].value;
		char buff[100];
		sprintf(buff, "(%d, %d) ", index, value);
		strPrint.join(buff);
		if(index == -1)
			break;
		++ n;
	}
	cout << "#feature: " << n << endl << std::flush;
	strPrint.println();
}

void SVRLinearTrainModel::outputProblem2File(problem* problem, const char* filePath){
	int instanceNum = problem->l;
	char* buff = new char[10*1024*1024];
	int pos=0;
	for(int i = 0; i < instanceNum; ++ i){
		if(i % 100 == 0)
			cout << "Output: " << i << endl << std::flush;
		feature_node* pfn = problem->x[i];
		double target = problem->y[i];
		pos += sprintf(buff + pos, "%f ", target);
		while(pfn->index != -1){
			pos += sprintf(buff + pos, "%d:1 ", pfn->index);
			++ pfn;
		}
		pos += sprintf(buff + pos, "\n", pfn->index);
		if(pos > 10*1024*1024){
			cout << "Increase buffer size: SVRLiblinear::outputProblem2File()." << endl << std::flush;
			exit(1);
		}
	}
	MyFile::writeFile(buff, pos, filePath);
	delete[] buff;
}

char* SVRLinearTrainModel::genModelFileName(int tag, bool bUnigram){
	MyString str(m_modelFolder);
	if(bUnigram){
		str.join("U_");
		MyString att(tag);
		str.join(&att);
	}else{
		str.join("B_");
		MyString att(tag);
		str.join(&att);
	}
	str.print();

	return str.getCString();
}

void SVRLinearTrainModel::deleteProblem(problem* problem){
	int instanceNum = problem->l;
	for(int i = 0; i < instanceNum; ++ i){
		feature_node* pfn = problem->x[i];
		free(pfn);
	}

	delete problem->x;
	delete[] problem->y;
	delete problem;
}

void SVRLinearTrainModel::printProblem(problem* pProblem, int numLines){
	cout << endl << std::flush;
	int totalInstance = pProblem->l;
	cout << "#instance: " << totalInstance << endl << std::flush;
	cout << "#feature: " << pProblem->n << endl << std::flush;
	int num = std::min(totalInstance, numLines);
	for(int i = 0; i < num; ++ i){
		feature_node* pfn = pProblem->x[i];
		printFeatureNode(pfn);
	}
}

void SVRLinearTrainModel::trainModel()
{
	MyVector<CPT>* uniCPTs = m_CPTs->getUnigramCPTs();
	int numUniCPTs = uniCPTs->length();
	for(int i = 0; i < numUniCPTs; ++ i)
		uniCPTs->getItem(i)->sortFeatures();

	MyVector<CPT>* biCPTs = m_CPTs->getBigramCPTs();
	int numBiCPTs = biCPTs->length();
	for(int i = 0; i < numBiCPTs; ++ i)
		biCPTs->getItem(i)->sortFeatures();

	MyTimer timer;
	timer.start();
	vector<thread> workers;
	int numThread = 0;
	int unitagNum = m_indices->getUnigramTagNum();
	model** unigramModels = new model*[unitagNum];
	for(int uniTag = 0; uniTag < unitagNum; ++ uniTag){
		++ numThread;
		workers.push_back(thread(&SVRLinearTrainModel::trainTag, this, uniTag,
				true, &numThread, unigramModels));
		while(numThread > 4) usleep(50);
	}

	int bitagNum = m_indices->getBigramTagNum();
	model** bigramModels = new model*[bitagNum];
	for(int biTag = 0; biTag < bitagNum; ++ biTag){
		++ numThread;
		workers.push_back(thread(&SVRLinearTrainModel::trainTag, this, biTag,
				false, &numThread, bigramModels));
		while(numThread > 4) usleep(50);
	}

	for (std::thread &t: workers)
		if (t.joinable())
			t.join();
	timer.end();

	cout << "\n\nTraining finished!" << endl;
	timer.printDuration("Total training time: ");
	cout << "Saving models ..." << endl << std::flush;

	char buffer[256];
	for(int tag = 0; tag < unitagNum; ++ tag){
		sprintf(buffer, "%s%s%d", m_modelFolder, "/U_" , tag);
		model* pModel = unigramModels[tag];
		save_model(buffer, pModel);
		free_and_destroy_model(&pModel);
	}

	for(int tag = 0; tag < bitagNum; ++ tag){
		sprintf(buffer, "%s%s%d", m_modelFolder, "/B_" , tag);
		model* pModel = bigramModels[tag];
		save_model(buffer, pModel);
		free_and_destroy_model(&pModel);
	}

	cout << "Models saved to: " << m_modelFolder << endl << std::flush;
	delete[] unigramModels;
	delete[] bigramModels;
}

void SVRLinearTrainModel::trainTag(
		int tag,
		bool bUnigram,
		int* numThread,
		model** models)
{
	char buffer[256];
	if(bUnigram)
		sprintf(buffer, "\n\nTraining unigram tag:\t%d\n...", tag);
	else
		sprintf(buffer, "\n\nTraining Bigram tag:\t%d\n...", tag);

	MyString str1(buffer);
	str1.print();

	problem* prob = constructProblem(tag, bUnigram);
	struct model* pModel = train(prob, &m_param);

	deleteProblem(prob);
	models[tag] = pModel;
	-- *numThread;
}

problem* SVRLinearCRTrainModel::constructProblem(int tag, bool bUnigram){
	if(bUnigram)
		return constructProblem_uniProb(tag);
	else
		return constructProblem_CR(tag);
}

problem* SVRLinearTrainModel::constructProblem_uniProb(int tag){
	MyVector<CPT>* cpts = m_CPTs->getUnigramCPTs();
	int feNum = m_indices->getUnigramFeatureNum();

	problem* prob = new problem;
	int cptNum = cpts->length();

	feature_node** fn = static_cast<feature_node**> (::operator new (sizeof(feature_node*) * cptNum));
	double* values = new double[cptNum];

	for(int i = 0; i < cptNum; ++ i){
		CPT* cpt = cpts->getItem(i);
		int cptFeNum = cpt->getFeatureNum();
		values[i] = cpt->getProb(tag);
		feature_node* pfn = (feature_node*) malloc(sizeof(feature_node) * (cptFeNum + 1));
		*(fn + i) = pfn;
		for(int j = 0; j < cptFeNum; ++ j){
			pfn[j].index = cpt->getFeature(j) + 1;
			pfn[j].value = 1;
		}

		pfn[cptFeNum].index = -1;
		pfn[cptFeNum].value = 0;
	}

	prob->l = cptNum;
	prob->bias = -1.0;
	prob->n = feNum;
	prob->x = fn;
	prob->y = values;
	return prob;
}

problem* SVRLinearCRTrainModel::constructProblem_CR(int tag){
	MyVector<CR>* CRs = m_CPTs->getCRs();
	int feNum = m_indices->getBigramFeatureNum();
	problem* prob = new problem;
	int crNum = CRs->length();

	feature_node** fn = static_cast<feature_node**> (::operator new (sizeof(feature_node*) * crNum));
	double* values = new double[crNum];

	int crFeNum = CRs->getItem(0)->getFeatureNum();
	int crTrainNum = 0;
	for(int i = 0; i < crNum; ++ i){
		CR* cr = CRs->getItem(i);
		double value = cr->getCR_train(tag, m_indices);
		if(value < 0.0) //at least one of the unary probs is 0. CR is not defined in this case.
			//continue;
		value = 0.000001;
		values[crTrainNum] = log(value);
		feature_node* pfn = (feature_node*) malloc(sizeof(feature_node) * (crFeNum + 1));
		fn[crTrainNum] = pfn;
		for(int j = 0; j < crFeNum; ++ j){
			pfn[j].index = cr->getFeature(j) + 1;
			pfn[j].value = 1;
		}

		pfn[crFeNum].index = -1;
		pfn[crFeNum].value = 0;
		++ crTrainNum;
	}

	prob->l = crTrainNum;
	prob->bias = -1.0;
	prob->n = feNum;
	prob->x = fn;
	prob->y = values;
	return prob;
}

problem* SVRLinearBiProbTrainModel::constructProblem(int tag, bool bUnigram){
	if(bUnigram)
		return constructProblem_uniProb(tag);
	else
		return constructProblem_BiProb(tag);
}

problem* SVRLinearBiProbTrainModel::constructProblem_BiProb(int tag){
	MyVector<CPT>* cpts = 0;
	int feNum;
	cpts = m_CPTs->getBigramCPTs();
	feNum = m_indices->getBigramFeatureNum();

	problem* prob = new problem;
	int cptNum = cpts->length();  //number of training instances

	feature_node** fn = static_cast<feature_node**> (::operator new (sizeof(feature_node*) * cptNum));
	double* values = new double[cptNum];

	for(int i = 0; i < cptNum; ++ i){
		CPT* cpt = cpts->getItem(i);
		int cptFeNum = cpt->getFeatureNum();
		values[i] = cpt->getProb(tag);
		feature_node* pfn = (feature_node*) malloc(sizeof(feature_node) * (cptFeNum + 1));
		*(fn + i) = pfn;
		for(int j = 0; j < cptFeNum; ++ j){
			pfn[j].index = cpt->getFeature(j) + 1;
			pfn[j].value = 1;
		}

		pfn[cptFeNum].index = -1;
		pfn[cptFeNum].value = 0;
	}

	prob->l = cptNum;
	prob->bias = -1.0;
	prob->n = feNum;
	prob->x = fn;
	prob->y = values;
	return prob;
}

SVRLinearDecodeModel::SVRLinearDecodeModel(const char* modelFolder)
{
}

SVRLinearDecodeModel::~SVRLinearDecodeModel(){
	delete m_unigramModels;
	delete m_bigramModels;
}

void SVRLinearDecodeModel::loadModels(const char* modelFolder){
	m_unigramModels = new MyVector<model>;
	m_bigramModels = new MyVector<model>;

	//loading the unigram regression models
	int unigramTagNum = m_pIndices->getUnigramTagNum();
	for(int i = 0; i < unigramTagNum; ++ i){
		char buff[128];
		sprintf(buff, "%sU_%d", modelFolder, i);
		struct model* pModel = load_model(buff);
		m_unigramModels->push_back(pModel);
	}

	//loading the bigram regression models
	int bigramTagNum = m_pIndices->getBigramTagNum();
	for(int i = 0; i < bigramTagNum; ++ i){
		char buff[128];
		sprintf(buff, "%sB_%d", modelFolder, i);
		struct model* pModel = load_model(buff);
		m_bigramModels->push_back(pModel);
	}
}

bool SVRLinearDecodeModel::isOOV(IndexedSentence* pIS, int pos){
	CPT* cpt = m_pTemplate->extractUnigramCPT(pIS, pos, m_pIndices);
	CPT* exist_cpt = m_pCTPs->getUnigramCPT(cpt);
	if(exist_cpt == NULL)
		return true;
	return false;
}

vector<int> SVRLinearDecodeModel::getPromisingTags(IndexedSentence* pSent, int pos){
	CPT* cpt = m_pTemplate->extractUnigramCPT(pSent, pos, m_pIndices);
	cpt = m_pCTPs->getUnigramCPT(cpt);
	if(cpt != NULL){
		return *cpt->getPromisingTags();
	}else{
		m_pIndices->getUnigramTagNum();
		vector<int> vec;
		for(int i = 0; i < m_pIndices->getUnigramTagNum(); ++ i)
			vec.push_back(i);
		return vec;
	}
}

feature_node* SVRLinearDecodeModel:: constructFeatureNode(CPT* pCPT){
	int cptFeNum = pCPT->getFeatureNum();
	feature_node* pfn = (feature_node*) malloc(sizeof(feature_node) * (cptFeNum + 1));
	for(int j = 0; j < cptFeNum; ++ j){
		pfn[j].index = pCPT->getFeature(j) + 1;
		pfn[j].value = 1;
	}
	pfn[cptFeNum].index = -1;
	pfn[cptFeNum].value = 0;

	return pfn;
}

SVRLinearBiProbDecodeModel::SVRLinearBiProbDecodeModel(
		const char* modelFolder):SVRLinearDecodeModel(modelFolder)
{
	string str(modelFolder);
	string trainCorpusFile = str + MyGlobal::g_trainFileName;
	string templateFile = str + MyGlobal::g_templateFileName;
	m_pTemplate = new Template(templateFile.c_str());
	Corpus* pTrainCorpus = new Corpus(trainCorpusFile.c_str());
	m_pIndices = new Indices(pTrainCorpus);
	IndexedCorpus* pIC = m_pIndices->index(pTrainCorpus);
	delete pTrainCorpus;
	m_pCTPs = new CPTConstuctor(pIC, m_pTemplate, m_pIndices, false);
	loadModels(modelFolder);
}

double SVRLinearBiProbDecodeModel::getUnigramProb(IndexedSentence* pSent, int pos, int tag){
	CPT* cpt = m_pTemplate->extractUnigramCPT(pSent, pos, m_pIndices);
	CPT* exist_cpt = m_pCTPs->getUnigramCPT(cpt);
	if(exist_cpt != NULL){
		delete cpt;
		return exist_cpt->getProb(tag);
	}else{
		string strCPT = cpt->toString();
		auto iter = m_mapOOVUnigramCPT.find(strCPT);
		if(iter != m_mapOOVUnigramCPT.end()){
			return iter->second->getProb(tag);
		}else{
			m_mapOOVUnigramCPT.insert(std::make_pair(strCPT, cpt));
			predictUnigramCPT(cpt);
			return cpt->getProb(tag);
		}
	}
}

double sigmoid(double t, double a){
	return 1 / (1 + exp(-t * a));
}

double SVRLinearBiProbDecodeModel::getCR(IndexedSentence* pSent, int pos, int preTag, int curTag){
	CPT* bicpt = m_pTemplate->extractBigramCPT(pSent, pos, m_pIndices);
	//bicpt->sortFeatures();
	CPT* exist_bicpt = m_pCTPs->getBigramCPT(bicpt);
	int biTag = m_pIndices->getIntBiTag(BiTag::mergeTag(preTag, curTag));
	if(exist_bicpt != NULL){
		delete bicpt;
		double preProb = getUnigramProb(pSent, pos - 1, preTag);
		double curProb = getUnigramProb(pSent, pos, curTag);
		double biProb = exist_bicpt->getProb(biTag);
		if(preProb < 0.01 || curProb < 0.01)
			return 0.000001;
		return biProb / preProb / curProb;
	}else{
		double preProb = getUnigramProb(pSent, pos - 1, preTag);
		double curProb = getUnigramProb(pSent, pos, curTag);
		double biProb;
		if(preProb < 0.01 || curProb < 0.01)
			return 0.000001;
		auto iter = m_mapOOVBigramCPT.find(bicpt->toString());
		if(iter != m_mapOOVBigramCPT.end()){
			biProb = iter->second->getProb(biTag);
		}else{
			m_mapOOVBigramCPT.insert(std::make_pair(bicpt->toString(), bicpt));
			predictBigramCPT(bicpt);
			biProb = bicpt->getProb(biTag);
		}
		double result = biProb / pow(preProb,0.1) / pow(curProb, 0.1);
		return result;
	}
}

void SVRLinearBiProbDecodeModel::predictUnigramCPT(CPT* pCPT){
	int tagNum = m_unigramModels->length();
	feature_node* pfn = constructFeatureNode(pCPT);
	//SVRLiblinear::printFeatureNode(pfn);
	for(int i = 0; i < tagNum; ++ i){
		model* pModel = m_unigramModels->getItem(i);
		double prob = predict(pModel, pfn);
		pCPT->addProb(i, prob);
	}
	pCPT->normalizeProb();
	free(pfn);
}

void SVRLinearBiProbDecodeModel::predictBigramCPT(CPT* pCPT){
	int tagNum = m_bigramModels->length();
	feature_node* pfn = constructFeatureNode(pCPT);
	//SVRLiblinear::printFeatureNode(pfn);
	for(int i = 0; i < tagNum; ++ i){
		model* pModel = m_bigramModels->getItem(i);
		double prob = predict(pModel, pfn);
		//cout << prob << endl << std::flush;
		pCPT->addProb(i, prob);
	}
	pCPT->normalizeProb();
	free(pfn);
}

SVRLinearCRDecodeModel::SVRLinearCRDecodeModel(
		const char* modelFolder):SVRLinearDecodeModel(modelFolder)
{
	string str(modelFolder);
	string trainCorpusFile = str + MyGlobal::g_trainFileName;
	string templateFile = str + MyGlobal::g_templateFileName;
	m_pTemplate = new Template(templateFile.c_str());
	Corpus* pTrainCorpus = new Corpus(trainCorpusFile.c_str());
	m_pIndices = new Indices(pTrainCorpus);
	IndexedCorpus* pIC = m_pIndices->index(pTrainCorpus);
	delete pTrainCorpus;
	m_pCTPs = new CPTConstuctor(pIC, m_pTemplate, m_pIndices, true);
	loadModels(modelFolder);
}

double SVRLinearCRDecodeModel::getUnigramProb(IndexedSentence* pSent, int pos, int tag){
	CPT* cpt = m_pTemplate->extractUnigramCPT(pSent, pos, m_pIndices);
	CPT* exist_cpt = m_pCTPs->getUnigramCPT(cpt);
	if(exist_cpt != NULL){
		delete cpt;
		return exist_cpt->getProb(tag);
	}else{
		string strCPT = cpt->toString();
		auto iter = m_mapOOVUnigramCPT.find(strCPT);
		if(iter != m_mapOOVUnigramCPT.end()){
			return iter->second->getProb(tag);
		}else{
			m_mapOOVUnigramCPT.insert(std::make_pair(strCPT, cpt));
			predictUnigramCPT(cpt);
			return cpt->getProb(tag);
		}
	}
}

double SVRLinearCRDecodeModel::getCR(IndexedSentence* pSent, int pos, int preTag, int curTag){
	int biTag = m_pIndices->getIntBiTag(BiTag::mergeTag(preTag, curTag));
	if(biTag < 0)
		return 0.0000001;
	CR* bicr = m_pTemplate->extractCR(pSent, pos, m_pIndices);
	CR* exist_cr = m_pCTPs->getCR(bicr);
	if(exist_cr != NULL){
		//return 1.0;
		delete bicr;
		double cr = exist_cr->getCR_train(biTag, m_pIndices);
		if(cr < 0.0)
			return 0.000001;
		return cr;
	}else{
		//return 1.0;

		double prob1 = getUnigramProb(pSent, pos - 1, preTag);
		double prob2 = getUnigramProb(pSent, pos, curTag);

		if(prob1 < 0.001 || prob2 < 0.001)
			return 0.000001;

		double cr = 0.0;
		auto iter = m_mapOOVCR.find(bicr->toString());
		if(iter != m_mapOOVCR.end()){
			cr = iter->second->getCR_decode(biTag);
		}else{
			m_mapOOVCR.insert(std::make_pair(bicr->toString(), bicr));
			predictCR(bicr);
			cr = bicr->getCR_decode(biTag);
		}
		return exp(cr);
	}
}

void SVRLinearCRDecodeModel::predictUnigramCPT(CPT* pCPT){
	int tagNum = m_unigramModels->length();
	feature_node* pfn = constructFeatureNode(pCPT);
	for(int i = 0; i < tagNum; ++ i){
		model* pModel = m_unigramModels->getItem(i);
		double prob = predict(pModel, pfn);
		pCPT->addProb(i, prob);
	}
	pCPT->normalizeProb();
	free(pfn);
}

void SVRLinearCRDecodeModel::predictCR(CR* pCR){
	int tagNum = m_bigramModels->length();
	feature_node* pfn = constructFeatureNodeCR(pCR);
	//SVRLiblinear::printFeatureNode(pfn);
	for(int i = 0; i < tagNum; ++ i){
		model* pModel = m_bigramModels->getItem(i);
		double cr = predict(pModel, pfn);
		//if(cr <= 0)
			//cr = 0.0000001;
		//cout << prob << endl << std::flush;
		pCR->addCR(i, cr);
	}
	free(pfn);
}

feature_node* SVRLinearCRDecodeModel:: constructFeatureNodeCR(CR* pCR){
	int crFeNum = pCR->getFeatureNum();
	feature_node* pfn = (feature_node*) malloc(sizeof(feature_node) * (crFeNum + 1));
	for(int j = 0; j < crFeNum; ++ j){
		pfn[j].index = pCR->getFeature(j) + 1;
		pfn[j].value = 1;
	}
	pfn[crFeNum].index = -1;
	pfn[crFeNum].value = 0;
	return pfn;
}
