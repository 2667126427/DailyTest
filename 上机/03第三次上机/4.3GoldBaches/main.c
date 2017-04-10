#include <stdio.h>
#include <math.h>
#define BEGIN 10
#define END 20

int IsPrime(int N)
{
    if (N == 1)
    {
        return 0;
    }
    for (int i = 2; i <= sqrt(N); ++i)
    {
        if (N % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int Prime(int N)
{
    for (int i = 1; i <= N; ++i)
    {
        if (IsPrime(i) && IsPrime(N - i))
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int numA = 0, numB = 0;
    int t = 0;
    numA = BEGIN;
    numB = END;
    printf("GOLDBACH'S CONJECTURE:\n");
    printf("Every even number n >= 4 is the sum of two primes.\n");
    if (numA % 2 == 1)
    {
        ++numA;
    }
    for (int i = numA; i <= numB; ++i)
    {
        t = Prime(i);
        printf("%d = %d + %d\n", i, t, i - t);
        ++i;
    }
    return 0;
}
