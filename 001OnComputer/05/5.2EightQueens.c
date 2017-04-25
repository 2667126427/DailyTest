#include <stdio.h>
#define MAX 8 // 设置皇后总数
#define true 1
#define false 0
typedef int bool;
int count = 0; // 全局记录总数
bool Check(int* arr, int depth) {
	int val_dif = 0; // 左右差
	int ind_dif = 0; // 上下差
	for (int i = 1; i <= depth; ++i) {
		for (int j = i + 1; j <= depth; j++) {
			val_dif = arr[i] - arr[j];
			ind_dif = i - j;
			if (val_dif == 0 || val_dif == ind_dif || val_dif == -ind_dif) {
				return false;
			}
		}
	}
	return true;
}
// 和深度优先算法极似
void Search(int *arr, const int now) {
	for (int i = 1; i <= MAX; i++) {
		arr[now] = i;
		if (Check(arr, now)) {// 如果已经是第八个并且满足条件，打印
			if (now == MAX) {
				printf("%d", arr[1]);
				for (int i = 2; i <= MAX; i++) {
					printf(" %d", arr[i]);
				}
				printf("\n");
				++count;
				continue; // 不需要到下一层继续找了
			}// 未到第八层且前面的几层可以满足条件
			Search(arr, now + 1);
		}
	}
}
int main(void) {
	int a[MAX + 1] = { 0, }; // 定为9维，第一维不要啦，写着方便
	Search(a, 1); // 从第一层开始找
	printf("一共%d种情况。\n", count);
	return 0;
}