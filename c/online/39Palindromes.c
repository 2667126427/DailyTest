#include <stdio.h>
#include <string.h>
#define true 1
#define false 0
typedef int bool;

bool Parlind(char* start, char* end){
    if (start >= end){
        return true;
    }
    else if (*start == *end){
        return Parlind(start + 1, end - 1);
    }
    else{
        return false;
    }
}

int main()
{
    char str[1000];
    int N = 0;
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; ++i){
        scanf("%[^\n]", str);
        getchar();
        if (Parlind(&str[0], &str[strlen(str) - 1])){
            printf("Yes!\n");
        }
        else{
            printf("No!\n");
        }
    }
    return 0;
}
