#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int bool;

bool LeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int DayOfYear(int year, int month, int day)
{
    int result = 0;
    switch (month)
    {
    case 12:
        result += 30;
    case 11:
        result += 31;
    case 10:
        result += 30;
    case 9:
        result += 31;
    case 8:
        result += 31;
    case 7:
        result += 30;
    case 6:
        result += 31;
    case 5:
        result += 30;
    case 4:
        result += 31;
    case 3:
        result += 28;
    case 2:
        result += 31;
    case 1:
        result += day;
        break;
    default:
        exit(0);
    }

    if (LeapYear(year) && month > 2)
    {
        ++result;
    }

    return result;
}

int main()
{
    int year = 0;
    int month = 0;
    int day = 0;

    while (scanf("%d %d %d", &year, &month, &day) != EOF)
    {
        printf("该日期是这一年中的第%d天\n", DayOfYear(year, month, day));
    }



    return 0;
}
