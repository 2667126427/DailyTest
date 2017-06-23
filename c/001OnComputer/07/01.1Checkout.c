/*************************************************************************
	> File Name: 01.1Checkout.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月15日 星期一 23时13分05秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main(void){
    char u[] = "UVWXYZ";
    char v[] = "xyz";
    struct T{
        int x;
        char c;
        char*t;
    }a[] = {{ 11, 'A', u }, { 100, 'B', v }}, *p = a;
    // 按要求写下来，再对应还原
    // 前四个是对p指针直接操作
    printf("(++p)->x = %d\n", (++p)->x);
    p--;
    p++, printf("p++, p->c = %c\n", p->c);
    p--;
    *p++->t, printf("*p++->t, *p->t = %c\n", *p->t);
    p--;
    printf("*(++p)->t = %c\n", *(++p)->t);
    p--;
    // 后两个是对p指向的对象操作
    // p->t为u的首地址，++后指向下一个字母即V
    printf("*++p->t = %c\n", *++p->t);
    (p->t)--;
    // *p-t是'U'
    printf("++*p->t = %c\n", ++*p->t);
    --*p->t;
    return 0;
}
