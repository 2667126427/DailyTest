#ifndef FDACCOUNT_FDACCOUNT_H
#define FDACCOUNT_FDACCOUNT_H
#include <iostream>
#include <string>

class FDAccount{
private:
    const int&number;       // 账号
    const std::string& name;//账户名
    double money;           // 余额
    int deadline;           // 账户存款期限
    double rate;            // 存款利率
public:
    FDAccount() = delete;   // 删除默认构造函数
    FDAccount(const int&number, const std::string&name, double balance,
              int deadline, double rate);   // 构造函数
    void saveMoney(const double& money);    // 存款
    bool withdraw(const double&take);       // 取款
    const double& getMoney()const;          // 获取余额
    void showInfo()const;                   // 显示账户信息
};

#endif //FDACCOUNT_FDACCOUNT_H
