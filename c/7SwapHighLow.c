#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned short k = 0;
    scanf("%hu", &k);

    k = (((0xF000)&k)>>12)|(((0x000F)&k)<<12)|((0x0FF0)&k);

    printf("%hu\n", k);

    return 0;
}
