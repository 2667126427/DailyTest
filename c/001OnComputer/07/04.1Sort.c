/*************************************************************************
	> File Name: 04.1Sort.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月27日 星期六 19时31分46秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define SORT_TYPE 0 // 0使用交换数据，1使用交换指针


typedef struct Stu{
    char no[11];
    char name[10];
    float e_lang;
    float math;
    float phy;
    float c_lang;
    float sum;
    float ave;
    struct Stu *next;
}Stu;
typedef Stu* pStu;
char Select(void);
pStu CreateNode();
void Create(pStu*head);
void OutInfo(const pStu head);
void Change(pStu head);
void OutAll(const pStu head);
void Sort_data(pStu*head);
void Sort_point(pStu*head);
void SwapData(pStu s1, pStu s2);
void SwapPoint(pStu s1, pStu s2, pStu l1, pStu l2);

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
        case ('5'):
            Sort_data(&head);
            break;
        case ('6'):
            Sort_point(&head);
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
    printf("5：数据排序;\n");
    printf("6：指针排序;\n");
    printf("0：结束程序。\n");
    scanf("%s", flag);
    if (strlen(flag) != 1)return 'a';
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
    if (!null) {
        while (temp->next) {
            temp = temp->next;
        }
    }
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

// 交换数据域
void SwapData(pStu s1, pStu s2) {
    Stu t = *s1;
    *s1 = *s2;
    *s2 = t;
    pStu tp = s1->next;
    s1->next = s2->next;
    s2->next = tp;
}

// 使用选择排序
void Sort_data(pStu*head) {
    pStu s1 = *head;
    pStu s2 = NULL;
    if (s1 == NULL){
        return;
    }
    pStu min = NULL; 
    while (s1 != NULL){
        min = s1;
        s2 = s1->next;
        while (s2!= NULL) {
            if (s2->ave < min->ave){
                min = s2;
            } 
            s2 = s2->next;
        }
        if (s1 != min){
            SwapData(s1, min);
        }
        s1 = s1->next;
    };
}
// 交换指针域
void SwapPoint(pStu s1, pStu s2, pStu l1, pStu l2){
    pStu tp = s1->next;
    s1->next = s2->next;
    s2->next = tp;
    tp = l1->next;
    l1->next = l2->next;
    l2->next = tp;
}

// 使用选择排序
void Sort_point(pStu*head){
    // 空结点返回
    if (*head == NULL) {
        return;
    }
    // 标记修改的是第一个结点的位置
    int first = 1;
    // 存储要交换的结点
    pStu s1 = *head;
    pStu s2 = NULL;
    // pre1存放s1前结点
    // pre2存放s2前结点
    pStu pre1 = (pStu)malloc(sizeof(Stu));
    pre1->next = *head;
    pStu pre2 = NULL;
    // 存放min前结点
    pStu min_pre;
    // 最小元素的结点
    pStu min = NULL;
    while (s1) {
        min = pre2 = s1;
        s2 = pre2->next;
        while (s2) {
            if (s2->ave < min->ave) {
                min = s2;
                min_pre = pre2;
            }
            s2 = s2->next;
            pre2 = pre2->next;
        }
        if (s1 != min){
            // 交换对应结点的指针
            SwapPoint(pre1, min_pre, s1, min);
        }
        if (first){
            // 修改的是第一个结点需要修改head指针的内容
            *head = pre1->next;
            first = 0;
        }
        // 向后移动
        s1 = s1->next;
        pre1 = pre1->next;
    }
    free(pre1);
}
