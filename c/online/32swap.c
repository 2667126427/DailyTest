#include <stdio.h>
#define swap(a, b) {a ^= b; b^= a; a ^= b;}

int main()
{
    int a = 0, b = 0;
    int N = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d", &a, &b);
        swap(a, b);
        printf("%d %d\n", a, b);
    }
    return 0;
}
