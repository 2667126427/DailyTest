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
    struct Char* next;
}Char;
typedef Char* pChar;

// 输入字符串，返回值为输入的字符个数，便于下一步开辟空间
int Input(pChar* head){
    char ch = 0;
    int size = 0;
    int isFirst = 1;
    pChar temp = NULL;
    pChar last = NULL;
    while ((ch = getchar()) != '#'){
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

// 链表输出
void Output(const pChar head){
    pChar temp = head;
    while (temp){
        printf("%c", temp->ch);
        temp = temp->next;
    }
}

// 输入到字符串数组中
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
    // 输入并统计输入字符个数
    size = Input(&head);
    // 链表输出
    Output(head);
    printf("\n\n");
    // 开辟空间，+1是为了存储'\0'
    char*str = (char*)malloc((size + 1) * sizeof(char));
    // copy
    MyCpy(str, head);
    printf("%s", str);
    printf("\n");
    return 0;
}
