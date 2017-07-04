/*************************************************************************
	> File Name: 104Webpage.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月18日 星期四 13时08分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Web{
    char abbre[20];
    char full[40];
    char url[40];
    struct Web*next;
}Web;
typedef Web* pWeb;
void Input(pWeb*head, const int N){
    pWeb temp = NULL;
    pWeb last = NULL;
    for (int i = 0; i < N; ++i){
        temp = (pWeb)malloc(sizeof(Web));
        scanf("%s %s %s", temp->abbre, temp->full, temp->url);
        temp->next = NULL;
        if (i == 0){
            *head = last = temp;
        }
        else{
            last = last->next = temp;
        }
    }
}

void Output(const pWeb head){
    pWeb temp = head;
    while (temp){
        printf("%-20s%-40s%s\n", temp->abbre, temp->full, temp->url);
        temp = temp->next;
    }
}

void Swap(pWeb s1, pWeb s2){
    Web t = *s1;
    *s1 = *s2;
    *s2 = t;
    t.next = s1->next;
    s1->next = s2->next;
    s2->next = t.next;
}

void Sort(pWeb head){
    pWeb webi = head;
    pWeb webj = NULL;
    pWeb min = NULL;
    while (webi){
        min = webi;
        webj = webi->next;
        while (webj){
            if (strcmp(webj->abbre, min->abbre) < 0){
                min = webj;
            }
            webj = webj->next;
        }
        if (webi != min){
           Swap(webi, min);
        }
        webi = webi->next;
    }
}

int main(void){
    int N = 0;
    scanf("%d", &N);
    pWeb head = NULL;
    Input(&head, N);
    Output(head);
    printf("\n");
    Sort(head);
    Output(head);
    
    return 0;
}
