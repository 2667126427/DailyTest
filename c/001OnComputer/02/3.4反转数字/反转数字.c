#include <stdio.h>
#include <stdlib.h>

int main()
{
    int target = 0;
    printf("Please enter a number:");

    scanf("%d", &target);
    while (target > 0)
    {
        printf("%d", target % 10);
        target /= 10;
    }
    printf("\n");

    return 0;
}
