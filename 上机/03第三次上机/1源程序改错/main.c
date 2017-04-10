#include <stdio.h>
long sum_fac(int n); //1，添加声明
int main(void)
{
    int k;
    for (k = 1; k < 6; ++k)
    {
        printf("k=%d\tthe sum is %ld\n", k, sum_fac(k)); // 与第1处相关调用的sum_fac函数未声明
    }
    return 0;
}
// return 0; 2，return 应该写在main函数最后而不是外面
long sum_fac(int n)
{
    static long s = 0; // 修改s为静态变量
    int i;
    long fac = 1; // 3，fac未初始化，值未知
    for (i = 1; i <= n; ++i)
        fac *= i;
    s += fac; //4， s += fac;这里的s是0，加上fac并不是1到n的阶乘和
              // 可以把s设置为静态变量，即可满足题意
    return s;
}
