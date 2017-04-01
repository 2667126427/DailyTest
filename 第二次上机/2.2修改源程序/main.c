#include <stdio.h>
#include <stdlib.h>

unsigned int JieCheng(unsigned int target)
{
	unsigned int result = 1;
	for (unsigned int i = 1; i <= target; ++i)
	{
		result *= i;
	}
	return result;
}

int main()
{
	unsigned int result = 0;
	unsigned int target = 0;
	printf("Please a number:");
	scanf("%d", &target);

	while (JieCheng(result) < target)
	{
		++result;
	}

	printf("%d! >= %d\n", result, target);

	return 0;
}
