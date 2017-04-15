#include <stdio.h>

void mycpy(char* s, char* t, int n){
    static int i = 0;
    for (i = 0; i < n; ++i){
        s[i] = t[i];
    }
    s[i] = '\0';
}

int main()
{
    char t[1000];
    char s[1000];
    int N = 0;
    int k = 0;
    scanf("%d",&N);
    getchar();
    for (int i = 0; i < N; ++i){
        scanf("%[^\n]", t);
        scanf("%d", &k);
        getchar();
        mycpy(s, t, k);
        printf("%s\n", s);
    }

    return 0;
}
