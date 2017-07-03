#include <stdio.h>
#include <string.h>

int main()
{
    int N = 0;
    char str[100];
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; ++i)
    {
        scanf("%[^\n]", str);
        getchar();
        printf("%d\n", (int)strlen(str));
    }

    return 0;
}
