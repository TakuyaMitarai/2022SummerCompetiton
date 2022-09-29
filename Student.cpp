#include "Student.h"

// static変数の初期化
Dataset* Student::dataset = NULL;

// コンストラクタ
Student::Student()
{
	int i;

	assortOrderNum = -1;
	snackOrderNum = new int [dataset->snackTypeNum];
	snackList = new int [dataset->snackTypeNum];
	for(i = 0; i < dataset->snackTypeNum; i++) {
		snackOrderNum[i] = -1;
	}
}

// デストラクタ
Student::~Student()
{
	delete [] snackOrderNum;
	delete [] snackList;
}

void Student::setSnackNum(int assortPrice)
{
	int i, listNum, residue, select;

	if(RAND_01 < 1 / (1 + exp(-0.023 * (assortPrice - dataset->maxAmount - 250))))
	   assortOrderNum = 1;
	else
	   assortOrderNum = 0;

	for(i = 0; i < dataset->snackTypeNum; i++) {
		snackOrderNum[i] = 0;
	}
	if(assortOrderNum == 0) {
		residue = dataset->maxAmount;
		do {
			listNum = 0;
			for(i = 0; i < dataset->snackTypeNum; i++) {
				if(dataset->snackPrice[i] <= residue) {
					snackList[listNum++] = i;
				}
			}
			if(listNum == 0) {
				break;
			}
			select = rand() % listNum;
			// 修正 2021/9/28
			//snackOrderNum[select]++;
			//residue -= dataset->snackPrice[select];
			snackOrderNum[snackList[select]]++;
			residue -= dataset->snackPrice[snackList[select]];
		} while(residue > 0);
	}
}
