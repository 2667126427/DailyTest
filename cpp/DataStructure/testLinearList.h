#ifndef DATASTRUCTURE_TESTLINEARLIST_H
#define DATASTRUCTURE_TESTLINEARLIST_H

#include "linearList.h"
#include "status.h"

#define LEN 100

void testLinearList() {
    int temp = 0;
    long op = 1;
    int cur = 0, next = 0, pre = 0, elem = 0;
    int list_index = 0;
    int temp_index = 0;

    int index;
    LinearList<int> lists[LEN];
    Compare<int> comp = [](const int &a, const int &b) -> bool { return a == b; };
    Visit<int> visit = [](const int &a) { std::cout << a << std::endl; };

    while (op != 0) {
        cls();
        std::cout << "\n\n";
        std::cout << "      Menu for Linked Table On Chain Structure \n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "          1. IntiaList       7. LocateElem\n";
        std::cout << "          2. DestroyList     8. PriorElem\n";
        std::cout << "          3. ClearList       9. NextElem \n";
        std::cout << "          4. ListEmpty       10.ListInsert\n";
        std::cout << "          5. ListLength      11.ListDelete\n";
        std::cout << "          6. GetElem         12.ListTraverse\n";
        std::cout << "          13.Change list     14.Save List\n";
        std::cout << "          0. Exit\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "    list using: " << list_index << "\n";
        std::cout << "    please select your operation[0~14]:";
        std::cin >> op;
        auto &L = lists[list_index];
        switch (op) {
        case 1:
            std::cout << "InitaList Function\n";
            if (L.InitaList() == OK) std::cout << "Initialze successful.\n";
            else std::cout << "Initailze failed.\n";
            getchar();
            getchar();
            break;
        case 2:
            std::cout << "\nDestroyList Function\n";
            if (L.DestroyList() == OK) std::cout << "Destroy successfully.\n";
            else std::cout << "Destroy failed.\n";
            getchar();
            getchar();
            break;
        case 3:
            std::cout << "\nClearList Function\n";
            if (L.ClearList() == OK) std::cout << "Clear successfully\n";
            else std::cout << "CLear failed.\n";
            getchar();
            getchar();
            break;
        case 4:
            std::cout << "\nListEmpty Function\n";

            if (L.ListEmpty()) {
                std::cout << "The list is empty.\n";
            }
            else {
                std::cout << "The list is not empty.\n";
            }
            getchar();
            getchar();
            break;
        case 5:
            std::cout << "\nListLength Function\n";
            std::cout << "The length of list: " << L.ListLength() << std::endl;
            getchar();
            getchar();
            break;
        case 6:
            std::cout << "\nGetElem Function\n";
            std::cout << "Please enter the index: ";
            std::cin >> index;
            if (L.GetElem(index, elem) == OK) {
                std::cout << "Get the element: " << elem << "\n";
            }
            else std::cout << "Get element failed.\n";
            getchar();
            getchar();
            break;
        case 7:
            std::cout << "\nLocateElem Function\n";
            std::cout << "Please enter the element: ";
            std::cin >> elem;
            if (L.LocateElem(elem, index, comp) == OK) {
                std::cout << "The index of element:" << index << std::endl;
            }
            else {
                std::cout << "Locate element failed.\n";
            }
            getchar();
            getchar();
            break;
        case 8:
            std::cout << "\nPriorElem Function\n";
            std::cout << "Please enter the element: ";
            std::cin >> cur;
            if (L.PriorElem(cur, pre, comp) == OK) {
                std::cout << "Get the result: " << pre << "\n";
            }
            else {
                std::cout << "Get the element failed.\n";
            }
            getchar();
            getchar();
            break;
        case 9:
            std::cout << "\nNextElem Function\n";
            std::cout << "PLease enter the element: ";
            std::cin >> cur;
            if (L.NextElem(cur, next, comp) == OK) {
                std::cout << "Get the element: " << next << "\n";
            }
            else {
                std::cout << "Operate failed.\n";
            }
            getchar();
            getchar();
            break;
        case 10:
            std::cout << "\nListInsert Function\n";
            std::cout << "Please enter the element: ";
            std::cin >> elem;
            std::cout << "Please enter the index: ";
            scanf_s("%d", &index);
            if (L.ListInsert(index, elem) == OK) {
                std::cout << "Insert successfully.\n";
            }
            else {
                std::cout << "Insert failed.\n";
            }
            getchar();
            getchar();
            break;
        case 11:
            std::cout << "\nListDelete Function\n";
            std::cout << "Please enter the index: ";
            std::cin >> index;
            if (L.ListDelete(index, elem) == OK) {
                std::cout << "Delete " << elem << " successfullyy.\n";
            }
            else {
                std::cout << "Delete failed.\n";
            }
            getchar();
            getchar();
            break;
        case 12:
            std::cout << "\nListTraverse Function\n";
            if (L.ListTraverse(visit)) {
                std::cout << "Traverse successfully.\n";
            }
            else {
                std::cout << "Traverse failed.\n";
            }
            getchar();
            getchar();
            break;
        case 13:
            std::cout << "Enter the index of list:[0-99] ";
            std::cin >> temp_index;
            if (temp_index >= LEN || temp_index < 0) {
                std::cout << "Change failed\n";
            }
            else {
                list_index = temp_index;
                std::cout << "Change successfully\n";
            }
            getchar();
            getchar();
            break;
        case 14:
            if (L.ListSave() == OK) {
                std::cout << "Save to file successfully\n";
            }
            else {
                std::cout << "Save to file failed.\n";
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
    std::cout << "Good bye.\n";

}
#endif //DATASTRUCTURE_TESTLINEARLIST_H
