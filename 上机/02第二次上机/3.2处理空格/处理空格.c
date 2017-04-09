#include <stdio.h>
#include <string.h>

int main()
{
    char str[1000];
    char result[1000];
    int count = 0;
    printf("Please enter a string:");
    scanf("%[^\n]", str);

    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[i] != ' ' || (str[i] == ' ' && str[i + 1] != ' '))
        {
            result[count] = str[i];
            ++count;
        }
    }
    result[count] = '\0';

    printf("%s\n", result);

    return 0;
}
