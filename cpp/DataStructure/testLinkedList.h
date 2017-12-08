#ifndef DATASTRUCTURE_TESTLINKEDLIST_H
#define DATASTRUCTURE_TESTLINKEDLIST_H


#include "linkedList.h"

void testLinkedList() {
	int list_index = 0;
	long op = 1;
	int cur = 0, next = 0, pre = 0, elem = 0;
	int l_index = 0;
	int index;
	LinkedList<int> lists[LEN];
	Compare<int> comp = [](const int &a, const int &b) -> bool { return a == b; };
	Visit<int> visit = [](const int &a) { std::cout << a << std::endl; };

	while (op != 0) {
		cls();
		printf("\n\n");
		printf("      Menu for Linked Table On Chain Structure \n");
		printf("-------------------------------------------------\n");
		printf("          1. IntiaList       7. LocateElem\n");
		printf("          2. DestroyList     8. PriorElem\n");
		printf("          3. ClearList       9. NextElem \n");
		printf("          4. ListEmpty       10.ListInsert\n");
		printf("          5. ListLength      11.ListDelete\n");
		printf("          6. GetElem         12.ListTraverse\n");
		printf("          13.Change list     14.Save List\n");
		printf("          0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("    list using: %2d\n", l_index);
		printf("    please select your operation[0~14]:");
		std::cin >> op;
		LinkedList<int> &L = lists[l_index];
		switch (op) {
		case 1:
			//printf("\nIntiaList");
			std::cout << "InitaList Function\n";
			if (L.InitaList() == OK) printf("Initialze successful.\n");
			else printf("Initailze failed.\n");
			getchar();
			getchar();
			break;
		case 2:
			printf("\nDestroyList Function\n");
			if (L.DestroyList() == OK) printf("Destroy successfully.\n");
			else printf("Destroy failed.\n");
			getchar();
			getchar();
			break;
		case 3:
			printf("\nClearList Function\n");
			if (L.ClearList() == OK) printf("Clear successfully\n");
			//L.ClearList();
			else printf("CLear failed.\n");
			getchar();
			getchar();
			break;
		case 4:
			printf("\nListEmpty Function\n");

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
			printf("\nListLength Function\n");
			std::cout << "The length of list: " << L.ListLength() << std::endl;
			getchar();
			getchar();
			break;
		case 6:
			printf("\nGetElem Function\n");
			printf("Please enter the index: ");
			//scanf_s("%d", &index);
			std::cin >> index;
			if (L.GetElem(index, elem) == OK) {
				std::cout << "Get the element: " << elem << "\n";
			}
			else printf("Get element failed.\n");
			getchar();
			getchar();
			break;
		case 7:
			printf("\nLocateElem Function\n");
			printf("Please enter the element: ");
			std::cin >> elem;
			if (L.LocateElem(elem, index, comp) == OK) {
				//printf("元素位置为：%d\n", index);
				std::cout << "The index of element:" << index << std::endl;
			}
			else {
				printf("Locate element failed.\n");
			}
			getchar();
			getchar();
			break;
		case 8:
			printf("\nPriorElem Function\n");
			printf("Please enter the element: ");
			std::cin >> cur;
			if (L.PriorElem(cur, pre, comp) == OK) {
				std::cout << "Get the result: " << pre << "\n";
			}
			else {
				printf("Get the element failed.\n");
			}
			getchar();
			getchar();
			break;
		case 9:
			printf("\nNextElem Function\n");
			printf("PLease enter the element: ");
			std::cin >> cur;
			if (L.NextElem(cur, next, comp) == OK) {
				std::cout << "Get the element: " << next << "\n";
			}
			else {
				printf("Operate failed.\n");
			}
			getchar();
			getchar();
			break;
		case 10:
			printf("\nListInsert Function\n");
			printf("Please enter the element: ");
			std::cin >> elem;
			printf("Please enter the index: ");
			scanf_s("%d", &index);
			if (L.ListInsert(index, elem) == OK) {
				printf("Insert successfully.\n");
			}
			else {
				printf("Insert failed.\n");
			}
			getchar();
			getchar();
			break;
		case 11:
			printf("\nListDelete Function\n");
			printf("Please enter the index: ");
			std::cin >> index;
			if (L.ListDelete(index, elem) == OK) {
				std::cout << "Delete " << elem << " successfullyy.\n";
			}
			else {
				printf("Delete failed.\n");
			}
			getchar();
			getchar();
			break;
		case 12:
			printf("\nListTraverse Function\n");
			if (L.ListTraverse(visit)) {
				printf("Traverse successfully.\n");
			}
			else {
				printf("Traverse failed.\n");
			}
			getchar();
			getchar();
			break;
		case 13:
			printf("Enter the index of list:[0-99] ");
			//scanf_s("%d", &list_index);
			std::cin >> list_index;
			if (list_index >= LEN || list_index < 0) {
				printf("Change failed\n");
			}
			else {
				l_index = list_index;
				printf("Change successfully\n");
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
	printf("Good bye.\n");

}

#endif //DATASTRUCTURE_TESTLINKEDLIST_H
