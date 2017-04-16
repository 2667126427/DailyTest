#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define BEGIN 10
#define END 20
int IsPrime(int N) {
	for (int i = 3; i <= N * 0.5; ++i) {
		if (N % i == 0) {
			return 0;
		}
		++i;
	}
	return 1;
}
// 用来获取满足条件的N的第一个素数也是较小的
int GetPrime(int N) {
	// 考虑4的特殊性
	if (N == 4) {
		return 2;
	}
	for (int i = 3; i <= N * 0.5; ++i) {
		if (IsPrime(i) && IsPrime(N - i)) {
			return i;
		}
		++i;
	}
	return -1;
}
int main() {
	int numA = 0, numB = 0;
	int t = 0;
	numA = BEGIN;
	numB = END;
	printf("GOLDBACH'S CONJECTURE:\n");
	printf("Every even number n >= 4 is the sum of two primes.\n");
	// 判断初始值奇偶
	if (numA % 2 == 1) {
		++numA;
	}
	for (int i = numA; i <= numB; ++i) {
		t = GetPrime(i);
		printf("%d = %d + %d\n", i, t, i - t);
		++i;
	}
	return 0;
}