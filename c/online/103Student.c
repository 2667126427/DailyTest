/*************************************************************************
	> File Name: 103Student.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月18日 星期四 13时29分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define ALL 3
typedef struct Student{
    int num;
    char name[19];
    double score;
}Stu;
typedef Stu* pStu;

void Input(pStu stus){
    for (int i = 0; i < ALL; ++i){
        scanf("%d %s %lf", &stus[i].num, stus[i].name, &stus[i].score);
    }

}

void Output(Stu stus[ALL]){
    for (int i = 0; i < ALL; ++i){
        printf("%d\t%-20s%f\n", stus[i].num, stus[i].name, stus[i].score);
    }
}

void Output_p(pStu stus){
    for (int i = 0; i < ALL; ++i){ 
        printf("%d\t%-20s%f\n", stus->num, stus->name, stus->score);
        ++stus;
    }
}

int main(void){
    int N  = 0;
    scanf("%d", &N);
    Stu stus[ALL];
    pStu p_stus = stus;
    for (int i = 0; i < N; ++i){
        Input(stus);
        Output(stus);
        Output_p(p_stus); 
    }
    return 0;
}
