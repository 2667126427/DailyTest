/*************************************************************************
	> File Name: 02.1Complete.c
	> Author: Yaning Wang
	> Mail: wangyaning6166@gmail.com
	> Created Time: 2017年05月01日 星期一 12时04分39秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(void){
    char*(*p)(char[], const char[]); // 1，下面用到了函数指针p，在此处定义，可推断参数为2个字符指针，返回值为一个字符指针
    char a[80], b[80], c[160], *result = c;
    int choise, i;
    do{
        printf("\t\t1 copy string.\n");
        printf("\t\t2 connect string.\n");
        printf("\t\t3 exit.\n");
        printf("\t\tinput a number(1-3)please!\n");
        scanf("%d", &choise);
    }while(choise < 1 || choise > 5);
    switch(choise){
    case 1:
        p = strcpy;
        break;
    case 2:
        p = strcat;
        break;
    case 3:
        goto down;
    }

    getchar();
    printf("input the first string please!\n");
    i = 0;
    scanf("%[^\n]", a), getchar(); //2， 在此处输入第一个字符串
    printf("input the second string please!\n");
    i = 0;
    scanf("%[^\n]", b), getchar(); // 3，在此处输入第二个字符串
    result = p(a, b); //4，此处调用函数
    printf("the result is %s\n", result);
    down:
      ;
    return 0;
}
