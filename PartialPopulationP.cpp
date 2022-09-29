#include "PartialPopulationP.h"

// コンストラクタ
PartialPopulationP::PartialPopulationP()
{
	int i;

	for(i = 0; i < PPOP_SIZE; i++)
		pop[i] = new PartialIndividualP();
}

// デストラクタ
PartialPopulationP::~PartialPopulationP()
{
	int i;

	for(i = 0; i < PPOP_SIZE; i++)
		delete pop[i];
}

// 次世代生成
void PartialPopulationP::newGeneration()
{
	int i, j, a, index1, index2;
	
	for(i = PPOP_SIZE / 4 * 3, j = 0; i < PPOP_SIZE; i += 2, j++) {
		a = ((rand() % (PPOP_SIZE / 4 - 1)) + j) % (PPOP_SIZE / 4);
		pop[i]->newGeneration(pop[a]);
	}
	for(i = 0; i < PPOP_SIZE / 4 * 3; i++)
		pop[i]->newGeneration();
}

// 評価
void PartialPopulationP::evaluation()
{
	sort(0, PPOP_SIZE - 1);
}

// 評価値初期化
void PartialPopulationP::evalinit()
{
	int i;
	
	for(i = 0; i < PPOP_SIZE; i++)
		pop[i]->fitness = DBL_MAX;
}

// popをfitnessの値によって昇順にソート（クイックソート）
// lb : ソートするpopの範囲の最小インデックス
// rb : ソートするpopの範囲の最大インデックス
void PartialPopulationP::sort(int lb, int ub)
{
	int i, j, k;
	double pivot;
	PartialIndividualP* swap;

	if(lb < ub) {
		k = (lb + ub) / 2;
		pivot = pop[k]->fitness;
		i = lb;
		j = ub;
		do {
			while(pop[i]->fitness < pivot)
				i++;
			while(pop[j]->fitness > pivot)
				j--;
			if(i <= j) {
				swap = pop[i];
				pop[i] = pop[j];
				pop[j] = swap;
				i++;
				j--;
			}
		} while(i <= j);
		sort(lb, j);
		sort(i, ub);
	}
}