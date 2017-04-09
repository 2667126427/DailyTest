#include <stdio.h>

int main()
{
    int num = 0;
    int testInt;
    double testDouble;
    char testChar;
    char testChars[200];

    printf("请分别输入一个整数，一个实数，一个字符，一个字符串：\n");
    num = scanf("%d %lf %c %s", &testInt, &testDouble, &testChar, testChars);

    printf("scanf返回值为：%d\n", num);

    return 0;
}
