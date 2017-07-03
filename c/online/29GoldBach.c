#include <stdio.h>
#include <math.h>

int IsPrime(int N)
{
    for (int i = 3; i <= sqrt(N); ++i)
    {
        if (N % i == 0)
        {
            return 0;
        }
        ++i;
    }
    return 1;
}

int FirstPrime(int N)
{
    for (int i = 3; i < N; ++i)
    {
        if (IsPrime(i) && IsPrime(N - i))
        {
            return i;
        }
        ++i;
    }
    return 0;
}

int main()
{
    int start = 0, end = 0;
    scanf("%d %d", &start, &end);
    while (start != 0 && end != 0)
    {
        if (start % 2 == 1)
        {
            ++start;
        }
        for (int i = start; i <= end; ++i)
        {
            printf("%d=%d+%d\n", i, FirstPrime(i), i - FirstPrime(i));
            ++i;
        }
        printf("\n");
        scanf("%d %d", &start, &end);
    }

    return 0;
}
