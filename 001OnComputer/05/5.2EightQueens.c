#include <stdio.h>
#define MAX 8 // ���ûʺ�����
#define true 1
#define false 0
typedef int bool;
int count = 0; // ȫ�ּ�¼����
bool Check(int* arr, int depth) {
	int val_dif = 0; // ���Ҳ�
	int ind_dif = 0; // ���²�
	for (int i = 1; i <= depth; ++i) {
		for (int j = i + 1; j <= depth; j++) {
			val_dif = arr[i] - arr[j];
			ind_dif = i - j;
			if (val_dif == 0 || val_dif == ind_dif || val_dif == -ind_dif) {
				return false;
			}
		}
	}
	return true;
}
// ����������㷨����
void Search(int *arr, const int now) {
	for (int i = 1; i <= MAX; i++) {
		arr[now] = i;
		if (Check(arr, now)) {// ����Ѿ��ǵڰ˸�����������������ӡ
			if (now == MAX) {
				printf("%d", arr[1]);
				for (int i = 2; i <= MAX; i++) {
					printf(" %d", arr[i]);
				}
				printf("\n");
				++count;
				continue; // ����Ҫ����һ���������
			}// δ���ڰ˲���ǰ��ļ��������������
			Search(arr, now + 1);
		}
	}
}
int main(void) {
	int a[MAX + 1] = { 0, }; // ��Ϊ9ά����һά��Ҫ����д�ŷ���
	Search(a, 1); // �ӵ�һ�㿪ʼ��
	printf("һ��%d�������\n", count);
	return 0;
}