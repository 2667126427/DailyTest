#include "FDAccount.h"

int main() {
    FDAccount account(1024, "HUST", 1000, 10, 3);
    account.showInfo();
    account.saveMoney(1000);
    account.showInfo();
    std::cout << "账户余额为：" << account.getMoney() << "元" << std::endl;
    account.withdraw(3000);
    account.withdraw(1500);
    account.showInfo();
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}
