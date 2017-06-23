#include <stdio.h>
int main()
{
    int i, n, s = 1;
    printf("Please enter n:");
    scanf("%d", &n); //1 输入变量没有取地址符
    for (i = 1; i <= n; i++) //2 for里面是分号隔开3个语句，不是逗号
        s = s * i;
    printf("%d!=%d\n", n, s);
    return 0;
}
// return 0;//3 return 0;应该在main最后不应该在外面
