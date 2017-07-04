#include <stdio.h>
int main()
{
unsigned short x, m, n;
printf("输入无符号短整数x, m, n(0<=m<=15， 1<=n<=16-m):");
    scanf("%hu %hu %hu", &x, &m, &n);
    x <<= (16 - m - n);
    x &= (0xFFFF)<<(16-n);
    printf("%u\n", x);

    return 0;
}
