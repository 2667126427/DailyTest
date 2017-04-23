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
	for (int i = 0; i < sizeof(int) * 8; i++) {
		printf("%c", chs[i]);
	}
	printf("\n");
}

int main(void) {
	int N = 0; 
	scanf("%d", &N);
	int *target = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) {
		scanf("%d", &target[i]);
	}
	for (int i = 0; i < N; i++) {
		Print(target[i]);
	}
	free(target);
	return 0;
}