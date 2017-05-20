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
    float e_lang;
    float math;
    float phy;
    float c_lang;
    float sum;
    float ave;
    Stu *next;
}Stu;
typedef Stu* pStu;
char Select(void);
pStu CreateNode();
void Create(pStu*head);
void OutInfo(const pStu head);
void Change(pStu head);
void OutAll(const pStu head);
int main(void){
    pStu head = NULL;
    int flag = 1;
    while (flag != 0){
        switch (Select()){
        case ('0'):
            flag = 0;
            break;
        case ('1'):
            Create(&head);
            break;
        case ('2'):
            OutInfo(head);
            break;
        case ('3'):
            Change(head);
            break;
        case ('4'):
            OutAll(head);
            break;
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
    printf("输入%s的英语成绩：", temp->name);
    scanf("%f", &temp->e_lang);
    printf("输入%s的数学成绩：", temp->name);
    scanf("%f", &temp->math);
    printf("输入%s的物理成绩：", temp->name);
    scanf("%f", &temp->phy);
    printf("输入%s的C语言成绩：", temp->name);
    scanf("%f", &temp->c_lang);
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
            null = 0;
        }
        else if (!null && flag){
            temp =  temp->next = CreateNode();
        }
    }
}
void OutInfo(const pStu head){
    pStu temp = head;
    while (temp){
        printf("学号：%s\t姓名：%s\t英语：%.2f\t数学：%.2f\t物理：%.2f\tC语言：%.2f\n", temp->no, temp->name,
               temp->e_lang, temp->math, temp->phy, temp->c_lang);
        temp = temp->next;
    }
}
void OutAll(const pStu head){
    pStu temp = head;
    while (temp){
        printf("学号：%s\t姓名：%s\t英语：%.2f\t数学：%.2f\t物理：%.2f\tC语言：%.2f\t总分：%.2f\t平均分：%.2f\n", temp->no, temp->name,
               temp->e_lang, temp->math, temp->phy, temp->c_lang, temp->sum, temp->ave);
        temp = temp->next;
    }
}
void Change(const pStu head){
    pStu temp = head;
    printf("请输入学号：");
    char num[20];
    scanf("%s", num);
    while(temp){
        if (strcmp(temp->no, num) == 0){
            printf("请输入要修改的科目：\n");
            printf("1:英语;2：数学;3：物理;4：C语言\n");
            int course;
            scanf("%d", &course);
            printf("修改为：");
            float score = 0;
            scanf("%f", &score);
            switch(course){
                case 1:
                    temp->e_lang = score;
                    break;
                case 2:
                    temp->math = score;
                    break;
                case 3:
                    temp->phy = score;
                    break;
                case 4:
                    temp->c_lang = score;
                    break;
                default:
                    printf("输入不合理，修改失败");
            }
            temp->sum = temp->e_lang + temp->math + temp->phy + temp->c_lang;
            temp->ave = temp->sum / 4;
            return;
        }
        temp = temp->next;
    }
    printf("无此学生.\n");
}

