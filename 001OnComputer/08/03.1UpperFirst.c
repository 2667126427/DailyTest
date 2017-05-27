/*************************************************************************
	> File Name: 03.1UpperFirst.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月22日 星期一 11时48分07秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int isCharacter(char ch){
    return (ch >= 'a'&& ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int isLower(char ch){
    return ch >= 'a' && ch <= 'z';
}

char* Upper(char* str){
    char *temp = str;
    if (isLower(*temp)){
        *temp = *temp + 'A' - 'a';
    }
    temp++;
    while (*temp != '\0'){
        if (isCharacter(*temp) && !isCharacter(*(temp - 1))){
            if (isLower(*temp)){
                *temp = *temp + 'A' - 'a';
            }
        }
        ++temp;
    }
    return str;
}

int main(void){
    char str[1000];
    printf("Please enter a sentence:");
    scanf("%[^\n]", str);
    /*printf("%s\n", str);*/
    getchar();
    FILE* fp;
    fp = fopen("./test", "w+");
    /*printf("%s\n", Upper(str)); */
    fprintf(fp, "%s\n", Upper(str));
    fclose(fp);
    return 0;
}
