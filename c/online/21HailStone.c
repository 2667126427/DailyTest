#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N = 0;
    int temp = 0;
    scanf("%d", &temp);
    while (temp != 0)
    {
        N = 0;
        if (temp == 1)
        {
            printf("%5d\n\n", 1);
        }
        else
        {
            while (temp != 1)
            {
                printf("%5d", temp);
                if (temp % 2 == 0)
                {
                    temp /= 2;
                }
                else
                {
                    temp = 3 * temp + 1;
                }
                ++N;
                if (N % 6 == 0)
                {
                    printf("\n");
                }
            }
            if (N % 6 != 0)
            {
                printf("%5d\n\n", 1);
            }
            else
            {
                printf("%5d\n", 1);
            }
        }
        scanf("%d", &temp);
    }

    return 0;
}
