#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ROW 3
#define COL 4

int main(void) {
	int matrix[ROW][COL];
	int resMar[COL][ROW];
	for (int i = 0; i < ROW; ++i) {
		// 每次输入4个数据
		scanf("%d %d %d %d", &matrix[i][0], &matrix[i][1], &matrix[i][2], &matrix[i][3]);
		// 顺便倒腾到转置矩阵里面去
		resMar[0][i] = matrix[i][0], resMar[1][i] = matrix[i][1];
		resMar[2][i] = matrix[i][2], resMar[3][i] = matrix[i][3];
	}
	for (int i = 0; i < ROW; i++) {// 输出原矩阵
		printf("%d %d %d %d\n", matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
	}
	printf("\n");
	for (int i = 0; i < COL; i++) {// 输出转置矩阵
		printf("%d %d %d\n", resMar[i][0], resMar[i][1], resMar[i][2]);
	}
	return 0;
}