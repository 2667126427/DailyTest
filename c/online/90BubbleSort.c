/*************************************************************************
	> File Name: 90BubbleSort.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月06日 星期六 17时43分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX 10
void Swap(int*a, int*b){
    int t = *a;
    *a = *b;
    *b = t;
}
void Bubble(int*start, int*end){
    while (start < end){
        int*max = start;
        int*temp = start + 1;
        while(temp < end){
            if (*max > *temp){
                Swap(temp, max);
            }
            max = temp;
            ++temp;
        }
        --end;
    }
}
void Print(int*arr){
    printf("%d", arr[0]);
    for (int i = 1; i < MAX; ++i){
        printf("->%d", arr[i]);
    }
    printf("\n");
}
int main(void){
    int arr[MAX] = { 0, };
    int count = 0;
    while(scanf("%d", &arr[count]) != EOF){
        ++count;
        if(count == MAX){
            Bubble(arr, arr + MAX);
            count = 0;
        Print(arr);
        }
    }
}
