#include <stdio.h>

int Biggest(int numA, int numB)
{
	int t = 0;
	if (numB > 0)
	{
		t = numB;
		numB = numA % numB;
		numA = t;
		return Biggest(numA, numB);
	}
	else
	{
		return numA;
	}
}

int main(void)
{
	int numA = 0, numB = 0;
	printf("Please enter two number:");
	scanf("%d %d", &numA, &numB);
	printf("Biggest common is %d\n", Biggest(numA, numB));

	return 0;
}
