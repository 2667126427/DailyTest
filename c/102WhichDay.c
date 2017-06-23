/*************************************************************************
	> File Name: 102WhichDay.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月18日 星期四 13时54分09秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef struct Date{
    int year;
    int month;
    int day;
}Date;

int IsLeap(Date date){
    if (date.year % 400 == 0 || (date.year % 4 == 0 && date.year % 100 != 0)){
        return 1;
    }
    return 0;
}

int WhichDay(Date date){
    int result = 0;
    switch (date.month){
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
        result += date.day;
        break;
    default:
        exit(0);
    }
    if (IsLeap(date) && date.month > 2)++result;
    return result;
}

int main(void){
    int N = 0;
    scanf("%d", &N);
    Date date;
    for (int i = 0; i < N; ++i){
        scanf("%d %d %d", &date.year, &date.month, &date.day);
        printf("%d\n", WhichDay(date));
    }


    return 0;
}
