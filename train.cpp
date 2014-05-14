/*
 * train.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: zhemin
 */

#include <iostream>

#include "Template.h"
#include "Utils.h"
#include "Corpus.h"
#include "ViterbiDecoder.h"
#include "IndexedCorpus.h"
#include "SVRLinearModel.h"
#include "Result.h"
#include "TrainModel.h"

using namespace std;

void train(const char* trainCorpusFile, const char* templateFile, const char* modelFoler);
void printUsage_train();


//para1: train file
//para2: template file
//para3: model folder
int main(int argc, char **argv) {
	if(argc == 1){
		printUsage_train();
		exit(0);
	}
	cout << "Train file: " << argv[1] << endl;
	cout << "Template file: " << argv[2] << endl;
	cout << "Model folder: " << argv[3] << endl << std::flush;
	//train("./data/ner/ner_en.train.fe", "./data/ner/svr.template", "./data/models/");
	train(argv[1], argv[2], argv[3]);
	exit(0);
}

void train(
		const char* trainCorpusFile,
		const char* templateFile,
		const char* modelFoler)
{
	//Corpus corpus(trainCorpusFile);
	TrainModel* pTrainModel = new SVRLinearBiProbTrainModel(trainCorpusFile, templateFile, modelFoler);
	pTrainModel->trainModel();
}

void printUsage_train(){
	//cout << "export LD_LIBRARY_PATH=./liblinear:$LD_LIBRARY_PATH" << endl;
	cout << "Usage:\t./train train_file template_file model_folder" << endl << std::flush;
}
