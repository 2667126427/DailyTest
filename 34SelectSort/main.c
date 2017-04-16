#include <stdio.h>
#include <malloc.h>
void Read(int* arr, int N){
    for (int i = 0; i < N; ++i){
        scanf("%d", &arr[i]);
    }
}

void SeleSort(int*arr, int N){
    int min = 0;
    for (int i = 0; i < N; ++i){
        min = i;
        for (int j = i + 1; j < N; ++j){
            if (arr[j] < arr[min]){
                min = j;
            }
        }
        if (min != i){
            int t = arr[i];
            arr[i] = arr[min];
            arr[min] = t;
        }
    }
}

void Print(int* arr, int N){
    printf("%d", arr[0]);
    for (int i = 1; i < N; ++i){
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int main()
{
    int N = 0;
    int *arr = NULL;
    while ((scanf("%d", &N), N) != 0){
        arr = (int*)malloc(N * sizeof(int));
        Read(arr, N);
        SeleSort(arr, N);
        Print(arr, N);
        free(arr);
        arr = NULL;
    }
    return 0;
}
