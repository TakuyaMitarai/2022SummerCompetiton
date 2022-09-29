#include "PartialIndividual.h"
#include "PartialIndividualP.h"

// �R���X�g���N�^
PartialIndividualP::PartialIndividualP()
{
	chrom[0] = AID_MAX * RAND_01;
}

// �f�X�g���N�^
PartialIndividualP::~PartialIndividualP()
{

}

// ����??���i??R?????j
void PartialIndividualP::newGeneration()
{
	mutate();
	fitness = DBL_MAX;
}

// ����??���i�R�s�[��??R???j
// p: �R�s�[��?????|�C���^
void PartialIndividualP::newGeneration(PartialIndividualP* p)
{
	int i;
	
	for(i = 0; i < PCHROM_LENP; i++)
		chrom[i] = chrom[i] + (p->chrom[i] - chrom[i]) * RAND_01;
		//chrom[i] = chrom[i];
	mutate();
	fitness = DBL_MAX;
}

// ����??���i�Q�_������??R???j
// p1: �e???��?P
// p2: �e???��?Q
// index1: �����_�i0�`PCHROM_LEN-1�j
// index2: �����_�i0�`PCHROM_LEN-1�j
void PartialIndividualP::newGeneration(PartialIndividualP* p1, PartialIndividualP* p2, int index1, int index2)
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
	for( ; i < PCHROM_LENP; i++)
		chrom[i] = p1->chrom[i];
	mutate();
	fitness = DBL_MAX;
}

// ??R???
void PartialIndividualP::mutate()
{
	if(rand() < MUTATE_PROBI)
		chrom[0] = AID_MAX * RAND_01;
}
