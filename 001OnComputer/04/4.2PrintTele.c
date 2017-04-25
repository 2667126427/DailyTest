#include <stdio.h>
#define CNANGE 0

void Print(char* str){
    #if CNANGE
    char*_str = str;
    while (*_str){
        if (*_str >= 'a' && *_str <= 'z'){
            printf("%c", *_str - 'a' + 'A');
        }
        else if(*_str >= 'A' && *_str <= 'Z'){
            printf("%c", *_str - 'A' + 'a');
        }
        else{
            printf("%c", *_str);
        }
        ++_str;
    }
    #else
    printf("%s", str);
    #endif // CNANGE
    printf("\n");
}
int main(void){
    char str[100];
    printf("Input a string:\n");
    scanf("%[^\n]", str);
    Print(str);
    return 0;
}
