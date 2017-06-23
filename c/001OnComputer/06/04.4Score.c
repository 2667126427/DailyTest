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
#define N 4 //人数
#define GOOD 90
#define BAD 60
double ave_stu[N];//所有学生平均
double ave_cla[M]; // 课程平均
int low_cla[M]; // 低于班级平均
int low_ave[M]; // 低于课程平均
int good[M]; // 好学生
int bad[M]; // 坏学生
// 计算每个学生的平均分
void AveStu(double (*scores)[M]){
    double sum;
    for(int stu  = 0; stu < N; ++stu){
        sum = 0;
        for (int cla = 0; cla < M; ++cla){
            sum += *(*(scores + stu) + cla);
        }
        ave_stu[stu] = sum / M;
    }
}
// 计算每门课的平均分
void AveCla(double (*scores)[M]){
    double sum = 0;
    for (int cla = 0; cla < M; ++cla){
        sum = 0;
        for (int stu = 0; stu < N; ++stu){
            sum += *(*(scores + stu) + cla);
        }
        *(ave_cla + cla) = sum / N;
    }
}
// 计算低于班级平均分的人数
void LowClass(double (*scores)[M]){
    for (int cla = 0; cla < M; ++cla){
        for (int stu = 0; stu < N; ++stu){
            if (*(*(scores + stu) + cla) < *(ave_cla + cla)){
                ++low_cla[cla];
            }
        }
    }
}
// 计算每门课超过了90分的人数和低于60分的人数
void BadAndGood(double (*scores)[M]){
    for (int cla = 0; cla < M; ++cla){
        for (int stu = 0; stu < N; ++stu){
            if (*(*(scores + stu) + cla) < BAD){
                ++*(bad + cla);
            }
            if (*(*(scores + stu) + cla) >= GOOD){
                ++*(good + cla);
            }
        }
    } 
}
// 没有重载只好这么写了，其实应该写模板的
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
        printf("请输入第%d名学生的%d门课的成绩：", i + 1, M);
        for (int j = 0; j < M; ++j){
            scanf("%lf", *(scores + i) + j);
        }
    }
    AveStu(scores);
    printf("每个学生平均：");
    Print(ave_stu, N);
    AveCla(scores);
    printf("每门课程平均：");
    Print(ave_cla, M);
    LowClass(scores);
    printf("每门课低于班级平均：");
    _Print(low_cla, N);
    BadAndGood(scores);
    printf("每门课里分数不低于90的学生：");
    _Print(good, M);
    printf("每门课里分数低于60的学生：");
    _Print(bad, M);
    return 0;
}
