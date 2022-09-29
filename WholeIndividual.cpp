#include "WholeIndividual.h"
#include <stdio.h>
#include <iostream>
using namespace std;

PartialPopulation** WholeIndividual::ppop = NULL;
PartialPopulationP** WholeIndividual::ppopP = NULL;
Dataset* WholeIndividual::dataset = NULL;

// コンストラクタ
WholeIndividual::WholeIndividual()
{
	
	int i;
	snackOrderNum = new int [dataset->snackTypeNum];
	for(i = 0; i < WCHROM_LEN; i++)
		chrom[i] = ppop[i]->pop[rand() % PPOP_SIZE];
	chromP[0] = ppopP[0]->pop[rand() % PPOP_SIZE];
	for(i = 0; i < dataset->snackTypeNum; i++) {
		snackOrderNum[i] = -1;
	}
	assortOrderNum = -1;
	fitness = DBL_MAX;
	studentList = new Student* [dataset->studentNum];
	
   	for(i = 0; i < dataset->studentNum; i++) {
		studentList[i] = new Student();
	}
}

// デストラクタ
WholeIndividual::~WholeIndividual()
{
	int i;
	delete [] snackOrderNum;
	for(i = 0; i < dataset->studentNum; i++) {
		delete studentList[i];
	}
	delete [] studentList;
}

// 次世代生成（ランダム）
void WholeIndividual::newGeneration()
{
	int i;

	for(i = 0; i < WCHROM_LEN; i++)
		chrom[i] = ppop[i]->pop[rand() % PPOP_SIZE];
	chromP[0] = ppopP[0]->pop[rand() % PPOP_SIZE];
	fitness = DBL_MAX;
}

// 次世代生成（コピー＆突然変異）
// p: コピー元個体へのポインタ
void WholeIndividual::newGeneration(WholeIndividual* p)
{
	int i;
	
	for(i = 0; i < WCHROM_LEN; i++)
		chrom[i] = p->chrom[i];
	chromP[0] = p->chromP[0];
	mutate();
	fitness = DBL_MAX;
}

// 次世代生成（２点交叉＆突然変異）
// p1: 親個体その１
// p2: 親個体その２
// index1: 交叉点（0～WCHROM_LEN-1）
// index2: 交叉点（0～WCHROM_LEN-1）
void WholeIndividual::newGeneration(WholeIndividual* p1, WholeIndividual* p2, int index1, int index2)
{
	int i, min, max;

	if(index1 < index2) {
		min = index1;
		max = index2;
	} else {
		min = index2;
		max = index1;
	}
	for(i = 0; i < min; i++)
		chrom[i] = p1->chrom[i];
	for( ; i < max; i++)
		chrom[i] = p2->chrom[i];
	for( ; i < PCHROM_LEN; i++)
		chrom[i] = p1->chrom[i];
	mutate();
	fitness = DBL_MAX;
}

// 突然変異
void WholeIndividual::mutate()
{
	int i;

	for(i = 0; i < WCHROM_LEN; i++) {
		if(rand() < MUTATE_PROBI)
			chrom[i] = ppop[i]->pop[rand() % PPOP_SIZE];
		chromP[0] = ppopP[0]->pop[rand() % PPOP_SIZE];
	}
}

// 評価
void WholeIndividual::evaluation()
{
	int i, j, k, diff;
	double subvalue, ave, sd, sqrSum;
	int a = 0;

	fitness = 0;
	for(i = 0; i < WCHROM_LEN; i++) {
		for(j = 0; j < PCHROM_LEN; j++) {
			if(chrom[i]->chrom[j] < 0) {
				fitness = WORST_VALUE;
				break;
			}
			a++;
		}
	}
	if(chromP[0]->chrom[0] < 0) {
		fitness = WORST_VALUE;
	} else {
		a++;
	}

	if(a == MAX_NUM + 1) {
		ave = 0.0;
		sqrSum = 0.0;
		for(k = 0; k < REP_NUM; k++) {
			// 初期化
			for(j = 0; j < dataset->snackTypeNum; j++) {
				snackOrderNum[j] = 0;
			}
			assortOrderNum = 0;

			// 児童の注文決定
			for(i = 0; i < dataset->studentNum; i++) {
				studentList[i]->setSnackNum((int)chromP[0]->chrom[0] + dataset->maxAmount);
				for(j = 0; j < dataset->snackTypeNum; j++) {
					snackOrderNum[j] += studentList[i]->snackOrderNum[j];
				}
				assortOrderNum += studentList[i]->assortOrderNum;
			}

			// 損失計算
			subvalue = 0;
			for(i = 0; i < WCHROM_LEN; i++) {
				for(j = 0; j < PCHROM_LEN; j++) {
					diff = snackOrderNum[i * PCHROM_LEN + j] - (int)chrom[i]->chrom[j];
					if(diff > 0) {
						subvalue += diff * (int)(dataset->snackPrice[i * PCHROM_LEN + j] * dataset->additionalRate);
					} else if(diff < 0) {
						subvalue += -diff * dataset->snackPrice[i * PCHROM_LEN + j];
					}
				}
			}
			subvalue += (int)chromP[0]->chrom[0] * assortOrderNum;
			ave += subvalue;
			sqrSum += subvalue * subvalue;
		}
		ave /= REP_NUM;
		sd = sqrt(sqrSum / REP_NUM - ave * ave);
		fitness = ave + sd;
	}
}
