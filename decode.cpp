//============================================================================
// Name        : pmi-crf.cpp
// Author      : Zhemin Zhu
// Version     : 0.1
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>

#include "Template.h"
#include "Utils.h"
#include "Corpus.h"
#include "DecodeModel.h"
#include "ViterbiDecoder.h"
#include "IndexedCorpus.h"
#include "SVRLinearModel.h"
#include "Result.h"

using namespace std;

void decode(const char* modelFoler,	const char* testCorpusFile,	const char* resultFile);
void printUsage_decode();

//para1: model folder
//para2: test file
//para3: result file
int main(int argc, char **argv) {
	if(argc == 1){
		printUsage_decode();
		exit(0);
	}
	cout << "Model folder: " << argv[1] << endl;
	cout << "Test file: " << argv[2] << endl;
	cout << "Result file: " << argv[3] << endl << std::flush;
	//decode("./data/models/", "./data/ner/ner_en.testa.fe", "./data/ner/result");
	decode(argv[1], argv[2], argv[3]);
	exit(0);
}

void decode(
		const char* modelFoler,
		const char* testCorpusFile,
		const char* resultFile)
{
	DecodeModel* pDecodeModel = new SVRLinearBiProbDecodeModel(modelFoler);
	ViterbiDecoder decoder(pDecodeModel);
	IndexedCorpus* indexedTestCorpus = pDecodeModel->index(testCorpusFile);

	int sentNum = indexedTestCorpus->getSentenceNum();
	ResultCorpus rc;
	for(int i = 0; i < sentNum; ++ i){
		cout << "Sentence: " << i << endl << std::flush;
		IndexedSentence* pIS = indexedTestCorpus->getSentence(i);
		ResultSentence* rs = decoder.decode(pIS);
		rc.addResultSentence(rs);
		//rs->print();
	}
	Evaluation::accuracy(&rc, pDecodeModel);
	rc.save2File(resultFile, pDecodeModel->getIndices());
	delete indexedTestCorpus;
}

void printUsage_decode(){
	//cout << "export LD_LIBRARY_PATH=./liblinear:$LD_LIBRARY_PATH" << endl;
	cout << "Usage:\t./decode model_folder test_file result_file" << endl << std::flush;
}
