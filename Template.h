/*
 * Template.h
 *
 *  Created on: Feb 26, 2014
 *      Author: zhemin
 */

#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "Utils.h"
#include "CPT.h"
#include "CR.h"
#include "IndexedCorpus.h"
#include "Indices.h"

using namespace std;

class Item;
class Feature;
class CPT;
class IndexedSentence;
class Indices;
class CR;

class ItemTemplate{
public:
	ItemTemplate(MyString* pStr);
	MyString* toString();
	void print();
	Item* extractItem(IndexedSentence* pIS, int pos);
private:
	int m_iPos;
	int m_iCol;
};

class FeatureTemplate{
public:
	FeatureTemplate(MyString* pLine);
	MyString* toString();
	void print();
	~FeatureTemplate();
	Feature* extractFeature(IndexedSentence* pIS, int pos);
	int getItemTemplateNum();
private:
	MyVector<ItemTemplate>* m_vecIT;
	MyString* m_ID;
	bool m_bUnigram;
};

class Template{
public:
	Template(const char* pTemplateFilePath);
	MyString* toString();
	void print();
	~Template();
	CPT* extractUnigramCPT(IndexedSentence* pIS, int pos, Indices* ind);
	CPT* extractBigramCPT(IndexedSentence* pIS, int pos, Indices* ind);
	CR* extractCR(IndexedSentence* pIS, int pos, Indices* ind);
private:
	MyVector<FeatureTemplate>* m_vecUnigramFT;
	MyVector<FeatureTemplate>* m_vecBigramFT;

};

#endif /* TEMPLATE_H_ */
