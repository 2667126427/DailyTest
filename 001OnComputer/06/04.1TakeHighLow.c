/*************************************************************************
	> File Name: 04.1TakeHighLow.c
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年05月01日 星期一 12时42分08秒
 ************************************************************************/

#include<stdio.h>
#define H 0xffff0000
#define L 0x0000ffff
int main(void){
    // printf("%lu\n", sizeof(int));
    int t = 0;
    printf("Please enter an integer:");
    scanf("%d", &t);
    printf("The high 4 Bit is %d\n", (int)(t & H));
    printf("the low 4 Bit is %d\n", (int)(t & L));
    return 0;
}
