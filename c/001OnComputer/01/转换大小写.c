#include <stdio.h>
int main()
{
    char c;
    printf("������һ���ַ���");
    c = getchar();
    if (c >= 'A' && c <= 'Z')
    {
        c = c - 'A' + 'a';
    }
    putchar(c);
    return 0;
}
