#include <stdio.h>
#define PI 3.14159 /* 1 宏定义后面不需要分号 */

int main(void) // 2 主函数名应为main且返回值应为int
{
    int f;
    short p, k;
    double c, r, s;
    short newint; // 定义newint
    // unsigned short newint;
    /* for task one */
    printf("Input Fahrenheit:");// 3 printf的字符串使用英文双引号
    scanf("%d", &f); // 4 scanf后的参数应为输入参数的地址，字符串使用英文双引号

    c = 5.0 / 9 * (f - 32); //5 整数运算会损失精度

    printf("\n%d(F)=%.2f(C)\n\n", f, c);

    /* for task two */
    printf("Input the radius r:");
    scanf("%lf", &r); //6 输入double应该使用%lf
    s = PI * r * r;

    printf("\nThe acreage is %.2f\n\n", s);// 7 printf 输出参数不需要取地址符

    /* for task three */
    printf("input hex int k, p:");
    scanf("%x %x", &k, &p);

    newint = ((k&0xff00)>>8)|(p&0xff00); // 8 newint 未定义 ,9 k的高字节应该向右移

    printf("new int = %x\n\n", newint);

    return 0;
}
