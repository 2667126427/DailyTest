#include <stdio.h>
#include <stdlib.h>
#define EPS 1e-6

double Func(double x)
{
    return (3 * x * x * x - 4 * x * x - 5 * x + 13);
}

double FuncDeri(double x)
{
    return (9 * x * x - 8 * x - 5);
}

int main()
{
    double x0 = 0;
    double x1 = 0;
    double diff = 1;
    double temp = 0;

    while (diff >= EPS)
    {
        x1 = x0 - Func(x0) / FuncDeri(x0);
        diff = x1 - x0;
        diff = diff > 0 ? diff : -diff;
        x0 = x1;
    }

    printf("%f\n", x0);

    return 0;
}
