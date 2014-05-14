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
#include "TrainModel.h"
#include "ViterbiDecoder.h"
#include "IndexedCorpus.h"
#include "SVRLinearModel.h"
#include "Result.h"

using namespace std;

void train(const char* trainCorpusFile, const char* templateFile, const char* modelFoler);
void decode(const char* modelFoler,	const char* testCorpusFile,	const char* resultFile);

/* no bife0
 * All Known Unknown Prec. Rec. F1
   PMI-CRF 97.37 98.80 84.34   ner.testa
 */

/* testa no bife 0
#Total Accuracy: 50091/51578 = 0.971170
#OOV Accuracy: 4288/5082 = 0.843762
#non-OOV Accuracy: 45803/46496 = 0.985095
*/

/* testb no bife 0
#Total Accuracy: 44611/46666 = 0.955964
#OOV Accuracy: 5474/6697 = 0.817381
#non-OOV Accuracy: 39137/39969 = 0.979184
*/

/* testa with bife 0
#Total Accuracy: 50232/51578 = 0.973904
#OOV Accuracy: 4292/5082 = 0.844549
#non-OOV Accuracy: 45940/46496 = 0.988042
*/

/* testb with bife 0
#Total Accuracy: 44583/46666 = 0.955364
#OOV Accuracy: 5400/6697 = 0.806331
#non-OOV Accuracy: 39183/39969 = 0.980335
*/

/*
#Total Accuracy: 44438/46666 = 0.952256
#OOV Accuracy: 5283/6697 = 0.788861
#non-OOV Accuracy: 39155/39969 = 0.979634
 */

//125s

/* testa CR
#Total Accuracy: 50173/51578 = 0.972760
#OOV Accuracy: 4283/5082 = 0.842778
#non-OOV Accuracy: 45890/46496 = 0.986967
*/

/* testb CR
#Total Accuracy: 44471/46666 = 0.952964
#OOV Accuracy: 5368/6697 = 0.801553
#non-OOV Accuracy: 39103/39969 = 0.978333
*/



/* BiProb without f0 testa
#Total Accuracy: 50091/51578 = 0.971170
#OOV Accuracy: 4288/5082 = 0.843762
#non-OOV Accuracy: 45803/46496 = 0.985095
*/

/* BiProb without f0 testb
#Total Accuracy: 44611/46666 = 0.955964
#OOV Accuracy: 5474/6697 = 0.817381
#non-OOV Accuracy: 39137/39969 = 0.979184
*/

/* BiProb with f0 testa
#Total Accuracy: 50232/51578 = 0.973904
#OOV Accuracy: 4292/5082 = 0.844549
#non-OOV Accuracy: 45940/46496 = 0.988042
*/

/* BiProb with f0 testb
#Total Accuracy: 44581/46666 = 0.955321
#OOV Accuracy: 5399/6697 = 0.806182
#non-OOV Accuracy: 39182/39969 = 0.980310
*/


/*CRF testa with F0
 * Total Tags: 51578	 Correct Tag: 50033	 Precision: 0.9700453681802319
Total Sentences: 3466	 Correct Sentences: 2664	 Precision: 0.7686093479515291
Total Unkowns: 5082	 Correct Unkowns: 4341	 Precision: 0.8541912632821723
Total Knowns: 46496	 Correct Knowns: 45692	 Precision: 0.9827081899518239
 *
 *CRF testb with F0
 Total Tags: 46666	 Correct Tag: 44332	 Precision: 0.9499849997857113
Total Sentences: 3684	 Correct Sentences: 2538	 Precision: 0.6889250814332247
Total Unkowns: 6697	 Correct Unkowns: 5379	 Precision: 0.8031954606540241
Total Knowns: 39969	 Correct Knowns: 38953	 Precision: 0.9745802997322925

 *CRF testa without F0
 *Total Tags: 51578	 Correct Tag: 49976	 Precision: 0.9689402458412502
Total Sentences: 3466	 Correct Sentences: 2636	 Precision: 0.760530871321408
Total Unkowns: 5082	 Correct Unkowns: 4351	 Precision: 0.8561589925226288
Total Knowns: 46496	 Correct Knowns: 45625	 Precision: 0.9812672057811425

 *CRF testb without F0
Total Tags: 46666	 Correct Tag: 44395	 Precision: 0.951335019071701
Total Sentences: 3684	 Correct Sentences: 2554	 Precision: 0.6932681867535287
Total Unkowns: 6697	 Correct Unkowns: 5422	 Precision: 0.8096162460803344
Total Knowns: 39969	 Correct Knowns: 38973	 Precision: 0.9750806875328379
 */

/*
#Total Accuracy: 50192/51578 = 0.973128
#OOV Accuracy: 4293/5082 = 0.844746
#non-OOV Accuracy: 45899/46496 = 0.987160
*/

int main() {
	train("./data/ner/ner_en.train.fe", "./data/ner/svr.template", "./data/models/");
	decode("./data/models/", "./data/ner/ner_en.testb.fe", "./data/ner/result");
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

void train(
		const char* trainCorpusFile,
		const char* templateFile,
		const char* modelFoler)
{
	Corpus corpus(trainCorpusFile);
	TrainModel* pTrainModel = new SVRLinearBiProbTrainModel(trainCorpusFile, templateFile, modelFoler);
	pTrainModel->trainModel();
}
