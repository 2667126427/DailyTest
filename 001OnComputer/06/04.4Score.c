/*************************************************************************
	> File Name: 04.4Score.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月08日 星期一 20时43分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define M 2 //课程
#define N 2 //人数
#define GOOD 90
#define BAD 60
double ave_stu[N];//所有学生平均
double ave_cla[M]; // 课程平均
int low_cla[M]; // 低于班级平均
int low_ave[M]; // 低于课程平均
int good[M]; // 好学生
int bad[M]; // 坏学生

void AveStu(double (*scores)[M]){
    double sum;
    for(int i = 0; i < N; ++i){
        sum = 0;
        for (int j = 0; j < M; ++j){
            sum += *(*(scores + i) + j);
        }
        ave_stu[i] = sum / M;
    }
}
void AveCla(double (*scores)[M]){
    double sum = 0;
    for (int i = 0; i < M; ++i){
        sum = 0;
        for (int j = 0; j < N; ++j){
            sum += *(*(scores + j) + i);
        }
        *(ave_cla + i) = sum / N;
    }
}

void LowClass(double (*scores)[M]){
    for (int i = 0; i < M; ++i){
        for (int j = 0; j < N; ++j){
            if (*(*(scores + j) + i) < *(ave_cla + i)){
                ++low_cla[i];
            }
        }
    }
}

void BadAndGood(double (*scores)[M]){
    for (int i = 0; i < M; ++i){
        for (int j = 0; j < N; ++j){
            if (*(*(scores + j) + i) < BAD){
                ++*(bad + i);
            }
            if (*(*(scores + j) + i) >= GOOD){
                ++*(good + i);
            }
        }
    } 
}
void Print(double *arr, int n){
    printf("%f", arr[0]);
    for (int i = 1; i < n; ++i){
        printf(" %f", *(arr + i));
    }
    printf("\n");
}
void _Print(int *arr, int n){
    printf("%d ", arr[0]);
    for (int i = 1; i < n; ++i){
        printf(" %d", *(arr + i));
    }
    printf("\n");
}
int main(void){
    double scores[N][M]; // N个学生，M门课程
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < M; ++j){
            scanf("%lf", *(scores + i) + j);
        }
    }
    AveStu(scores);
    printf("学生平均：");
    Print(ave_stu, N);
    AveCla(scores);
    printf("课程平均：");
    Print(ave_cla, M);
    LowClass(scores);
    printf("低于班级平均：");
    _Print(low_cla, N);
    BadAndGood(scores);
    printf("好学生：");
    _Print(good, M);
    printf("坏学生：");
    _Print(bad, M);
    return 0;
}
