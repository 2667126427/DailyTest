#include <stdio.h>
#include <stdlib.h>
#define BIG(a, b) (a > b ? a : b)
#define SMALL(a, b) (a> b ? b : a)

int Big(int numA, int numB)
{
    if (numA == 1 || numB == 1 || numA % numB == 0 || numB % numA == 0)
    {
        return SMALL(numA, numB);
    }
    else
    {
        int temp = 0;
        while (numB != 0)
        {
            temp = numB;
            numB = numA % numB;
            numA = temp;
        }
    }

    return numA;
}

int Small(int numA, int numB)
{
    if (numA == 1 || numB == 1 || numA % numB == 0 || numB % numA == 0)
    {
        return BIG(numA, numB);
    }
    else
    {
        return numA / Big(numA, numB) * numB;
    }
}

int main()
{
    int numA = 0;
    int numB = 0;

    scanf("%d %d", &numA, &numB);

    do {
        printf("%d %d\n", Big(numA, numB), Small(numA, numB));
        scanf("%d %d", &numA, &numB);
    } while(numA != 0 && numB != 0);

    return 0;
}
