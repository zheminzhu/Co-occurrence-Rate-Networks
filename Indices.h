/*
 * Indices.h
 *
 *  Created on: Mar 31, 2014
 *      Author: zhemin
 */

#ifndef INDICES_H_
#define INDICES_H_

#include <tr1/unordered_map>
#include <cstdlib>

#include "Corpus.h"
#include "IndexedCorpus.h"
#include "Utils.h"
#include "CPT.h"

using std::tr1::unordered_map;
using namespace std;

class BiTag;
class IndexedCorpus;
class Feature;

class Indices{
public:
	Indices(Corpus* pCorpus);
	~Indices();
	IndexedCorpus* index(Corpus* pCorpus);
	int getSentenceNum();
	string getStringCol(int col, int index);
	int getIntCol(int col, string str);
	string getStringTag(int index);
	int getIntTag(string str);
	string getStringBiTag(int index);
	int getIntBiTag(string str);
	int getUnigramTagNum();
	int getBigramTagNum();
	string toString();
	void print();
	int getUnigramFeatureNum();
	int getBigramFeatureNum();
	void printColCardinalities();
private:
	void buildIndices(Corpus* pCorpus);
	const char* m_corpusFile;
public:
	//column index
	MyVector<unordered_map <string, int>>* m_vecMapString2IntCol;
	MyVector<vector<string>>* m_vecMapInt2StringCol;

	//unigram tag index
	unordered_map <string, int> m_mapString2IntTag;
	vector<string> m_mapInt2StringTag;

	//bigram tag index
	unordered_map <string, int> m_mapString2IntBiTag;
	vector<string> m_mapInt2StringBiTag;

	//unigram feature index
	unordered_map<string, Feature*>* m_mapUnigramFeature;
	MyVector<Feature>* m_vecUnigramFeatures;

	//bigram feature index
	unordered_map<string, Feature*>* m_mapBigramFeature;
	MyVector<Feature>* m_vecBigramFeatures;
};

class BiTag{
public:
	static string mergeTag(MyString* first, MyString* second){
		MyString bitag;
		bitag.join(first);
		bitag.join(" ");
		bitag.join(second);
		return bitag.getString();
	}

	static MyVector<MyString>* seperate(string strBiTag){
		return MyString(strBiTag).split(' ');
	}

	static int getTag1(string strBiTag){
		MyVector<MyString>* strs = seperate(strBiTag);
		int tag1 = atoi(strs->getItem(0)->getCString());
		return tag1;
	}

	static int getTag2(string strBiTag){
		MyVector<MyString>* strs = seperate(strBiTag);
		int tag2 = atoi(strs->getItem(1)->getCString());
		return tag2;
	}

	static string mergeTag(int first, int second){
		MyString strFirst(first);
		MyString strSecond(second);
		return mergeTag(&strFirst, &strSecond);
	}
};

#endif /* INDICES_H_ */
