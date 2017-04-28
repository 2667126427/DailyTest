#include <stdio.h>
void Print(const int N) {
	char chs[sizeof(int) * 8 + 1] = { 0, }; // 根据系统选择chs大小
	int count = sizeof(int) * 8 - 1; // 调控字符数组的赋值
	unsigned int temp = N;
	while (count >= 0) { // 根据count来控制循环保证是32个0~31
		chs[count--] = temp % 2 + '0';
		temp /= 2;
	}
	printf("%s\n", chs); // 输出
}
int main(void) {
	int N;
	scanf("%d", &N); // 输入数据
	Print(N);
	return 0;
}
