#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

void Print(const int N) {
	char chs[sizeof(int) * 8 + 1] = { 0, };
	int count = sizeof(int) * 8 - 1;
	unsigned int temp = N;
	while (count >= 0) {
		chs[count--] = temp % 2 + '0';
		temp /= 2;
	}
	printf("%s\n", chs);
}

int main(void) {
    int N;
		scanf("%d", &N);

		Print(N);
	return 0;
}
