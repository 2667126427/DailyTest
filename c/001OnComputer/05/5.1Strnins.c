#include <stdio.h>
#include <string.h>
int strnins(char* s, char* t, int n) {
	char temp[1000]; // �洢Ҫ�����ǵĲ���
	if (n > (int)strlen(s)) {
		printf("Ŀ���ַ������Ȳ��㣡\n");
		return 0;
	}
	if (n < 0) {
		printf("����λ��Ӧ�ò�С��0��\n");
		return 0;
	}
	unsigned len = strlen(s);
	// ��N��ʼ��len�Ķ���Ҫ����Ӧ�ĵط��ƶ�
	for (unsigned i = n; i <= len; ++i) {
		temp[i - n] = s[i];
	}
	// �����ַ���
	for (unsigned i = 0; i <= strlen(t); ++i) {
		s[n + i] = t[i];
	}
	// ��ԭ���Ĳ���ȥ
	for (unsigned i = 0; i <= len - n; i++) {
		s[n + strlen(t) + i] = temp[i];
	}
	// ����ɹ�����1
	return 1;
}

int main(void) {
	char chs[1000];
	char ch[200];
	printf("������Ŀ���ַ�����");
	scanf("%[^\n]", chs);
	getchar();
	printf("������Ҫ������ַ�����");
	scanf("%[^\n]", ch);
	getchar();
	printf("������Ҫ�����λ�ã�");
	int index = 0;
	scanf("%d", &index);
	if (strnins(chs, ch, index)) {
		printf("%s\n", chs);
	}
	else {
		printf("����ʧ�ܣ�\n");
	}
	return 0;
}