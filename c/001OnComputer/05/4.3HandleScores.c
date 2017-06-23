#include <stdio.h>
#include <malloc.h> // ���ٿռ�
// ʹ�ýṹ�壬������
typedef struct Stu {
	char name[20]; // ����
	int sco; // ����
}Stu;
typedef Stu *pStu;
// ��������
void InputStu(pStu stus, const int N) {
	for (int i = 0; i < N; ++i) {
		scanf("%s %d", stus[i].name, &stus[i].sco);
	}
}
// �������Ч��
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
	}// ����ʱ_end_start
	stus[e] = key;
	Sort(stus, start, s - 1);
	Sort(stus, s + 1, end);
}
// ��Ҫ�����
void Print(pStu stus, int N) {
	for (int i = 0; i < N; i++) {
		// %-20s
		printf("%-20s %d\n", stus[i].name, stus[i].sco);
	}
	printf("\n");// Ҫ��Ŀ���
}
// ���ң�stusѧ�����飬N��������searҪ�ҵķ���
void Search(pStu stus, const int N, const int sear) {
	// result�洢���˳��䵱�Ƿ���ҵ��ı�־
	int result = -1;
	int mid = N / 2;
	int first = 0;
	int last = N- 1;
	// ���������Ѿ���������ʹ�ö��ֲ���
	while (first <= last) {
		mid = (first + last) / 2;
		if (stus[mid].sco == sear) {// �ҵ�����
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
		printf("%-20s %d\n", stus[result].name, stus[result].sco);// ��ӡ���
	}
	else {
		printf("Not found!\n");
	}
}
int main(void) {
	int N = 0;
	printf("������ѧ��������");
	scanf("%d", &N);
	pStu stus = (pStu)malloc(N * sizeof(Stu));// ��������
	InputStu(stus, N); // ����
	Sort(stus, 0, N - 1); // ����
	Print(stus, N); // ��ӡ�ĺõ�
	int sear = 0;// Ҫ���ҵ���
	printf("������Ҫ���ҵ�ѧ���ķ�����");
	scanf("%d", &sear);
	Search(stus, N, sear);
	free(stus);
	return 0;
}