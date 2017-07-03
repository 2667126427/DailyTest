#include <stdio.h>

void Print(int* nums){
    for (int i = 0; i < 10; ++i){
        printf("Number %d: %d\n", i, nums[i]);
    }
}

int main()
{
    int nums[10] = { 0, };
    int _char = 0;
    int other = 0;
    char ch;
    while ((ch = getchar()) != '#'){
        if (ch >= '0' && ch <= '9'){
            ++nums[ch - '0'];
        }
        else if ((ch >= 'a' && ch <= 'z')||(ch >= 'A' && ch <= 'Z')){
            ++_char;
        }
        else{
            ++other;
        }
    }
    Print(nums);
    printf("characters: %d\nother: %d\n", _char, other);
    return 0;
}
