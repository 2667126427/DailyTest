#include <stdio.h>
#define true 1
#define false 0
typedef int bool;
int count = 0;
int point = 0;

int Sum(int N)
{
	int sum = 0;
	while (N > 0)
	{
		sum += N % 10;
		N /= 10;
	}
	int t = sum % 6;
	return (t ? t + 1 : 1);
}

bool Result(int numA, int numB)
{
	++count;
	int sum = Sum(numA + count - 1) + Sum(numB + count - 1);
	
	if ((sum == 7 || sum == 11) && count == 1)
	{
		return true;
	}
	else if ((sum == 2 || sum == 3 || sum == 12) && count == 1)
	{
		return false;
	}
	else if (count == 1)
	{
		point = sum;
		return Result(numA, numB);
	}
	if (sum == point)
	{
		return true;
	}
	else if (sum == 7)
	{
		return false;
	}
	else
	{
		return Result(numA, numB);
	}
}

int main()
{
	int N = 0;
	int numA = 0, numB = 0;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i)
	{
		scanf("%d %d", &numA, &numB);
		count = 0;
		if (Result(numA, numB))
		{
			printf("success!\n");
		}
		else
		{
			printf("fail!\n");
		}

	}

	return 0;
}
