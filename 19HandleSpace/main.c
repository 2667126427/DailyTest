#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* HandleSpace(char* target)
{
    static char result[1000]; // don't need to worry to be freeed by system;
    int index = 0;

    for (int i = 0; i < strlen(target); ++i)
    {
        // judge if the character fit the requirements;
        if (target[i] != ' ' || (target[i] == ' ' && target[i + 1] != ' '))
        {
            // then get the value
            result[index] = target[i];
            ++index;
        }
    }
    // handle the end
    result[index] = '\0';
    return result;
}

int main()
{
    int N = 0;
    // nonsense how long the string will be;
    char test[1000];
    scanf("%d", &N);
    // first time I don't add this code and there is an error;
    getchar();

    for (int i = 0; i < N; ++i)
    {
        // don't think of using reguler expression
        scanf("%[^\n]", test);
        getchar();
        // handle string
        printf("%s\n", HandleSpace(test));
    }

    return 0;
}
