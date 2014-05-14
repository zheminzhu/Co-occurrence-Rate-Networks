/*
 * CR.h
 *
 *  Created on: Mar 31, 2014
 *      Author: zhemin
 */

#ifndef CR_H_
#define CR_H_

#include "CPT.h"
#include "Indices.h"

using namespace std;

class Indices;
class CPT;

class CR{
public:
	CR();
	void addFeature(int fe);
	string toString();
	void addTag(int tag);
	double getCR_train(int tag, Indices* pIND);
	double getCR_decode(int tag);
	int getFeatureNum();
	int getFeature(int i);
	vector<int>* getPromisingTags();
	void sortFeatures();
	void setCPT1(CPT* cpt1);
	void setCPT2(CPT* cpt2);
	void addCR(int tag, double cr);
private:
	vector<int> m_features;
	std::tr1::unordered_map <int, int> m_mapTagCNT;
	std::tr1::unordered_map <int, double> m_mapTagCR;
	int m_sumCNT;
	vector<int> m_tags;
	CPT* m_cpt1;
	CPT* m_cpt2;
};

#endif /* CR_H_ */
