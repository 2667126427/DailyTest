#include <stdio.h>
#include <string.h>
int strnins(char* s, char* t, int n) {
	char temp[1000]; // 存储要被覆盖的部分
	if (n > (int)strlen(s)) {
		printf("目标字符串长度不足！\n");
		return 0;
	}
	if (n < 0) {
		printf("插入位置应该不小于0！\n");
		return 0;
	}
	unsigned len = strlen(s);
	// 从N开始到len的都需要往相应的地方移动
	for (unsigned i = n; i <= len; ++i) {
		temp[i - n] = s[i];
	}
	// 插入字符串
	for (unsigned i = 0; i <= strlen(t); ++i) {
		s[n + i] = t[i];
	}
	// 将原来的补回去
	for (unsigned i = 0; i <= len - n; i++) {
		s[n + strlen(t) + i] = temp[i];
	}
	// 插入成功返回1
	return 1;
}

int main(void) {
	char chs[1000];
	char ch[200];
	printf("请输入目标字符串：");
	scanf("%[^\n]", chs);
	getchar();
	printf("请输入要插入的字符串：");
	scanf("%[^\n]", ch);
	getchar();
	printf("请输入要插入的位置：");
	int index = 0;
	scanf("%d", &index);
	if (strnins(chs, ch, index)) {
		printf("%s\n", chs);
	}
	else {
		printf("插入失败！\n");
	}
	return 0;
}