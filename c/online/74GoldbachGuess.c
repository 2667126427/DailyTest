#include <stdio.h>
#define true 1
#define false 0

typedef int bool;


bool IsPrime(int test)
{
    bool result = true;

    if (test == 2)
    {
        result = true;
    }
    else if (test % 2 == 0)
    {
        result = false;
    }
    else
    {
        for (int i = 3; i <= (test + 1) / 2; ++i)
        {
            if (test % i == 0)
            {
                result = false;
                break;
            }
            ++i; // 两次++是因为不需要判断偶数
        }
    }

    return result;
}

int main()
{
    int N = 0;
    int temp = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &temp);

        for (int one = 2; one <= (temp + 1) / 2; ++one)
        {
            if (IsPrime(one) && IsPrime(temp - one))
            {
                printf("%d=%d+%d\n", temp, one, temp - one);
                break;
            }
        }
    }

    return 0;
}
