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
输出斐波拉契数列的前n项。n≥3输入：有多组输入，每行是一个整数n，当输入为0时，程序结束运行。
输出：对于每组输入n，当n≥3时，输出斐波拉契数列的前n项，每行输出8个数（最后一行可不是8个），
每个数的宽度为10（右对齐，左边用空格补齐）；否则输出Error!。两组输出用空行隔开。
*/
