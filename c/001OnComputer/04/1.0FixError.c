#include <stdio.h>
#define SUM ((a)+(b)) //1, �궨����ö���������
#define DIF ((a)-(b))
#define SWAP(a, b) a^=b,b^=a,a^=b //2��a=b,b=a�˽�����Ч
int main(void){
    int a, b, t;
    printf("Input two integers a, b:");
    scanf("%d,%d", &a, &b); //3��aδ����
    printf("\nSUM=%d\n the difference between square of a and square of b is: %d",
           SUM, SUM*DIF);
    SWAP(a,b);
    printf("\nNow a=%d, b=%d\n", a, b);//4��printf��pСд

    return 0;
}
