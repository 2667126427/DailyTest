#include <stdio.h>
#include <malloc.h> // 开辟空间
// 使用结构体，简化运算
typedef struct Stu {
	char name[20]; // 名字
	int sco; // 分数
}Stu;
typedef Stu *pStu;
// 输入数据
void InputStu(pStu stus, const int N) {
	for (int i = 0; i < N; ++i) {
		scanf("%s %d", stus[i].name, &stus[i].sco);
	}
}
// 快排提高效率
void Sort(pStu stus, const int start, const int end) {
	if (start >= end) {
		return;
	}
	Stu key = stus[start];
	int s = start;
	int e = end;
	while (s < e) {
		while (stus[e].sco <= key.sco && s < e) --e;
		stus[s] = stus[e];
		while (stus[s].sco >= key.sco && s < e)++s;
		stus[e] = stus[s];
	}// 结束时_end_start
	stus[e] = key;
	Sort(stus, start, s - 1);
	Sort(stus, s + 1, end);
}
// 按要求输出
void Print(pStu stus, int N) {
	for (int i = 0; i < N; i++) {
		// %-20s
		printf("%-20s %d\n", stus[i].name, stus[i].sco);
	}
	printf("\n");// 要求的空行
}
// 查找：stus学生数组，N总人数，sear要找的分数
void Search(pStu stus, const int N, const int sear) {
	// result存储结果顺便充当是否查找到的标志
	int result = -1;
	int mid = N / 2;
	int first = 0;
	int last = N- 1;
	// 由于数据已经有序，所以使用二分查找
	while (first <= last) {
		mid = (first + last) / 2;
		if (stus[mid].sco == sear) {// 找到结束
			result = mid;
			break;
		}
		else if (stus[mid].sco > sear) {
			first = mid + 1;
		}
		else {
			last = mid - 1;
		}
	}
	if (result != -1) {
		printf("%-20s %d\n", stus[result].name, stus[result].sco);// 打印结果
	}
	else {
		printf("Not found!\n");
	}
}
int main(void) {
	int N = 0;
	printf("请输入学生个数：");
	scanf("%d", &N);
	pStu stus = (pStu)malloc(N * sizeof(Stu));// 开辟数组
	InputStu(stus, N); // 输入
	Sort(stus, 0, N - 1); // 排序
	Print(stus, N); // 打印拍好的
	int sear = 0;// 要查找的人
	printf("请输入要查找的学生的分数：");
	scanf("%d", &sear);
	Search(stus, N, sear);
	free(stus);
	return 0;
}