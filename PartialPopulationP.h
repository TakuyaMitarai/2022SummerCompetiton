#pragma once

#include "PartialIndividual.h"
#include "PartialIndividualP.h"

class PartialPopulationP
{
public:
	PartialPopulationP();
	~PartialPopulationP();
	void newGeneration();
	void evaluation();
	void evalinit();

	PartialIndividualP* pop[PPOP_SIZE];

private:
	void sort(int lb, int ub);
};
