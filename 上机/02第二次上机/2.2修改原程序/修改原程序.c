#include <stdio.h>
#include <stdlib.h>

int main()
{
	unsigned int s = 1;
	unsigned int S = 0;
	int i = 0;
	printf("Please a number:");
	scanf("%d", &S);

	while (s < S)
	{
		s *= ++i;
	}

	printf("%d! >= %d\n", i, S);

	return 0;
}
