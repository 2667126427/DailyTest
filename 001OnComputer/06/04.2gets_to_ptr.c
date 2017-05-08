/*************************************************************************
	> File Name: 04.2gets_to_ptr.c
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年05月01日 星期一 13时03分25秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void concen_space(char (*str)[81], int num){
    int temp = 0;
    int len = 0;
    for (int i = 0; i < num; ++i){
        temp = 0;
        len = strlen(str[i]);
        if (len == 0){
            continue;
        }
        for (temp = 0; temp < len; ++temp){
            if ((str[i][temp] != ' ') || (str[i][temp] == ' ' && str[i][temp + 1] != ' ')){
                printf("%c", str[i][temp]);
            }
        }
        printf("\n");
    }
}

int main(void){
	int N; // n行
	printf("请输入行数：");
	scanf("%d", &N);
	getchar();
	char strs[100][81];
	char (*pstr)[81] = strs;
	for (int i = 0; i < N; ++i){
		gets(strs[i]);
	}
	concen_space(pstr, N);
    return 0;
}
