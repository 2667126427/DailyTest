/*************************************************************************
	> File Name: 99HandleScore.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月17日 星期三 23时01分35秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Stu{
    char no[15];
    char name[20];
    float e_lang;
    float math;
    float phy;
    float c_lang;
    float sum;
    float ave;
    struct Stu* next;
}Stu;
typedef Stu* pStu;

void Input(pStu* head, int sum){
    pStu temp = NULL;
    pStu last = NULL;
    for (int i = 0; i < sum; ++i){
        temp = (pStu)malloc(sizeof(Stu));
        scanf("%s %s %f %f %f %f", temp->no, temp->name, 
              &temp->e_lang, &temp->math, &temp->phy, &temp->c_lang);
        temp->sum = temp->e_lang + temp->math + temp->phy + temp->c_lang;
        temp->ave = temp->sum / 4;
        temp->next = NULL;
        if (i == 0){
            *head = temp;
            last = temp;
        }
        else{
            last = last->next = temp;
        }
    }
}

void OutputAll(const pStu head){
    printf("%-15s%-20s%-10s%-10s%-10s%-10s\n", "ID", "Name", "English",
          "Math", "Physics", "C");
    pStu temp = head;
    while (temp){
        printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n", temp->no, temp->name,
               temp->e_lang, temp->math, temp->phy, temp->c_lang);
        temp = temp->next;
    }
    printf("\n");
}
void Change(pStu head, const int sum){
    char no[15];
    char course[10];
    float score;
    pStu temp = head;
    for (int i = 0; i < sum; ++i){
        temp = head;
        scanf("%s %s %f", no, course, &score); 
        while (temp){
            if (strcmp(no, temp->no) == 0){
                switch (course[0]){
                case ('E'):
                    temp->e_lang = score;
                    break;
                case ('M'):
                    temp->math = score;
                    break;
                case ('P'):
                    temp->phy = score;
                    break;
                case ('C'):
                    temp->c_lang = score;
                    break;
                }
                temp->sum = temp->e_lang + temp->math + temp->phy + temp->c_lang;
                temp->ave = temp->sum / 4;
                break;
            }
            temp = temp->next;
        }
    }
}
void PrintAveSum(const pStu head){
    pStu temp = head;
    printf("SumAndAvg:\n");
    printf("%-15s%-20s%-10s%-10s\n", "ID", "Name", "SUM", "AVG");
    while (temp){
        printf("%-15s%-20s%-10.2f%-10.2f\n", temp->no, temp->name,
              temp->sum, temp->ave);
        temp = temp->next;
    }
    printf("\n");
}

void Swap(pStu s1, pStu s2){
    Stu t = *s1;
    *s1 = *s2;
    *s2 = t;
    t.next = s1->next;
    s1->next = s2->next;
    s2->next = t.next;
}

int ave_comp(pStu s1, pStu s2){
    return s1->ave < s2->ave;
}

void Sort(pStu head, int(*comp)(pStu s1, pStu s2)){
    pStu min = NULL;
    pStu stui = head;
    pStu stuj = NULL;
    while (stui){
        min = stui;
        stuj = stui->next;
        while (stuj){
            if (comp(stuj, min)){
                min = stuj;
            } 
            stuj = stuj->next;
        }
        if (stui != min){
            Swap(stui, min);
        }
        stui = stui->next;
    }
}
void PrintAve(const pStu head){
    printf("%s\n", "Sort:");
    printf("%-15s%-20s%-10s\n", "ID", "Name", "AVG");
    pStu temp = head;
    while (temp){
        printf("%-15s%-20s%-10.2f\n", temp->no, temp->name, temp->ave);
        temp = temp->next;
    }
    printf("\n");
}
int main(void){
    int sum_stu = 0;
    scanf("%d", &sum_stu);
    pStu head = NULL;
    Input(&head, sum_stu);
    OutputAll(head); 
    int change = 0;
    scanf("%d", &change);
    Change(head, change);
    printf("Alter:\n");
    OutputAll(head); 
    PrintAveSum(head);
    Sort(head, ave_comp);
    PrintAve(head);

    return 0;
}
