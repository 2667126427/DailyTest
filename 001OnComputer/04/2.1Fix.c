// 1，添加使用了的头文件
#include <stdio.h>
// 2，函数调用时没有声明，添加声明
int max(int x, int y, int z);
float sum(float x, float y);
// 3，main函数最后返回了0，那么应该为int
int main(void){
    int a, b, c;
    float d, e;
    printf("Enter three integers:");
    scanf("%d,%d,%d", &a, &b, &c);
    printf("\nthe maximum of them is %d\n", max(a, b, c));
    printf("Enter two floating point numbers:");
    scanf("%f,%f", &d, &e);
    printf("\nthe sum of them is %f\n", sum(d, e));
    return 0;
}
int max(int x, int y, int z){
    int t;
    if (x > y)
        t=x;
    else
        t=y;
    if (t < z)
        t=z;
    return t;
}
float sum(float x, float y){
    return x + y;
}
