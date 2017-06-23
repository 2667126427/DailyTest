#include <stdio.h>
#include <stdlib.h>

void Print(int num)
{
    while (num > 0)
    {
        printf("%d", num % 10);
        num /= 10;
    }

    printf("\n");
}

int main()
{
    int temp = 0;

    scanf("%d", &temp);

    while (temp != 0)
    {
        Print(temp);
        scanf("%d", &temp);
    }

    return 0;
}
