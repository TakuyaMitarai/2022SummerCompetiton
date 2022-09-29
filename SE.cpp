// floydSE.cpp : ���̃t�@�C���ɂ� 'main' �֐����܂܂�Ă��܂��B�v���O�������s�̊J�n�ƏI���������ōs���܂��B
//

#include "SymbioticEvolution.h"
int cnt = 0;
int cnt2 = 0;
int ppos;

// ���C�����[�`��
int main()
{
	int i, j;
	char dataFname[] = "data.csv";
	char resultFname[] = "result.csv";
	clock_t start, end;
	float comptime;
	SymbioticEvolution *se;

	// ���Ԍv���X�^�[�g
	start = clock();

	// �����̃^�l�̐ݒ�
	srand((unsigned int)time(NULL));

	// ��T��
	se = new SymbioticEvolution(dataFname);
	se->solve();

	// �������Ԍv�Z
	comptime = (float)(clock() - start) / CLOCKS_PER_SEC;

	// ���ʕ\��
	
	FILE *fp;
	fp = fopen("result.csv", "w");
	for(i = 0; i < MAX_NUM; i++) {
		printf("%d,", se->best[i]);
		fprintf(fp, "%d,", se->best[i]);
	}
	printf("%d,", se->best[i] + se->best[i] + WholeIndividual::dataset->maxAmount);
	fprintf(fp, "%d,", se->best[i] + WholeIndividual::dataset->maxAmount);
	printf("\n最良適応度%f\n", se->bestfit);
	printf("タイム%f秒\n", comptime);
	// �㏈��
	delete se;

	return 0;
}
