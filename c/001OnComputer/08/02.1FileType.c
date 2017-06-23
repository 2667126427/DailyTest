/*************************************************************************
	> File Name: 02.1FileType.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月22日 星期一 11时34分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    char ch;
    FILE *fp;
    if (argc != 2){
        printf("ARguments error!\n");
        exit(-1);
    }
    if ((fp = fopen(argv[1], "r")) == NULL){        /* fp指向filename */
        printf("Can't open %s file!\n", argv[1]);
        exit(-1);
    }
    // 根据优先级，ch得不到字符，修改加括号
    while ((ch = fgetc(fp)) != EOF){                /* 从fileame中读字符 */
        putchar(ch);                                /* 向显示器写字符 */
    }
    fclose(fp);                                     /* 关闭filename */
    return 0;
}
