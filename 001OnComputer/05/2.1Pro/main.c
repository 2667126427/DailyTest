#include <stdio.h>
#define M 10
#define N 3
int main(void){
    int a[M], b[M];
    int i, j, k;
    for (i = 0; i < M; ++i)
        a[i] = i + 1;
    for (i = M, j = 0; i > 1; i--){
        for (k = 1; k <= N; k++){
            ++j;
            if (j == M)j = 0;
            while (a[j?j - 1 : M - 1] == 0){
                if (j == M - 1)j = 0;
                else ++j;
            }
        }
        b[M - i] = a[j?j - 1 : M - 1];
        a[j?j - 1 : M - 1] = 0;
    }
    for (i = 0; i < M - 1; i++)
        printf("%6d", b[i]);
    for(i = 0; i < M; ++i){
        if (a[i])
        {
            printf("%6d\n", a[i]);
            break;
        }
    }
    return 0;
}
