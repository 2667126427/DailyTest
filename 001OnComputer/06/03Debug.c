/*************************************************************************
	> File Name: 03Debug.c
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年05月01日 星期一 12时26分58秒
 ************************************************************************/

#include<stdio.h>
char * strcpy(char*, char*);
int main(void){
    char a[60], b[60] = "there is a boat on the lake."; // 1，a字符数组长度不够，调大一点
    printf("%s\n", strcpy(a, b));
    return 0;
}
char* strcpy(char * s, char * t){
    // 2，返回的不是字符数组首地址，可以设置一个指针专门存放首地址
    char *str = s;
    while(*s++ = *t++)
    ;
    return(str);
}

