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
/***
        1
      1   1
    1   2   1
  1   3   3   1
1   4   6   4   1

  1
1   1

                  1
                1   1
              1   2   1
            1   3   3   1
          1   4   6   4   1
        1   5  10  10   5   1
      1   6  15  20  15   6   1
    1   7  21  35  35  21   7   1
  1   8  28  56  70  56  28   8   1
1   9  36  84 126 126  84  36   9   1

                    1
                  1   1
                1   2   1
              1   3   3   1
            1   4   6   4   1
          1   5  10  10   5   1
        1   6  15  20  15   6   1
      1   7  21  35  35  21   7   1
    1   8  28  56  70  56  28   8   1
  1   9  36  84 126 126  84  36   9   1
1  10  45 120 210 252 210 120  45  10   1

*/
