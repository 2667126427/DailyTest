/* Linear Table On Sequence Structure */
#include "linearList.h"
#include <cstdio>

#define LEN 100

int main() {
    int temp = 0;
    int op = 1;
    int cur = 0, next = 0, pre = 0, elem = 0;
    int l_index = 0;
    int index;
    DS::linearList<int> lists[LEN];
    DS::Compare<int> comp = [](const int &a, const int &b) -> bool { return a == b; };
    DS::Visit<int> visit = [](const int &a) { std::cout << a << std::endl; };
    while (op != 0) {
        DS::cls();
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("          1. IntiaList       7. LocateElem\n");
        printf("          2. DestroyList     8. PriorElem\n");
        printf("          3. ClearList       9. NextElem \n");
        printf("          4. ListEmpty       10.ListInsert\n");
        printf("          5. ListLength      11.ListDelete\n");
        printf("          6. GetElem         12.ListTraverse\n");
        printf("          13.Change list  \n");
        printf("          0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    正在使用链表%2d\n", l_index);
        printf("    请选择你的操作[0~12]:");
        scanf("%d", &op);
        DS::linearList<int> &L = lists[l_index];
        switch (op) {
            case 1:
                printf("\nIntiaList功能！\n");
                if (L.InitaList() == OK) printf("线性表创建成功！\n");
                else printf("线性表创建失败！\n");
                getchar();
                getchar();
                break;
            case 2:
                printf("\nDestroyList功能！\n");
                if (L.DestroyList() == OK) printf("线性表销毁成功。\n");
                else printf("线性表销毁失败。\n");
                getchar();
                getchar();
                break;
            case 3:
                printf("\nClearList功能！\n");
                if (L.ClearList() == OK) printf("清除线性表成功。\n");
                else printf("清楚线性表失败。\n");
                getchar();
                getchar();
                break;
            case 4:
                printf("\nListEmpty功能！\n");
                if (L.ListEmpty()) printf("表为空。\n");
                else printf("表不为空。\n");
                getchar();
                getchar();
                break;
            case 5:
                printf("\nListLength功能！\n");
                printf("表长为%d.\n", L.ListLength());
                getchar();
                getchar();
                break;
            case 6:
                printf("\nGetElem功能！\n");
                printf("输入要获得的元素下标：");
                scanf("%d", &index);
                if (L.GetElem(index, elem) == OK) {
                    std::cout << "对应元素为：" << elem << "\n";
                } else printf("操作失败。\n");
                getchar();
                getchar();
                break;
            case 7:
                printf("\nLocateElem功能！\n");
                printf("输入你要定位的元素：");
                std::cin >> elem;
                if (L.LocateElem(elem, index, comp) == OK) {
                    printf("元素位置为：%d\n", index);
                } else {
                    printf("操作失败。\n");
                }
                getchar();
                getchar();
                break;
            case 8:
                printf("\nPriorElem功能！\n");
                printf("输入你要操作的元素：");
                std::cin >> cur;
                if (L.PriorElem(cur, pre, comp) == OK) {
                    std::cout << "操作结果为：" << elem << "\n";
                } else {
                    printf("操作失败。\n");
                }
                getchar();
                getchar();
                break;
            case 9:
                printf("\nNextElem功能！\n");
                printf("输入你要操作的元素：");
                std::cin >> cur;
                if (L.NextElem(cur, next, comp) == OK) {
                    std::cout << "操作结果为：" << next << "\n";
                } else {
                    printf("操作失败。\n");
                }
                getchar();
                getchar();
                break;
            case 10:
                printf("\nListInsert功能！\n");
                printf("输入你要插入的元素：");
                std::cin >> elem;
                printf("输入你要插入的位置：");
                scanf("%d", &index);
                if (L.ListInsert(index, elem) == OK) {
                    printf("插入成功。\n");
                } else {
                    printf("插入失败。\n");
                }
                getchar();
                getchar();
                break;
            case 11:
                printf("\nListDelete功能！\n");
                printf("输入你要删除元素的下标：");
                scanf("%d", &index);
                if (L.ListDelete(index, elem) == OK) {
                    std::cout << "删除" << elem << "成功。\n";
                } else {
                    printf("删除失败。\n");
                }
                getchar();
                getchar();
                break;
            case 12:
                printf("\nListTrabverse功能！\n");
                if (L.ListTraverse(visit)) {
                    printf("遍历成功。\n");
                } else {
                    printf("遍历失败。\n");
                }
                getchar();
                getchar();
                break;
            case 13:
                printf("输入你要操作的表：");
                scanf("%d", &temp);
                if (temp >= LEN || temp < 0) {
                    printf("切换失败。\n");
                } else {
                    l_index = temp;
                    printf("切换成功。\n");
                }
                getchar();
                getchar();
                break;
            case 0:
                break;
            default:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");

    return 0;
}//end of main()
/*--------page 23 on textbook --------------------*/
