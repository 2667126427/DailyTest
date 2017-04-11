#include <stdio.h>
#define Swap(a, b) {a ^= b; b^= a; a ^= b;}

int main()
{
    int a = 0, b = 0;
    int count = 0;
    while (scanf("%d %d", &a, &b) != EOF)
    {
        ++count;
        printf("Case %d:\n", count);
        printf("Before Swap:a=%d b=%d\n", a, b);
        Swap(a, b);
        printf("After Swap:a=%d b=%d\n\n", a, b);
    }
    return 0;
}
