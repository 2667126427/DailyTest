#include <stdio.h>
long sum_fac(int n); //1���������
int main(void)
{
    int k;
    for (k = 1; k < 6; ++k)
    {
        printf("k=%d\tthe sum is %ld\n", k, sum_fac(k)); // ���1����ص��õ�sum_fac����δ����
    }
    return 0;
}
// return 0; 2��return Ӧ��д��main����������������
long sum_fac(int n)
{
    static long s = 0; // �޸�sΪ��̬����
    int i;
    long fac = 1; // 3��facδ��ʼ����ֵδ֪
    for (i = 1; i <= n; ++i)
        fac *= i;
    s += fac; //4�� s += fac;�����s��0������fac������1��n�Ľ׳˺�
              // ���԰�s����Ϊ��̬������������������
    return s;
}
