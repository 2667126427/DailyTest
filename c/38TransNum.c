#include <stdio.h>
#include <string.h>

int TransToTen(const char* str){
    int res = 0;
    int i = 0;
    while (str[i] != '\0'){
        if (str[i] >= 'A' && str[i] <= 'F'){
            res = res * 16 + str[i] - 'A' + 10;
        }
        else if (str[i] >= 'a' && str[i] <= 'z'){
            res = res * 16 + str[i] - 'a' + 10;
        }
        else{
            res = res * 16 + str[i] - '0';
        }
        ++i;
    }
    return res;
}

int main()
{
    char str[20];
    int N = 0;
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; ++i){
        scanf("0x%s", str);
        getchar();
        printf("%d\n", TransToTen(str));
    }

    return 0;
}
