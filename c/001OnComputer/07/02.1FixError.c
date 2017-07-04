/*************************************************************************
	> File Name: 02.1FixError.c
	> Author: Yaning Wang, CS1607
	> Mail: wangyanign6166@gmail.com
	> School: HUST
	> Created Time: 2017年05月15日 星期一 23时35分19秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
struct s_list{
    int data;
    struct s_list* next;
};
// 修改可以使用二级指针或者改变返回值类型，这里选择使用二级指针。
void create_list(struct s_list**head_p, int*p);
int main(void){
    struct s_list*head = NULL, *p;
    int s[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    create_list(&head, s);
    p = head;
    while(p){
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}
void create_list(struct s_list**headp, int*p){
    struct s_list*loc_head = NULL, *tail;
    if (p[0] == 0){
        ;
    }
    else{
        loc_head = (struct s_list*)malloc(sizeof(struct s_list));
        loc_head->data = *p++;
        tail = loc_head;
        while(*p){
            tail->next = (struct s_list*)malloc(sizeof(struct s_list));
            tail = tail->next;
            tail->data = *p++;
        }
        tail->next = NULL;
    }
    *headp = loc_head;
}
// 出现的错误，没有输出数据，原因：函数传参是传值，这里指指针的值，
// 指针的值改变是局部变量的改变，而不能影响main函数中的值
