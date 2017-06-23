#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int TransNum(const char* num){
    int res = 0;
    int len = strlen(num);
    for (int i = 0; i < len; ++i){
        if (num[i] == '-' && i == 0)continue;
        if (num[i]>'9' || num[i] < '0'){
            printf("Invalid number: %s\n", num);
            exit(0);
        }
        res = res * 10 + num[i] - '0';
    }
    if (num[0] == '-')return -res;
    return res;
}

int main(int argc, char* argv[])
{
    if (argc != 3){
        printf("Please enter correct parameters.\n");
        exit(0);
    }
    int a = TransNum(argv[1]), b = TransNum(argv[2]);
    printf("Bigger number is %d\n", a > b ? a : b);
    return 0;
}
