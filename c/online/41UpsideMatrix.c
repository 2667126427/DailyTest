#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ROW 3
#define COL 4

int main(void) {
	int matrix[ROW][COL];
	int resMar[COL][ROW];
	for (int i = 0; i < ROW; ++i) {
		scanf("%d %d %d %d", &matrix[i][0], &matrix[i][1], &matrix[i][2], &matrix[i][3]);
		resMar[0][i] = matrix[i][0], resMar[1][i] = matrix[i][1];
		resMar[2][i] = matrix[i][2], resMar[3][i] = matrix[i][3];
	}
	for (int i = 0; i < ROW; i++) {
		printf("%5d%5d%5d%5d\n", matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
	}
	printf("\n");
	for (int i = 0; i < COL; i++) {
		printf("%5d%5d%5d\n", resMar[i][0], resMar[i][1], resMar[i][2]);
	}
	return 0;
}