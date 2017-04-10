#include <stdio.h>
#include <math.h>

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
    int temp = 0;
    int t = 0;
    printf("Please enter a even number greater than 3:");
    scanf("%d", &temp);
    t = Prime(temp);
    printf("%d = %d + %d\n", temp, t, temp - t);

    return 0;
}
