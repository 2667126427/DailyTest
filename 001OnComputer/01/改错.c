#include <stdio.h>
#define PI 3.14159 /* 1 �궨����治��Ҫ�ֺ� */

int main(void) // 2 ��������ӦΪmain�ҷ���ֵӦΪint
{
    int f;
    short p, k;
    double c, r, s;
    short newint; // ����newint
    // unsigned short newint;
    /* for task one */
    printf("Input Fahrenheit:");// 3 printf���ַ���ʹ��Ӣ��˫����
    scanf("%d", &f); // 4 scanf��Ĳ���ӦΪ��������ĵ�ַ���ַ���ʹ��Ӣ��˫����

    c = 5.0 / 9 * (f - 32); //5 �����������ʧ����

    printf("\n%d(F)=%.2f(C)\n\n", f, c);

    /* for task two */
    printf("Input the radius r:");
    scanf("%lf", &r); //6 ����doubleӦ��ʹ��%lf
    s = PI * r * r;

    printf("\nThe acreage is %.2f\n\n", s);// 7 printf �����������Ҫȡ��ַ��

    /* for task three */
    printf("input hex int k, p:");
    scanf("%x %x", &k, &p);

    newint = ((k&0xff00)>>8)|(p&0xff00); // 8 newint δ���� ,9 k�ĸ��ֽ�Ӧ��������

    printf("new int = %x\n\n", newint);

    return 0;
}
