/*************************************************************************
	> File Name: 01.1CheckOut.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月22日 星期一 11时23分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main(void){
    short a = 0x253f, b = 0x7b7d;
    char ch;
    FILE *fp1, *fp2;
    fp1 = fopen("./abc1.bin", "wb+");
    fp2 = fopen("./abc2.txt", "w+");
    fwrite(&a, sizeof(short), 1, fp1);
    fwrite(&b, sizeof(short), 1, fp1);
    fprintf(fp2, "%d %d", a, b);
    rewind(fp1); rewind(fp2);
    while ((ch = fgetc(fp1)) != EOF){
        putchar(ch);
    }
    putchar('\n');
    while ((ch = fgetc(fp2)) != EOF){
        putchar(ch);
    }
    putchar('\n');
    fclose(fp1);
    fclose(fp2);

    return 0;
}
