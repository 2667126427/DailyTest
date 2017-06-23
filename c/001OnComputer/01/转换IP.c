#include <stdio.h>
#define A 0xFF000000
#define B 0x00FF0000
#define C 0x0000FF00
#define D 0x000000FF
int main()
{
    unsigned long temp = 0;
unsigned char IP1, IP2, IP3, IP4;
printf("Please input the valid IP address:");
    scanf("%ld", &temp);
    IP1 = (temp&A)>>24;
    IP2 = (temp&B)>>16;
    IP3 = (temp&C)>>8;
    IP4 = (temp&D);
    printf("%u.%u.%u.%u\n", IP4, IP3, IP2, IP1);
    return 0;
}
