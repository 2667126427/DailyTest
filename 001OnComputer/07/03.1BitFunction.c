/*************************************************************************
	> File Name: 03.1BitFunction.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月16日 星期二 22时03分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdlib.h>

typedef unsigned int u_int;
typedef struct bits{
    u_int bit0 : 1;u_int bit1 : 1;
    u_int bit2 : 1;u_int bit3 : 1;
    u_int bit4 : 1;u_int bit5 : 1;
    u_int bit6 : 1;u_int bit7 : 1;
}bits;

void SetBit(bits* res, unsigned short tar){
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

void Print(const bits* tar, void (*p_fun[8])(void)){
    if (tar->bit0)p_fun[0]();
    if (tar->bit1)p_fun[1]();
    if (tar->bit2)p_fun[2]();
    if (tar->bit3)p_fun[3]();
    if (tar->bit4)p_fun[4]();
    if (tar->bit5)p_fun[5]();
    if (tar->bit6)p_fun[6]();
    if (tar->bit7)p_fun[7]();
}

void f0(void){
    printf("The function 0 is called!\n");
}
void f1(void){
    printf("The function 1 is called!\n");
}
void f2(void){
    printf("The function 2 is called!\n");
}
void f3(void){
    printf("The function 3 is called!\n");
}
void f4(void){
    printf("The function 4 is called!\n");
}
void f5(void){
    printf("The function 5 is called!\n");
}
void f6(void){
    printf("The function 6 is called!\n");
}
void f7(void){
    printf("The function 7 is called!\n");
}

int main(void){

    bits* temp = (bits*)malloc(sizeof(bits));
    void (*p_fun[8])(void) = { f0, f1, f2, f3, f4, f5, f6, f7 };
    unsigned short t;
    scanf("%hu", &t);
    SetBit(temp, t);
    Print(temp, p_fun);
    printf("\n");

    free(temp);
    return 0;
}
