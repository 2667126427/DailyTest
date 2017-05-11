/*************************************************************************
	> File Name: 04.1TakeHighLow.c
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年05月01日 星期一 12时42分08秒
 ************************************************************************/

#include<stdio.h>
#define A 0xf0000000
#define B 0x0f000000
#define C 0x00f00000
#define D 0x000f0000
#define E 0x0000f000
#define F 0x00000f00
#define G 0x000000f0
#define H 0x0000000f

void ToChar(unsigned int N){
    int i = 0;
    const int count = 5;
    char str[count] = { 0, };
    i = count - 2; // 初始化i在正确地方
    while (i >= 0){
        str[i] = N % 2 + '0';
        N /= 2;
        --i;
    }
    printf("%s\n", str);
}

int main(void){
    // printf("%lu\n", sizeof(int));
    unsigned int t = 0;
    printf("Please enter an integer:");
    scanf("%ud", &t);
    ToChar((t&A)>>28);
    ToChar((t&B)>>24);
    ToChar((t&C)>>20);
    ToChar((t&D)>>16);
    ToChar((t&E)>>12);
    ToChar((t&F)>>8);
    ToChar((t&G)>>4);
    ToChar((t&H)>>0);

    return 0;
}
