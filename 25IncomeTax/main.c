#include <stdio.h>
#include <stdlib.h>
#define EPS 1e-6
#define SWITCH 0 // value 1:using switch; value 0: using if;
#define RATE0 0
#define RATE1 0.05
#define RATE2 0.1
#define RATE3 0.15
#define RATE4 0.2
#define RATE5 0.25

double Tax(double salary)
{
    double tax = 0;

    #if SWITCH
    {
        switch ((int)salary % 1000)
        {
        default:
            tax += (salary - 5000) * RATE5;
            salary = 5000;
        case 4:
            tax += (salary - 4000) * RATE4;
            salary = 4000;
        case 3:
            tax += (salary - 3000) * RATE3;
            salary = 3000;
        case 2:
            tax += (salary - 2000) * RATE2;
            salary = 2000;
        case 1:
            tax += (salary - 1000) * RATE1;
            salary = 1000;
        case 0:
            tax += (salary - 0) * RATE0;
            salary = 0;
        }
    }
    #else
    if (salary > 5000)
    {
        tax += (salary - 5000) * RATE5;
        salary = 5000;
    }
    if (salary > 4000)
    {
        tax += (salary - 4000) * RATE4;
        salary = 4000;
    }
    if (salary > 3000)
    {
        tax += (salary - 3000) * RATE3;
        salary = 3000;
    }
    if (salary > 2000)
    {
        tax += (salary - 2000) * RATE2;
        salary = 2000;
    }
    if (salary > 1000)
    {
        tax += (salary - 1000) * RATE1;
        salary = 1000;
    }
    if (salary > 0)
    {
        tax += (salary - 0) * RATE0;
        salary = 0;
    }
    #endif // SWITCH

    return tax;
}

int main()
{
    double salary = 0;

    scanf("%lf", &salary);

    while (salary > EPS)
    {
        printf("%f\n", Tax(salary));
        scanf("%lf", &salary);
    }

    return 0;
}
