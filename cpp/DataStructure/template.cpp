/* Linear Table On Sequence Structure */
#include <cstdio>
#include <cstdlib>
// cout to print the elem
#include <iostream>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

void cls() {
    printf("\033c");
}


/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
struct SqList{  //顺序表（顺序结构）的定义
    ElemType *elem = nullptr;
    int length = 0;
    int listsize = 0;

    SqList &operator=(const SqList &l) {
        elem = l.elem;
        length = l.length;
        listsize = l.listsize;
        return *this;
    }

};
/*-----page 19 on textbook ---------*/
status IntiaList(SqList & L);
status DestroyList(SqList & L);
status ClearList(SqList &L);
status ListEmpty(const SqList &L);
int ListLength(const SqList &L);
status GetElem(const SqList &L, const int &i, ElemType &e);
status LocateElem(const SqList &L, const ElemType &e, int &index, bool (*compare)(const ElemType &a, const ElemType &b)); //简化过
status PriorElem(const SqList &L, const ElemType &cur, ElemType & pre_e);
status NextElem(const SqList &L, const ElemType &cur,ElemType &next_e);
status ListInsert(SqList &L, const int &i, const ElemType &e);
status ListDelete(SqList &L, const int &i, ElemType &e);
status ListTrabverse(const SqList &L, void (*visit)(const ElemType &elem));  //简化过
/*--------------------------------------------*/
void visit(const ElemType &elem) {
    std::cout << elem << std::endl;
}

bool compare(const ElemType &a, const ElemType &b) {
    return a == b;
}

int main(){
    int op=1;
    ElemType cur, next, pre, elem;
    int index;
    SqList lists[100];
    while(op){
        cls();
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("          1. IntiaList       7. LocateElem\n");
        printf("          2. DestroyList     8. PriorElem\n");
        printf("          3. ClearList       9. NextElem \n");
    printf("          4. ListEmpty     10. ListInsert\n");
    printf("          5. ListLength     11. ListDelete\n");
    printf("          6. GetElem       12. ListTrabverse\n");
    printf("          0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~12]:");
    scanf("%d",&op);
    int l_index = 0;
    if (op) {
        printf("Please enter the list you want to operate:");
        scanf("%d", &l_index);
    }
    SqList &L = lists[l_index];
    switch(op) {
        case 1:
            printf("\nIntiaList功能！\n");
            if(IntiaList(L)==OK) printf("线性表创建成功！\n");
            else printf("线性表创建失败！\n");
            getchar();getchar();
            break;
        case 2:
            printf("\nDestroyList功能！\n");
            if (DestroyList(L)) printf("The list has been destroyed.\n");
            else printf("Destroyed the list failed.\n");
            getchar();getchar();
            break;
        case 3:
            printf("\nClearList功能！\n");
            if (ClearList(L)) printf("CLear the list successfully.\n");
            else printf("Clear the list failed.\n");
            getchar();getchar();
            break;
        case 4:
            printf("\nListEmpty功能！\n");
            if (ListEmpty(L)) printf("The list is empty.\n");
            else printf("The list is not empty.\n");
            getchar();getchar();
            break;
        case 5:
            printf("\nListLength功能！\n");
            printf("The length of the list is %d.\n", ListLength(L));
            getchar();getchar();
            break;
        case 6:
            printf("\nGetElem功能！\n");
            printf("PLease enter the index of the elem:");
            scanf("%d", &index);
            if (GetElem(L, index, elem) == OK) {
                std::cout << "The element is:" << elem << "\n";
            }
            else printf("Error occured.\n");
            getchar();getchar();
            break;
        case 7:
            printf("\nLocateElem功能！\n");
            printf("Please enter the elem you want to locate:");
            std::cin >> elem;
            if (LocateElem(L, elem, index, compare))
                printf("The locate of the elem is: %d\n", index);
            else printf("Error occcured.\n");
            getchar();getchar();
            break;
        case 8:
            printf("\nPriorElem功能！\n");
            printf("Please enter the element you need to operate with:");
            std::cin >> cur;
            if (PriorElem(L, cur, pre) == OK) {
                std::cout << "The element before you enter is " << elem << "\n";
            } else {
                printf("Error occured.\n");
            }
            getchar();getchar();
            break;
        case 9:
            printf("\nNextElem功能！\n");
            printf("Please enter the element you want to operate with:");
            std::cin >> cur;
            if (NextElem(L, cur, next) == OK) std::cout << "The elemnt after you enter is " << next << "\n";
            else printf("Error occured.\n");
            getchar();getchar();
            break;
        case 10:
            printf("\nListInsert功能！\n");
            printf("Please enter elemnt you want to insert: ");
            std::cin >> elem;
            printf("Please enter the index you want to insert:");
            scanf("%d", &index);
            if (ListInsert(L, index, elem) == OK) printf("Insert the elemnt successfully.\n");
            else printf("Insert failed.\n");
            getchar();getchar();
            break;
        case 11:
            printf("\nListDelete功能！\n");
            printf("Please enter the index of element you want to delete:");
            scanf("%d", &index);
            if (ListDelete(L, index, elem) == OK) std::cout << "Delete " << elem << " successfully.\n";
            else printf("Delete element failed.\n");
            getchar();getchar();
            break;
        case 12:
            printf("\nListTrabverse功能！\n");
            // if(!ListTrabverse(L, visit)) printf("线性表是空表！\n");
            if (ListTrabverse(L, visit))
                printf("Trabverse the list successfully.\n");
            else printf("Trabverse the list failed.\n");
            getchar();getchar();
            break;
        case 0:
            break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");

    return 0;
}//end of main()
/*--------page 23 on textbook --------------------*/

status IntiaList(SqList &L) {
    if (L.elem != nullptr) {
        delete L.elem;
    }
    L.elem = new int[LIST_INIT_SIZE];
    if (L.elem == nullptr) {
        exit(OVERFLOW);
    }
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}


status DestroyList(SqList &L) {
    delete L.elem;
    L.listsize = 0;
    L.length = 0;

    return OK;
}

status ClearList(SqList &L) {
    if (L.elem == nullptr) {
        return ERROR;
    }

    L.length = 0;
    return OK;
}

status ListEmpty(const SqList &L) {
    return L.length == 0 ? TRUE : FALSE;
}

int ListLength(const SqList &L) {
    return L.length;
}

status GetElem(const SqList &L, const int &i, ElemType &e) {
    if (i < 1 || i > L.length) {
        return ERROR;
    }

    e = L.elem[i - 1];
    return OK;
}

status LocateElem(const SqList &L, const ElemType &e, int &index,
        bool (*compare)(const ElemType &a, const ElemType &b))  {
    for (int i = 0; i < L.length; ++i) {
        if (compare(L.elem[i], e)) {
            index = i + 1;
            return OK;
        }
    }

    index = 0;
    return ERROR;
}

status PriorElem(const SqList &L, const ElemType &cur, ElemType &pre_e) {
    if (L.elem == nullptr) {
        return ERROR;
    }

    for (int i = 0; i < L.length - 1; ++i) {
        if (L.elem[i + 1] == cur) {
            pre_e = L.elem[i];
            return OK;
        }
    }

    return ERROR;
}

status NextElem(const SqList &L, const ElemType &cur,ElemType &next_e) {
    if (L.elem == nullptr) {
        return ERROR;
    }

    for (int i = 1; i < L.length; ++i) {
        if (cur == L.elem[i - 1]) {
            next_e = L.elem[i];
            return OK;
        }
    }
    return ERROR;
}

void LargerList(SqList &L) {
    ElemType *elem = new int[L.listsize + LISTINCREMENT];
    if (elem == nullptr) {
        exit(OVERFLOW);
    }

    for (int i = 0 ; i < L.length; ++i) {
        elem[i] = L.elem[i];
    }
    delete L.elem;
    L.elem = elem;
    L.listsize = L.listsize + LISTINCREMENT;
}

status ListInsert(SqList &L, const int &i, const ElemType &e) {
    if (L.elem == nullptr) {
        //exit(0);
        return ERROR;
    }

    if (i < 1 || i > L.length + 1) {
        //exit(0);
        return ERROR;
    }
    // if the list is full, larger the array;
    if (L.listsize == L.length) {
        LargerList(L);
    }
    // 1 2 3 4, insert (3, 1), index
    for (int index = L.length; index >= i - 1; --index) {
        L.elem[index] = L.elem[index - 1];
    }
    L.elem[i - 1] = e;
    ++L.length;

    return OK;
}

status ListDelete(SqList &L, const int &i, ElemType &e) {
    if (i < 1 || i > L.length) {
        return ERROR;
    }
    // 1 2 3 4, delele 2, index in base array is 1
    e = L.elem[i -1];

    for (int index = i - 1; index < L.length - 1; ++index) {
        L.elem[index] = L.elem[index + 1];
    }
    --L.length;
    return OK;
}

status ListTrabverse(const SqList &L, void (*visit)(const ElemType &elem)) {
    for (int i = 0; i < L.length; ++i) {
        visit(L.elem[i]);
    }
    return OK;
}

