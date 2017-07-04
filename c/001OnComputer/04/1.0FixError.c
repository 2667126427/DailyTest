#include <stdio.h>
#define SUM ((a)+(b)) //1, 宏定义最好都加上括号
#define DIF ((a)-(b))
#define SWAP(a, b) a^=b,b^=a,a^=b //2，a=b,b=a此交换无效
int main(void){
    int a, b, t;
    printf("Input two integers a, b:");
    scanf("%d,%d", &a, &b); //3，a未定义
    printf("\nSUM=%d\n the difference between square of a and square of b is: %d",
           SUM, SUM*DIF);
    SWAP(a,b);
    printf("\nNow a=%d, b=%d\n", a, b);//4，printf的p小写

    return 0;
}
