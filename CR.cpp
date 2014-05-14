/*
 * CR.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: zhemin
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "CR.h"

using namespace std;

CR::CR() {
	m_sumCNT = 0;
}

void CR::addFeature(int fe){
	m_features.push_back(fe);
}

void CR::setCPT1(CPT* cpt1){
	m_cpt1 = cpt1;
}

void CR::setCPT2(CPT* cpt2){
	m_cpt2 = cpt2;
}

void CR::addCR(int tag, double prob){
	m_mapTagCR.insert(make_pair(tag, prob));
	m_tags.push_back(tag);
}

void CR::sortFeatures(){
	std::sort (m_features.begin(), m_features.end());
}

string CR::toString(){
	MyString str;
	int feNum = m_features.size();
	for(int i = 0; i < feNum; ++ i){
		MyString strFe(m_features[i]);
		str.join(&strFe);
		str.join(":");
	}
	return str.getString();
}

int CR::getFeatureNum(){
	return m_features.size();
}

int CR::getFeature(int i){
	return m_features[i];
}

double CR::getCR_train(int bitag, Indices* pIND){
	string strBitag = pIND->getStringBiTag(bitag);
	int tag1 = BiTag::getTag1(strBitag);
	int tag2 = BiTag::getTag2(strBitag);
	double prob1 = m_cpt1->getProb(tag1);
	double prob2 = m_cpt2->getProb(tag2);

	if(prob1 <= 0.001 || prob2 <= 0.001)
		return -1.0;

	auto iter = m_mapTagCNT.find(bitag);
	if(iter == m_mapTagCNT.end())
		return 0.0001;

	int bitagCNT = iter->second;
	return bitagCNT * 1.0 / m_sumCNT / prob1 / prob2;
}

double CR::getCR_decode(int bitag){
	auto iter = m_mapTagCR.find(bitag);
	if(iter == m_mapTagCR.end())
		return 0.0000001;
	return iter->second;
}

void CR::addTag(int bitag){
	++ m_sumCNT;
	std::tr1::unordered_map <int, int>::const_iterator iter = m_mapTagCNT.find(bitag);
	if(iter == m_mapTagCNT.end()){ //not found
		m_mapTagCNT.insert(make_pair(bitag, 1));
		m_tags.push_back(bitag);
	}else{ //found
		m_mapTagCNT[bitag] = iter->second + 1;
	}
}

vector<int>* CR::getPromisingTags(){
	return &m_tags;
}
