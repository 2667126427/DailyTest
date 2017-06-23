#include <stdio.h>

unsigned short BitSwap(unsigned short temp)
{
    return ((temp&0xF000)>>12)|((temp&0x000F)<<12)|(temp&0x0FF0);
}

int main()
{
    int N = 0;
    unsigned short temp = 0;

    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        scanf("%hu", &temp);

        printf("%hu\n", BitSwap(temp));
    }

    return 0;
}
