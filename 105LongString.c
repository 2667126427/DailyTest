/*************************************************************************
	> File Name: 105LongString.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月18日 星期四 12时33分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Char{
    char ch;
    Char* next;
}Char;
typedef Char* pChar;

int Input(pChar* head){
    char ch = 0;
    int size = 0;
    int isFirst = 1;
    pChar temp = NULL;
    pChar last = NULL;
    while ((ch = getchar()) != EOF){
        ++size;
        temp = (pChar)malloc(sizeof(Char));
        temp->ch = ch;
        temp->next = NULL;
        if (isFirst){
            *head = last = temp;
            isFirst = 0;
        }
        else{
            last = last->next = temp;
        }
    }
    return size;
}

void Output(const pChar head){
    pChar temp = head;
    while (temp){
        printf("%c", temp->ch);
        temp = temp->next;
    }
    /*printf("\n");*/
}

void MyCpy(char* str, const pChar head){
    pChar temp = head;
    while (temp){
        *str++ = temp->ch;
        temp = temp->next;
    }
    *str++ = '\0';
}


int main(void){
    pChar head = NULL;
    int size = 0;
    size = Input(&head);
    Output(head);
    printf("\n");
    char*str = (char*)malloc((size + 1) * sizeof(char));
    MyCpy(str, head);
    printf("%s", str);
    printf("\n");
    return 0;
}
