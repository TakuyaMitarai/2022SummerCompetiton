#pragma once

#include "WholePopulation.h"

class SymbioticEvolution
{
public:
	SymbioticEvolution(char *fileName);
	~SymbioticEvolution();
	void solve();

	int best[MAX_NUM + 1];
	double bestfit;

	Dataset *dataset;
	WholePopulation* wpop;
	PartialPopulation* ppop[WCHROM_LEN];
	PartialPopulationP* ppopP[PCHROM_LENP];
};
