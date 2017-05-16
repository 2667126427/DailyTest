/*************************************************************************
    > File Name: 101BreakSer.c
    > Author: Yaning Wang, CS1607
    > Mail: wangyanign6166@gmail.com
    > School: HUST
    > Created Time: 2017年05月16日 星期二 23时32分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef unsigned int u_int;
typedef struct ISR_BITS{
    u_int bit0 : 1;u_int bit1 : 1;
    u_int bit2 : 1;u_int bit3 : 1;
    u_int bit4 : 1;u_int bit5 : 1;
    u_int bit6 : 1;u_int bit7 : 1;
    u_int rsv : 8;
}ISR_BITS;

typedef union ISR_REG{
    unsigned short all;
    ISR_BITS bit;
}ISR_REG;

void SetBit(ISR_BITS* res, unsigned short tar){
    res->rsv = tar;
    res->bit0 = tar % 2;
    tar /= 2;
    res->bit1 = tar % 2;
    tar /= 2;
    res->bit2 = tar % 2;
    tar /= 2;
    res->bit3 = tar % 2;
    tar /= 2;
    res->bit4 = tar % 2;
    tar /= 2;
    res->bit5 = tar % 2;
    tar /= 2;
    res->bit6 = tar % 2;
    tar /= 2;
    res->bit7 = tar % 2;
}

void Print(const ISR_BITS* tar, void (*p_isr[8])(void)){
    printf("%d\n", tar->rsv);
    if (tar->bit0)p_isr[0]();
    if (tar->bit1)p_isr[1]();
    if (tar->bit2)p_isr[2]();
    if (tar->bit3)p_isr[3]();
    if (tar->bit4)p_isr[4]();
    if (tar->bit5)p_isr[5]();
    if (tar->bit6)p_isr[6]();
    if (tar->bit7)p_isr[7]();
}

void isr0(void){
    printf("The Interrupt Service Routine isr0 is called!\n");
}
void isr1(void){
    printf("The Interrupt Service Routine isr1 is called!\n");
}
void isr2(void){
    printf("The Interrupt Service Routine isr2 is called!\n");
}
void isr3(void){
    printf("The Interrupt Service Routine isr3 is called!\n");
}
void isr4(void){
    printf("The Interrupt Service Routine isr4 is called!\n");
}
void isr5(void){
    printf("The Interrupt Service Routine isr5 is called!\n");
}
void isr6(void){
    printf("The Interrupt Service Routine isr6 is called!\n");
}
void isr7(void){
    printf("The Interrupt Service Routine isr7 is called!\n");
}

int main(void){

    ISR_REG* temp = 0;
    void (*p_isr[8])(void) = { isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7 };
    int N = 0;
    scanf("%d", &N);
    temp = (ISR_REG*)malloc(N * sizeof(ISR_REG));

    for (int i = 0; i < N; ++i){
        scanf("%hu", &temp[i].all);
    }

    for (int i = 0; i < N; ++i){
        int t = temp[i].all;
        SetBit(&temp[i].bit, t);
        Print(&temp[i].bit, p_isr);
        printf("\n");
    }

    free(temp);
    return 0;
}
