#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h> // 开辟空间
// 使用结构体，简化运算
typedef struct Stu {
	char name[20];
	int score;
}Stu;
typedef Stu *pStu;
// 输入数据
void InputStu(pStu stus, const int N) {
	for (int i = 0; i < N; ++i) {
		scanf("%s %d", stus[i].name, &stus[i].score);
	}
}
// 快排
void Sort(pStu stus, const int start, const int end) {
	if (start >= end) {
		return;
	}
	Stu key = stus[start];
	int _start = start;
	int _end = end;
	while (_start < _end) {
		while (stus[_start].score > key.score) {
			++_start;
		}
		while (stus[_end].score < key.score) {
			--_end;
		}
		if (_end > _start) {
			Stu t = stus[_end];
			stus[_end] = stus[_start];
			stus[_start] = t;
		}
	}
	stus[_end] = key;
	Sort(stus, start, _start - 1);
	Sort(stus, _start + 1, end);
}
// 按要求输出
void Print(pStu stus, int N) {
	for (int i = 0; i < N; i++) {
		// %-20s
		printf("%-20s %d\n", stus[i].name, stus[i].score);
	}
	// 要求的空行
	printf("\n");
}
// 查找
void Search(pStu stus, const int N, const int sear) {
	// 开辟数组存储要找的数
	int* target = (int*)malloc(sear * sizeof(int));
	int result = 0;
	int mid = N / 2;
	int first = 0;
	int last = 0;
	// 输入数据
	for (int i = 0; i < sear; i++) {
		scanf("%d", &target[i]);
	}
	for (int i = 0; i < sear; ++i) {
		first = 0;
		last = N - 1;
		result = -1;
		// 由于数据已经有序，所以使用二分查找
		while (first <= last) {
			mid = (first + last) / 2;
			if (stus[mid].score == target[i]) {
				result = mid;
				break;
			}
			else if (stus[mid].score > target[i]){
				first = mid + 1;
			}
			else {
				last = mid - 1;
			}
		}
		if (result != -1) {
			// 打印结果
			printf("%-20s %d\n", stus[result].name, stus[result].score);
		}
		else {
			printf("Not found!\n");
		}
	}
	// 释放空间
	free(target);
}

int main(void) {
	int N = 0;
	scanf("%d", &N);
	pStu stus = (pStu)malloc(N * sizeof(Stu));
	InputStu(stus, N);
	Sort(stus, 0, N - 1);
	Print(stus, N);
	// 要查找的个数
	int sear = 0;
	scanf("%d", &sear);
	Search(stus, N, sear);
	free(stus);
	return 0;
}
/*
5
ZhangChuanChao 88
XiaoHong 95
XiaoMing 90
LiSi 100
XiDaDa 83
4
90 88 83 59
*/