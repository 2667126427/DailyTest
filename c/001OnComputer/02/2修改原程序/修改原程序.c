#include <stdio.h>

int main()
{
    int i, n, s = 1;
    printf("Please enter n:");
    scanf("%d", &n);
    // whileʵ��
    s = 1;
    i = 1;
    while (i <= n)
    {
        s *= i;
        ++i;
    }
    printf("%d! = %d\n", n, s);
    // do-whileʵ��
    i = 1;
    s = 1;
    do {
        s *= i;
        ++i;
    } while (i <= n);
    printf("%d! = %d\n", n, s);

    return 0;
}
