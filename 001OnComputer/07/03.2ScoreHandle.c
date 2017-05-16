/*************************************************************************
> File Name: 03.2ScoreHandle.c
> Author: Yaning Wang, CS1607
> Mail: wangyanign6166@gmail.com
> School: HUST
> Created Time: 2017年05月16日 星期二 22时11分58秒
************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
typedef struct Stu{
    char no[11];
    char name[10];
    int e_lang;
    int math;
    int phy;
    int c_lang;
    int sum;
    double ave;
    Stu *next;
}Stu;
typedef Stu* pStu;
char Select(void);
pStu CreateNode();
void OutInfo(const pStu head);
void OutAll(const pStu head);
int main(void){
    pStu head = NULL;
    int flag = '1';
    while (flag != '0'){
        switch (Select()){
            case ('0'):
            break;
            case ('1'):
            default:
            printf("请重新输入：\n");
        }
    }
    return 0;
}
char Select(void){
    char flag[100];
    printf("输入编号进行操作：\n");
    printf("1：输入学生信息;\n");
    printf("2：输出学生信息;\n");
    printf("3：修改指定学生的指定信息;\n");
    printf("4：输出学生所有信息;\n");
    printf("0：结束程序。\n");
    scanf("%s", flag);
    if (strlen(flag) != 1)return '5';
    return flag[0];
}
pStu CreateNode(){
    pStu temp = (pStu)malloc(sizeof(Stu));
    if (temp == NULL){
        printf("分配空间失败！\n");
        exit(1);
    }
    printf("输入学号：");
    scanf("%s", temp->no);
    getchar();
    printf("输入姓名：");
    scanf("%s", temp->name);
    printf("输入英语成绩：");
    scanf("%d", &temp->e_lang);
    printf("输入数学成绩：");
    scanf("%d", &temp->math);
    printf("输入物理成绩：");
    scanf("%d", &temp->phy);
    printf("输入C语言成绩：");
    scanf("%d", &temp->c_lang);
    temp->sum = temp->e_lang + temp->math + temp->phy + temp->c_lang;
    temp->ave = temp->sum * 0.25;
    temp->next = NULL;
    return temp;
}
void Create(pStu* head){
    pStu temp = *head;
    int flag = 1;
    int null = (*head == NULL ? 1 : 0);
    while (flag){
        printf("是否添加？0：否，非0：是\n");
        scanf("%d", &flag);
        if (null && flag){
            *head = temp = CreateNode();
        }
        else if (flag && !null){
            temp =  temp->next = CreateNode();
        }
    }
}
void OutInfo(const pStu head){
    pStu temp = head;
    while (temp){
        printf("学号：%s\t姓名：%s\t英语：%d\t数学：%d\t物理：%d\tC语言：%d\n", temp->no, temp->name,
               temp->e_lang, temp->math, temp->phy, temp->c_lang);
        temp = temp->next;
    }
}
void OutAll(const pStu head){
    pStu temp = head;
    while (temp){
        printf("学号：%s\t姓名：%s\t英语：%d\t数学：%d\t物理：%d\tC语言：%d\t%d\t%.2f\n", temp->no, temp->name,
               temp->e_lang, temp->math, temp->phy, temp->c_lang, temp->sum, temp->ave);
        temp = temp->next;
    }
}
