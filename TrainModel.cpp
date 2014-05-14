/*
 * TrainModel.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: zhemin
 */

#include "TrainModel.h"
#include "Utils.h"

using namespace std;

TrainModel::TrainModel(const char* corpusFile, const char* templateFile, const char* modelFolder) {
	MyFile::makeDir(modelFolder);
	string str(modelFolder);
	str += "/";
	string save_trainCorpusFile = str + MyGlobal::g_trainFileName;
	string save_templateFile = str + MyGlobal::g_templateFileName;
	MyFile::copyFile(corpusFile, save_trainCorpusFile.c_str());
	MyFile::copyFile(templateFile, save_templateFile.c_str());
}

TrainModel::~TrainModel() {
	// TODO Auto-generated destructor stub
}
