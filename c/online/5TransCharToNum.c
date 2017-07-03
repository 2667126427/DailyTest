#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N = 0;
    char ch;

    scanf("%d", &N);
    getchar();

    for (int i = 0; i < N; ++i)
    {
        scanf("%c", &ch);
        getchar();

        if (ch >= '0' && ch <= '9')
        {
            ch = ch - '0';
        }
        else if (ch >= 'a' && ch <= 'f')
        {
            ch = ch - 'a' + 10;
        }
        else if (ch >= 'A' && ch <= 'F')
        {
            ch = ch - 'A' + 10;
        }

        printf("%d\n", (int)ch);
    }

    return 0;
}
