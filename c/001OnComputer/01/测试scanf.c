#include <stdio.h>

int main()
{
    int num = 0;
    int testInt;
    double testDouble;
    char testChar;
    char testChars[200];

    printf("��ֱ�����һ��������һ��ʵ����һ���ַ���һ���ַ�����\n");
    num = scanf("%d %lf %c %s", &testInt, &testDouble, &testChar, testChars);

    printf("scanf����ֵΪ��%d\n", num);

    return 0;
}
