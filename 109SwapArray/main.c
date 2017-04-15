#include <stdio.h>

void Read(int* arr, const int n){
    for (int i = 0; i < n; ++i){
        scanf("%d", &arr[i]);
    }
}

void SwapArr(int* arr, const int n, const int k){
    int t = 0;
    for (int i = k; i > 0; --i){
        for (int j = 0; j < n - k; ++j){
            // 单个向后移动，类似冒泡排序
            t = arr[i + j - 1];
            arr[i + j - 1] = arr[i + j];
            arr[i + j] = t;
        }
    }
}

void Print(const int* arr, const int n){
    printf("%d", arr[0]);
    for (int i = 1; i < n; ++i){
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[60] = { 0, };
    int n = 0, k = 0;
    while (scanf("%d %d", &n, &k) != EOF){
        Read(arr, n);
        SwapArr(arr, n, k);
        Print(arr, n);
    }
    return 0;
}
