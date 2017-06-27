#include <stdio.h>
#include <stdlib.h>

typedef struct Mid
{
    char stu;
    int score;
}Mid;

Mid GetMiddle(int A, int B, int C)
{
    Mid mid;
    if (A == B || A == C || (B > A && A > C) || (C > A && A > B))
    {
        mid.stu = 'A';
        mid.score = A;
    }
    else if (B == C || (A > B && B > C) || (C > B && B > A))
    {
        mid.stu = 'B';
        mid.score = B;
    }
    else
    {
        mid.stu = 'C';
        mid.score = C;
    }

    return mid;
}

int main()
{
    int scoreA = 0;
    int scoreB = 0;
    int scoreC = 0;
    Mid mid;

    while (scanf("%d %d %d", &scoreA, &scoreB, &scoreC) != EOF)
    {
        mid = GetMiddle(scoreA, scoreB, scoreC);
        printf("%c:%d\n", mid.stu, mid.score);
    }

    return 0;
}
/*
A:90
B:88
C47
*/
