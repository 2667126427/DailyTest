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
    Stu* next;
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
                break;
            }
            temp = temp->next;
        }
    }
}
void PrintAveSum(const pStu head){
    pStu temp = head;
    printf("SumAndAvg:\n");
    printf("%-15s%-20s%-15s%-15s\n", "ID", ":Nmae", "SUM", "AVG");
    while (temp){
        printf("%-15s%-20s%-15.2f%-15.2f\n", temp->no, temp->name,
              temp->sum, temp->ave);
    }
    printf("\n");
}

void Sort(pStu head, int(*comp)(pStu s1, pStu s2)){
    pStu max = head;
    pStu stui = NULL;
    pStu stuj = NULL;
    while (stui){
        max = stui;
        stuj = stui->next;
        while (stuj){
            
            stuj = stuj->next;
        }

        stui = stui->next;
    }
}

int main(void){
    int sum_stu = 0;
    scanf("%d", &sum_stu);
    pStu head = NULL;
    Input(&head, sum_stu);
    OutputAll(head); 
    printf("Alter:\n");
    OutputAll(head);

    return 0;
}
