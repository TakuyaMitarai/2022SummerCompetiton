#pragma once

#include "PartialPopulation.h"
#include "PartialPopulationP.h"

class WholeIndividual
{
public:
	static PartialPopulation** ppop;
	static PartialPopulationP** ppopP;
	static Dataset *dataset;

	WholeIndividual();
	~WholeIndividual();
	void newGeneration();
	void newGeneration(WholeIndividual* p);
	void newGeneration(WholeIndividual* p1, WholeIndividual* p2, int index1, int index2);
	void evaluation();

	PartialIndividual* chrom[WCHROM_LEN];	// ���F��
	PartialIndividualP* chromP[WCHROM_LEN];	// ���F��
	double fitness;							// �K���x

	Student **studentList;	
	int *snackOrderNum;	
	int assortOrderNum;

private:
	void mutate();
};
