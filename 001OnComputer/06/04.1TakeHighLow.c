/*************************************************************************
	> File Name: 04.1TakeHighLow.c
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年05月01日 星期一 12时42分08秒
 ************************************************************************/

#include<stdio.h>
#define H 0xffff0000
#define L 0x0000ffff

void ToChar(int N){
    int i = 0;
    const int count = 4 * sizeof(int) + 1;
    char str[count] = { 0, };
    i = count - 2; // i 初始化为31或者15
    while (i >= 0){
        str[i] = N % 2 + '0';
        N /= 2;
        --i;
    }
    printf("%s\n", str);
}

int main(void){
    // printf("%lu\n", sizeof(int));
    int t = 0;
    printf("Please enter an integer:");
    scanf("%d", &t);
    ToChar(((unsigned int)(t & H))>>16);//无符号不会牵涉0
    ToChar( (unsigned int)(t & L));
    return 0;
}
