/*************************************************************************
	> File Name: 04.3Sort.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月08日 星期一 20时05分44秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>

// 有参数减序
int Desce(int a, int b){
    return a <= b;
}
int Ascen(int a, int b){
    return a >= b;
}

void Input(int*arr, int N){
    for (int i = 0; i < N; ++i)scanf("%d", &arr[i]);
}
void Print(int* arr, int N){
    printf("%d", arr[0]);
    for (int i = 1; i < N; ++i)printf(" %d", arr[i]);
    printf("\n");
}


void Sort(int *arr, const int start, const int end, int (*comp)(int a, int b)){
    if (start >= end)return;
    int key = arr[start];
    int s = start;
    int e = end;
    while(s < e){
        while(comp(arr[e], key) && s < e)--e;
        arr[s] = arr[e];
        while(comp(key,arr[s]) && s < e)++s;
        arr[e] = arr[s];
    }
    arr[s] = key;
    Sort(arr, start, s - 1, comp);
    Sort(arr, s + 1, end, comp);
}

int main(int argc, char*argv[]){
    // printf("argc = %d\n", argc);
    int *arr = NULL;
    int N = 0;
    scanf("%d", &N);
    arr = (int*)malloc(N * sizeof(int));
    Input(arr, N);
    // argc 为 1 没有-d，2有
    Sort(arr, 0, N - 1, (argc - 1) ? Desce : Ascen);
    Print(arr, N);
    return 0;
}
