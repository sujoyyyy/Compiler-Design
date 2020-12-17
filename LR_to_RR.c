#include <stdio.h> //header files
#include <stdlib.h>
#include <string.h>

#define NOP 10 //number of production
#define SOP 50 //size of each production

char pro[NOP][SOP];		 //initial productions
char spro[2 * NOP][SOP]; //final solution production

int checkLR(int i) //check if left recusion exists
{
	int j;
	char nt = pro[i][0];
	for (j = 3; pro[i][j] != '\0'; j++)
		if (nt == pro[i][j] && (pro[i][j - 1] == '|' || pro[i][j - 1] == '>'))
			return (1);
	return (0);
}

void resolveLR(int i, int j) //resolve left recursion
{
	int k, l = 3, m = 4;
	char nt = pro[i][0];
	spro[j][0] = spro[j + 1][0] = nt;
	spro[j + 1][1] = '\'';
	spro[j][1] = spro[j + 1][2] = '-';
	spro[j][2] = spro[j + 1][3] = '>';
	for (k = 3; k < strlen(pro[i]);)
	{
		if (pro[i][k] == nt)
		{
			k++;
			for (; !(pro[i][k] == '|' || pro[i][k] == '\0'); k++)
				spro[j + 1][m++] = pro[i][k];
			k++;
			spro[j + 1][m++] = nt;
			spro[j + 1][m++] = '\'';
			spro[j + 1][m++] = '|';
		}
		else
		{
			if (spro[j][l - 1] != '>')
				spro[j][l++] = '|';

			for (; !(pro[i][k] == '|' || pro[i][k] == '\0'); k++)
				spro[j][l++] = pro[i][k];
			k++;
			spro[j][l++] = nt;
			spro[j][l++] = '\'';
		}
	}
	spro[j + 1][m++] = '#';
	spro[j][l] = spro[j + 1][m] = '\0';
}

int main()
{
	int i, n;
	printf("\nEnter number of productions: ");
	scanf("%d", &n);
	printf("\nEnter the production rules: \n");
	for (i = 0; i < n; i++)
	{
		printf("P%d: ", i + 1);
		scanf("%s", pro[i]);
	}
	int j = 0;
	for (i = 0; i < n; i++)
	{
		if (!checkLR(i))
			strcpy(spro[j++], pro[i]);
		else
		{
			resolveLR(i, j);
			j += 2;
		}
	}

	printf("\nProduction after removal of left recursion[IF ANY](# - epsilon):\n");
	for (i = 0; i < j; i++)
		printf("P%d: %s\n", i + 1, spro[i]);
	printf("\n");
	return 0;
}