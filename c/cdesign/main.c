#include "Functions.h"

int main() {
    BuildingsPtr head = initialize();
    // 测试函数，测试是否读取成功
    // printBuildings(head);
    // 进入操作界面
    operations(&head);
    return 0;
}