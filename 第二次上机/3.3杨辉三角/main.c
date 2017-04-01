#include <stdio.h>

void PrintSpace(unsigned int N)
{
	char space[3] = { ' ', ' ', '\0' };
	for (unsigned int i = 0; i < N; ++i)
	{
		printf("%s", space);
	}
}

void Print(unsigned int N)
{
	unsigned int temp = 0;
	unsigned int j = 0;
	for (unsigned int i = 1; i <= N; ++i)
	{
		temp = 1;
		PrintSpace(N - i);
		printf("%d", temp);
		for (j = 1; j < i; ++j)
		{
			temp = temp * (i - j) / j;
			printf("%4d", temp);
		}
		printf("\n");
	}
}

int main()
{
	unsigned int N = 0;
	printf("Please enter the number of plies you want:");
	scanf("%d", &N);

	Print(N);

	return 0;
}
