#include <stdio.h>

int main()
{
    int N = 0;
    short temp = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        scanf("%hu", &temp);

        printf("%c,%c\n", (char)((unsigned short)temp>>8), (char)(temp&0x00FF));
    }

    return 0;
}
