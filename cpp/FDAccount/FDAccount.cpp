//
// Created by yaning on 01/07/17.
//

#include "FDAccount.h"

FDAccount::FDAccount(const int &number, const std::string &name, double money = 0,
                     int deadline = 0, double rate = 0) : number(number), name(name),
                                                          money(money), deadline(deadline), rate(rate) {}

void FDAccount::saveMoney(const double &money) {
    this->money += money;
    std::cout << "存款成功！" << std::endl;
    std::cout << "此时余额为：" << this->money << "元" << std::endl;
    std::cout << std::endl;
    // return true;
}


bool FDAccount::withdraw(const double &money) {
    if (money > this->money) {
        std::cerr << "对不起，余额不足，取款失败" << std::endl;
        std::cout << std::endl;
        return false;
    } else {
        this->money -= money;
        std::cout << "取款成功，余额为：" << this->money << "元" << std::endl;
        std::cout << std::endl;
        return true;
    }
}

const double &FDAccount::getMoney() const {
    return this->money;
}

void FDAccount::showInfo() const {
    std::cout << "您的信息如下：" << std::endl;
    std::cout << "账户账号为：" << this->number << std::endl;
    std::cout << "账户名称为：" << this->name << std::endl;
    std::cout << "账户余额为：" << this->money << std::endl;
    std::cout << "账户存款期限：" << this->deadline << std::endl;
    std::cout << "账户利率为：" << this->rate << "%" << std::endl;
    std::cout << std::endl;
}

