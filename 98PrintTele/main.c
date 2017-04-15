#include <stdio.h>
#define CHANGE(c) ((c) % 2)

char* Upside(const char* str){
    static char _str[1000];
    int i = 0;
    while (str[i] != '\0'){
        if (str[i] >= 'A' && str[i] <= 'Z'){
            _str[i] = str[i] - 'A' + 'a';
        }
        else if (str[i] >= 'a' && str[i] <= 'z'){
            _str[i] = str[i] - 'a' + 'A';
        }
        else {
            _str[i] = str[i];
        }
        ++i;
    }
    _str[i] = '\0';
    return _str;
}

void Print(const char* str){
    if (CHANGE(str[0]) == 0){
        printf("%s\n", str);
    }
    else {
        printf("%s\n", Upside(str));
    }
}

int main() {
    char str[1000];
    while (scanf("%[^\n]", str) != EOF){
        getchar();
        Print(str);
    }
    return 0;
}
