/*************************************************************************
	> File Name: 49MyStrcat.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月06日 星期六 21时59分26秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
void _strcat(char* result, char strs[][1000], int count){
    int temp = 0;
    for (int i = 0; i < count; ++i){
        temp = 0;
         while(*result++ = *(*strs + temp++));// 其实我内心是拒绝这么写的
        strs++;
        result--; // 去除句末的结束符
    }
    *(++result) = '\0';
}
int main(void){
    char chs[20][1000];
    char result[20000];
    int N = 0;
    while(scanf("%d", &N), N){
        getchar();
        for (int i = 0; i < N; ++i){
            scanf("%[^\n]", chs[i]);
            getchar();
        }
        _strcat(result, chs, N);
        printf("%s\n", result);
    }
    return 0;
}
