/*************************************************************************
	> File Name: 47UpsideArray.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月06日 星期六 17时25分43秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
// 输入数据
void Input(int* arr,const  int num){
    for (int i = 0; i < num; ++i){
        scanf("%d", &arr[i]);
    }
}
// 反转
void Upside(int* start, int* end){
    while(start <= end){
        int t = *start;
        *start = *end;
        *end = t;
        start++;
        end--;
    }
}
// 输出
void Print(int*arr, const int num){
    printf("%d", arr[0]);
    for (int i = 1; i < num; ++i){
        printf(" %d", arr[i]);
    }
    printf("\n");
}
int main(void){
    int *arr = NULL;// 由于每次的个数都不知道,所以使用动态分配
    int N = 0;
    scanf("%d", &N);
    int num = 0;
    for (int i = 0; i < N; ++i){
        scanf("%d", &num);
        arr = (int*)malloc(num * sizeof(int));
        Input(arr, num);
        Upside(arr, arr + num - 1);
        Print(arr, num);
        free(arr);// 记得释放,防止内存泄漏
    }
    return 0;
}
