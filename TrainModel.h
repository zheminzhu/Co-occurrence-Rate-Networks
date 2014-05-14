/*
 * TrainModel.h
 *
 *  Created on: Mar 31, 2014
 *      Author: zhemin
 */

#ifndef TRAINMODEL_H_
#define TRAINMODEL_H_

using namespace std;

class TrainModel {
public:
	TrainModel(const char* corpusFile, const char* templateFile, const char* modelFolder);
	virtual void trainModel() = 0;
	virtual ~TrainModel();
};

#endif /* TRAINMODEL_H_ */
