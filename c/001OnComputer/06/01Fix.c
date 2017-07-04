/*************************************************************************
	> File Name: 01Fix.c
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年05月01日 星期一 11时57分16秒
 ************************************************************************/

#include<stdio.h>
int main(void){
    float t = 0; 
    float *p = &t; // 初始化
    scanf("%f", p); // 1，p是野指针，没有指向正确的地方，应该为其初始化
    printf("%f\n", *p);
    return 0;
}
