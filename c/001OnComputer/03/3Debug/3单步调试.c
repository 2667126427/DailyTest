#include <stdio.h>
long fabnocci(int);
int main(void)
{
    int i, k;
    long sum = 0, *p = &sum;
    scanf("%d", &k);
    for (i = 1; i <= k; ++i){
        sum += fabnocci(i);
        printf("i = %d\tthe sum is %ld\n", i, *p);
    }
    return 0;
}
long fabnocci(int n)
{
    if (n == 1 || n == 2)
        return 1;
    else
        return fabnocci(n - 1) + fabnocci(n - 2);
}
