#include <stdio.h>
int main()
{
    char c;
    printf("ÇëÊäÈëÒ»¸ö×Ö·û£º");
    c = getchar();
    if (c >= 'A' && c <= 'Z')
    {
        c = c - 'A' + 'a';
    }
    putchar(c);
    return 0;
}
