#include <stdio.h>
#include <string.h>
#define SIZE 10

int main()
{
	char non_terminal;
	char beta, alpha;
	int num;
	char production[10][SIZE];
	int index = 3; // starting of the string following "->"

	printf("\nEnter Number of Productions : ");
	scanf("%d", &num);

	printf("\nEnter the grammar as E->E-A|a :\n");

	for (int i = 0; i < num; i++)
		scanf("%s", production[i]);

	for (int i = 0; i < num; i++)
	{
		int main_flag = 0;
		printf("\nGRAMMAR : : : %s", production[i]);
		non_terminal = production[i][0];

		if (non_terminal == production[i][index])
		{
			printf(" is left recursive.\n");
			main_flag = 1;
			continue;
		}

		while (1)
		{
			if (production[i][index + 1] == '\0')
				break;
			if (production[i][index] == '|')
			{
				if (production[i][index + 1] == non_terminal)
				{
					printf(" is left recursive.\n");
					main_flag = 1;
					break;
				}
			}
			index++;
		}

		if (main_flag == 0)
		{
			int flag = 0;
			index = 0;
			while (1)
			{
				if ((production[i][index + 1] == '|' || production[i][index + 1] == '\0'))
				{
					if (production[i][index] == non_terminal)
					{
						printf(" is right recursive.\n");
						flag = 1;
						break;
					}
					if (production[i][index + 1] == '\0')
						break;
				}
				index++;
			}
			if (flag == 0)
				printf(" is neither left nor right recursive.\n");
			//	index = 3;
		}
	}
	printf("\n");
}
