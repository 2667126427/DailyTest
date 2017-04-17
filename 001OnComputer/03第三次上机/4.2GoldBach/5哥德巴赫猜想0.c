#include <stdio.h>

int IsPrime(int N) {
	for (int i = 3; i <= N * 0.5; ++i) {
		if (N % i == 0) {
			return 0;
		}
		++i;
	}
	return 1;
}
int GetPrime(int N) {
	if (N == 4){
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
	int temp = 0;
	int t = 0;
	printf("Please enter a even number greater than 3:");
	scanf("%d", &temp);
	t = GetPrime(temp);
	printf("%d = %d + %d\n", temp, t, temp - t);

	return 0;
}