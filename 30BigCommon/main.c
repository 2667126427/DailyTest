#include <stdio.h>
#include <stdlib.h>

int BigCom(int numA, int numB)
{
    int t = 0;
    while (numA > 0)
    {
        t = numB % numA;
        numB = numA;
        numA = t;
    }
    return numB;
}

int main()
{
    int numA = 0, numB = 0;
    scanf("%d %d", &numA, &numB);
    while (numA != 0 && numB != 0)
    {
        printf("%d\n", BigCom(numA, numB));
        scanf("%d %d", &numA, &numB);
    }

    return 0;
}
