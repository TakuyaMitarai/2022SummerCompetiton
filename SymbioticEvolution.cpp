#include "SymbioticEvolution.h"
extern int cnt2;
extern int ppos;

// コンストラクタ
SymbioticEvolution::SymbioticEvolution(char *fileName)
{
	dataset = new Dataset(fileName);
	WholeIndividual::dataset = dataset;
	Student::dataset = dataset;
	int i, j;

	// 初期集団生成
	
	for(i = 0; i < WCHROM_LEN; i++){
		cnt2 = i;
		ppop[i] = new PartialPopulation();
	}
	ppopP[0] = new PartialPopulationP();
	WholeIndividual::ppop = ppop;
	WholeIndividual::ppopP = ppopP;
	
	
	wpop = new WholePopulation();
	wpop->evaluation();
	for(i = 0; i < WCHROM_LEN; i++)
		ppop[i]->evaluation();
	ppopP[0]->evaluation();
	// 最適解初期化
	bestfit = wpop->pop[0]->fitness;
	for(i = 0; i < WCHROM_LEN; i++) {
		for(j = 0; j < PCHROM_LEN; j++)
			best[i*PCHROM_LEN+j] = wpop->pop[0]->chrom[i]->chrom[j];
	}
	best[MAX_NUM] = wpop->pop[0]->chromP[0]->chrom[0];
	printf("初期世代\t最良個体の適応度は%f\n", bestfit);
}

// デストラクタ
SymbioticEvolution::~SymbioticEvolution()
{
	int i;

	for(i = 0; i < WCHROM_LEN; i++)
		delete ppop[i];
	delete ppopP[0];
	delete wpop;
}

// 進化
void SymbioticEvolution::solve(void)
{
	int gen, i, j;

	for(gen = 1; gen <= GENERATION_MAX; gen++) {
		// 次世代生成
		for(i = 0; i < WCHROM_LEN; i++) {
			ppos = i;
			ppop[i]->newGeneration();
		}
		ppopP[0]->newGeneration();
		wpop->newGeneration();
		// 評価
		for(i = 0; i < WCHROM_LEN; i++)
			ppop[i]->evalinit();
		ppopP[0]->evalinit();
		wpop->evaluation();
		for(i = 0; i < WCHROM_LEN; i++)
			ppop[i]->evaluation();
		ppopP[0]->evaluation();
		// 最適解更新
		if(wpop->pop[0]->fitness < bestfit) {
			bestfit = wpop->pop[0]->fitness;
			for(i = 0; i < WCHROM_LEN; i++) {
				for(j = 0; j < PCHROM_LEN; j++)
					best[i*PCHROM_LEN+j] = wpop->pop[0]->chrom[i]->chrom[j];
			}
			best[MAX_NUM] = wpop->pop[0]->chromP[0]->chrom[0];
			printf("第%d世代\t最良個体の適応度は%f\n", gen, bestfit);
		}
		
	}
}
