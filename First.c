#include <stdio.h>
#include <string.h>

//PRODUCTION DETAILS - count 	
// productions		
// non-terminals
// terminals
int prodCount;
char prod[30][30];
char nt[10];
char unique_nt[10];
char t[10];

char first[20];
int f_count;

void First(char c, int hop, int flag);
void removeDuplicate();

int prev_row, prev_col; // it will store row & col of previous called First()
int nt_count;

void removeDuplicate()
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

void First(char c, int hop, int flag)
{
	int i, j;
	char res[20];
	int prodIndex = 0;

	if (c != '#')
	{
		for (i = 0; i < prodCount; i++)
		{
			if (prod[i][0] == c) 
			//checks if non-terminal symbol
			{
				prodIndex = i;
				hop = 0;
				if (i == 0)
					First(prod[prodIndex][3 + hop], hop, 0);
				else
					First(prod[prodIndex][3 + hop], hop, 1);
				prev_row = prodIndex;
				prev_col = 3 + hop;
			}
			else 
			// if terminal
			{
				if (!strchr(first, c) && !strchr(unique_nt, c)) 
				// if not already in set & not a Non-Terminal
				{
					first[f_count] = c;
					f_count++;
				}
			}
		}
	}

	else if (flag == 1) // if it is indirect null from the first of other variables
	{
		if (!strchr(first, c))
		{
			first[f_count] = c;
			f_count++;
		}
		hop++;
		prev_col = prev_col + hop;
		char d = prod[prev_row][prev_col + 3];
		First(d, hop, 1);
	}

	else // if it is direct null of Starting variable
	{
		hop++;
		prev_col = prev_col + hop;
		char d = prod[prev_row][prev_col + 3];
		First(d, hop, 1);
	}
}

int main()
{
	int i, j = 0, flag = 0;
	f_count = 0;
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

	removeDuplicate();
	printf("\n");

	for (int k = 0; k < nt_count; k++)
	{
		First(unique_nt[k], 0, 0);
		printf("First of %c is {", unique_nt[k]);

		for (i = 0; i < f_count; i++)
		{
			if (k == 0 && first[i] == '#')
				continue;
			else
				printf(" %c", first[i]);
		}

		printf(" }\n");
		memset(first, 0, 20);
		f_count = 0;
	}

	printf(" \n");

	return 0;
}
