#include <stdio.h>
#define M 10
#define N 3
int main(void) {
	int a[M], b[M];
	int i, j, k;
	for (i = 0; i < M; ++i)
		a[i] = i + 1;
	for (i = M, j = 0; i > 1; i--) {
		for (k = 1; k <= N; k++) {
			++j; // 下一个
			if (j == M)j = 0; // 编号为M也就是0，走了一圈
			while (a[j ? j - 1 : M - 1] == 0) { // 当没有找到符合的下标时
				if (j == M - 1)j = 0; // 如果到了结尾下一个是0而不是M
				else ++j; // 没有到尾部加一
			}
		}
		b[M - i] = a[j ? j - 1 : M - 1]; // 和while里的保持一致
		a[j ? j - 1 : M - 1] = 0; // 找到的地方置0
	}
	// 输出
	for (i = 0; i < M - 1; i++)
		printf("%6d", b[i]); 
	for (i = 0; i < M; ++i) {
		if (a[i])
		{
			printf("%6d\n", a[i]);
			break;
		}
	}
	return 0;
}
