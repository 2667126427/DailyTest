//
// Created by yaning on 11/24/17.
//

#ifndef DATASTRUCTURE_STATUS_H
#define DATASTRUCTURE_STATUS_H

namespace DS {

#include <iostream>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE (-1)
#define OVERFLOW (-2)
// 状态定义
    typedef int status;

// 清屏函数
    void cls() {
        std::cout << "\033c";
    }

// 定义比较函数指针类型
    template<typename T>
    using Compare = bool (*)(const T &a, const T &b);
// 定义遍历函数指针类型
    template<typename T>
    using Visit = void (*)(const T &a);

}

#endif //DATASTRUCTURE_STATUS_H
