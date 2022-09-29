#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "Student.h"

// 定数の定義
/*
#define GENERATION_MAX	300						// 世代交代数
#define WPOP_SIZE		400						// 全体解集団内の個体の数
#define PPOP_SIZE		400						// 部分解集団内の個体の数
#define MUTATE_PROB		0.01					// 突然変異確率
#define MUTATE_PROBI	MUTATE_PROB*RAND_MAX	// 突然変異確率×乱数の最大値
#define MAX_NUM			WCHROM_LEN*PCHROM_LEN	// フロイド問題におけるN
#define WCHROM_LEN		15						// 全体解の染色体の長さ
*/
#define PCHROM_LENP		1						// 部分解の染色体の長さ
//#define CHILDPOP		6

class PartialIndividualP
{
public:
	PartialIndividualP();
	~PartialIndividualP();
	void newGeneration();
	void newGeneration(PartialIndividualP* p);
	void newGeneration(PartialIndividualP* p1, PartialIndividualP* p2, int index1, int index2);

	int chrom[PCHROM_LENP];	// 染色体
	double fitness;			// 適応度

private:
	void mutate();
};
