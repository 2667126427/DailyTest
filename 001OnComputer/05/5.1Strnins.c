#include <stdio.h>
#include <string.h>
int strnins(char* target, char* add, const int N) {
	char temp[1000];
	if (N > (int)strlen(target)) {
		printf("Ŀ���ַ������Ȳ��㣡\n");
		return 0;
	}
	if (N < 0) {
		printf("����λ��Ӧ�ò�С��0��\n");
		return 0;
	}
	unsigned len = strlen(target);
	for (unsigned i = N; i <= len; ++i) {
		temp[i - N] = target[i];
	}
	for (unsigned i = 0; i <= strlen(add); ++i) {
		target[N + i] = add[i];
	}
	for (unsigned i = 0; i <= len - N; i++) {
		target[N + strlen(add) + i] = temp[i];
	}
	return 1;
}

int main(void) {
	char chs[1000] = "Hello";
	char ch[] = " world.";
	if (strnins(chs, ch, 1)) {
		printf("%s\n", chs);
	}
	else {
		printf("����ʧ�ܣ�\n");
	}
		return 0;
}
