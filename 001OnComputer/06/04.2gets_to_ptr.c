/*************************************************************************
	> File Name: 04.2gets_to_ptr.c
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年05月01日 星期一 13时03分25秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
void concen_space(char* str[], int num){
    int len = strlen(str);
    int temp = 0;
    int i = 0;
    do{
        if (str[i] == ' ' && str[i + 1] != ' ' || str[i] != ' '){
            str[temp++] = str[i++];
        }
    }while(str[i - 1]);
    
}
int main(void){
    char *strs[81];


    return 0;
}
