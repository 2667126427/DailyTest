#include <stdio.h>
double sum_fac(int n);
int main(void)
{
    int k;
    for (k = 1; k < 6; ++k)
    {
        printf("k=%d\tthe sum is %f\n", k, sum_fac(k));
    }
    return 0;
}
double sum_fac(int n)
{
    static double s = 0;
    static double fac = 1;
    fac /= n;
    s += fac;
    return s;
}

