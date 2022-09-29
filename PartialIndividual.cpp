#include "PartialIndividual.h"
#include "SymbioticEvolution.h"
#include <iostream>
using namespace std;
extern int cnt2;
extern int ppos;

// �R���X�g���N�^
PartialIndividual::PartialIndividual()
{
	int i;
	int j = 0;
	//cout << cnt2 * PCHROM_LEN << endl;
	//cout <<  WholeIndividual::dataset->maxAmount << " " << WholeIndividual::dataset->snackPrice[i] << " " << WholeIndividual::dataset->studentNum << " " << RAND_01 << endl;
   	for(i = cnt2 * PCHROM_LEN; i < cnt2 * PCHROM_LEN + PCHROM_LEN; i++) {
		chrom[j] = WholeIndividual::dataset->maxAmount / WholeIndividual::dataset->snackPrice[i] * WholeIndividual::dataset->studentNum * RAND_01;
		//cout << chrom[j] << endl;
		j++;
	}
}

// �f�X�g���N�^
PartialIndividual::~PartialIndividual()
{
}

// ����??���i??R?????j
void PartialIndividual::newGeneration()
{
	mutate();
	fitness = DBL_MAX;
}

// ����??���i�R�s�[��??R???j
// p: �R�s�[��?????|�C���^
void PartialIndividual::newGeneration(PartialIndividual* p)
{
	int i;
	
	for(i = 0; i < PCHROM_LEN; i++)
		chrom[i] = p->chrom[i];
	mutate();
	fitness = DBL_MAX;
}

// ����??���i�Q�_������??R???j
// p1: �e???��?P
// p2: �e???��?Q
// index1: �����_�i0�`PCHROM_LEN-1�j
// index2: �����_�i0�`PCHROM_LEN-1�j
void PartialIndividual::newGeneration(PartialIndividual* p1, PartialIndividual* p2, int index1, int index2)
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
	for( ; i < max; i++){
		double r = RAND_01;
		chrom[i] = p2->chrom[i];
	}
	for( ; i < PCHROM_LEN; i++)
		chrom[i] = p1->chrom[i];
	mutate();
	fitness = DBL_MAX;
}

// ??R???
void PartialIndividual::mutate()
{
	int i;
	int j = 0;
	for(i = ppos * PCHROM_LEN; i < (ppos + 1) * PCHROM_LEN; i++) {
		if(rand() < MUTATE_PROBI)
			chrom[j] = WholeIndividual::dataset->maxAmount / WholeIndividual::dataset->snackPrice[i] * WholeIndividual::dataset->studentNum * RAND_01;
		j++;
	}
}
