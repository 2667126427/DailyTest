#include <stdio.h>
#include <string.h>

int main()
{
    int k = 0;
    int len = 0;
    char num[11];

    while (scanf("%s %d", num, &k) != EOF)
    {
        len = strlen(num);
        if (k > len)
        {
            printf("-1\n");
        }
        else
        {
            printf("%c\n", num[len - k]);
        }
    }

    return 0;
}
