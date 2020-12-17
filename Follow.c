#include <stdio.h>
#include <string.h>

//PRODUCTION DETAILS - count 	productions		non-terminals	terminals
int prodCount;
char prod[30][30];
char nt[10];
char unique_nt[10];
char t[10];

char first[20];
int fir_count;
char follow[20];
int fol_count;

int firstForFollow(char c, int hop);
void removeDuplicate_first();
void removeDuplicate_follow();
void Follow(char c);

int prevr, prevc; // it will store row & col of previous called first()
int nt_count;

void removeDuplicate_first()
{
	int index = 0;

	for (int i = 0; i < nt_count; i++)
	{

		int j;
		for (j = 0; j < i; j++)
			if (nt[i] == nt[j])
				break;

		if (j == i)
			unique_nt[index++] = nt[i];
	}
	nt_count = index;
}

void removeDuplicate_follow()
{
	for (int i = 0; i < strlen(follow); i++)
	{
		for (int j = i + 1; follow[j] != '\0'; j++)
		{
			if (follow[j] == follow[i])
			{
				for (int k = j; follow[k] != '\0'; k++)
				{
					follow[k] = follow[k + 1];
				}
			}
		}
	}
}

void Follow(char c)
{
	int i, j;
	for (i = 0; i < prodCount; i++)
	{
		for (j = 3; prod[i][j] != '\0'; j++)
		{
			if (prod[i][j] == c)
			{
				if (prod[i][j + 1] != '\0') // if its not at last of production
				{
					int hop = 1;
					while (1 > 0)
					{
						int nu = firstForFollow(prod[i][j + hop], 0);
						if (nu == 1)
							hop = hop + 1;
						else
							break;
					}
					strcat(follow, first);
				}
				else
				{
					Follow(prod[i][0]); // if its last,then find Follow of LHS
				}
			}
		}
	}

	if (prod[0][0] == c)
	{
		if (!strchr(first, '$'))
		{
			strcat(follow, "$");
			fol_count++;
		}
	}
}

int firstForFollow(char c, int hop)
{
	int i, j;
	int nu = 0; // nu = 1 when first contains #
	int prodIndex = 0;
	if (c != '#') // not a null
	{
		for (i = 0; i < prodCount; i++)
		{
			if (prod[i][0] == c) //checks if non-terminal symbol
			{
				prodIndex = i;
				hop = 0;
				firstForFollow(prod[prodIndex][3 + hop], hop);
				prevr = prodIndex;
				prevc = 3 + hop;
			}
			else // if terminal
			{
				if (!strchr(first, c) && !strchr(nt, c)) // if not already in set & not a Non-Terminal
				{
					char x[] = "";
					x[0] = c;
					strcat(first, x);
				}
			}
		}
	}
	else // is null
	{
		nu = 1;
		hop++;
		prevc = prevc + hop;
		char d = prod[prevr][prevc + 3];
		firstForFollow(d, hop);
	}
	return nu;
}

int main()
{
	int i, j = 0;
	printf("\nRULES: \n\t1: If there are multiple entries in same production, split and enter.\n\t\tS->A|B == S->A and S->B\n\n\t2: Epsilon is '#'\n");

	printf("\nEnter number of productions: ");
	scanf("%d", &prodCount);
	printf("\n");

	for (i = 0; i < prodCount; i++)
	{
		printf("Enter production %d:  ", i);
		scanf("%s", prod[i]);
		nt[nt_count] = prod[i][0];
		nt_count++;
	}
	printf("\n");
	removeDuplicate_first();

	for (int k = 0; k < nt_count; k++)
	{
		Follow(unique_nt[k]);

		printf("Follow of %c is {", unique_nt[k]);
		removeDuplicate_follow();
		for (i = 0; i < strlen(follow); i++)
		{
			printf(" %c", follow[i]);
		}
		printf(" }\n");

		memset(follow, 0, 20);
		fol_count = 0;
	}
	printf(" \n");
	return 0;
}
