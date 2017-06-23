#include <stdio.h>
#include <stdlib.h>
unsigned int fibo[51] = { 0, };

void InitFibo(void)
{
    fibo[0] = 0;
    fibo[1] = 1;
    for (int i = 2; i < 51; ++i)
    {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    }
}

void Print(int num)
{
    if (num < 3)
    {
        printf("Error!");
        return;
    }

    for (int i = 1; i <= num; ++i)
    {
        printf("%10d", fibo[i]);
        if (i % 8 == 0 && i != num)
        {
            printf("\n");
        }
    }
}

int main()
{
    int temp = 0;
    InitFibo();

    while (1)
    {
        scanf("%d", &temp);
        if (temp != 0)
        {
            Print(temp);
            printf("\n\n");
        }
        else
        {
            break;
        }
    }


    return 0;
}
/*
���쳲��������е�ǰn�n��3���룺�ж������룬ÿ����һ������n��������Ϊ0ʱ������������С�
���������ÿ������n����n��3ʱ�����쳲��������е�ǰn�ÿ�����8���������һ�пɲ���8������
ÿ�����Ŀ��Ϊ10���Ҷ��룬����ÿո��룩���������Error!����������ÿ��и�����
*/
