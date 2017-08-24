#include "Functions.h"

int main() {
    // 初始化楼盘数据并得到其头指针
    BuildingsPtr head = initialize();
    // 测试函数，测试是否读取成功
    // printBuildings(head);
    // 进入操作界面
    operations(&head);
    return 0;
}