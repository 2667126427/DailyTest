//
// Created by yaning on 11/17/17.
//

#ifndef DATASTRUCTURE_LINEARLIST_H
#define DATASTRUCTURE_LINEARLIST_H

#include <iostream>
#include <fstream>
#include <exception>
#include "status.h"

namespace DS {
// 使用c++的输入输出

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

// 定义模板类，模板不支持导出
    template<typename T = int>
    class linearList {
    public:
        //  初始化函数
        status InitaList();

        //销毁的函数
        status DestroyList();

        // 清空函数
        status ClearList();

        // 判断是否为空函数
        bool ListEmpty();

        // 求表的长度的函数
        int ListLength();

        // 获取对应位置的元素
        status GetElem(const int &index, T &e);

        // 定位元素位置
        status LocateElem(const T &e, int &index, Compare<T> comp);

        // 给定元素前一个元素
        status PriorElem(const T &cur, T &pre_e, Compare<T> comp);

        // 查找元素下一个元素
        status NextElem(const T &cur, T &next, Compare<T> comp);

        // 插入元素
        status ListInsert(const int &index, const T &e);

        // 删除列表元素
        status ListDelete(const int &index, T &e);

        // 遍历列表
        status ListTraverse(Visit<T> visit);

        // 将表存储到文件中
        status ListSave();
        ~linearList();

    private:
        // 存储元素的指针数组
        T *elem = nullptr;
        // 表的长度
        int length = 0;
        // 表的容量
        int listSize = 0;

        // 给表扩容
        void largerList();
    };

    
    template<typename T>
    status linearList<T>::InitaList() {
        // 先判断是否被初始过
        if (elem != nullptr) {
            std::cerr << "线性表已存在，初始化失败，请先进行销毁操作。\n";
            return ERROR;
        }
        // 申请空间
        elem = new T[LIST_INIT_SIZE];
        // 申请失败的情况
        if (elem == nullptr) {
            std::cerr << "Out of memory\n";
            return ERROR;
        }
        // 设置表的现在长度和容量
        listSize = LIST_INIT_SIZE;
        length = 0;
        // 询问是否从文件进行初始化
        char ch = '\0';
        std::cout << "是否从文件初始化(y/n)：";
        std::cin >> ch;
        // 处理换行符
        getchar();
        if (ch == 'y') {
            // 得到使用文件名称
            std::cout << "请输入要使用的初始化的文件名：";
            std::string str;
            // 得到文件名
            std::getline(std::cin, str);
            std::fstream fin;
            // 打开文件流
            fin.open(str, std::ios_base::in);
            // 打开错误说明文件不存在或者损坏
            if (!fin.is_open()) {
                std::cerr << "文件打开错误。\n";
                return ERROR;
            } else {
                // 先得到文件中元素的个数
                int cnt = 0;
                fin >> cnt;
                T ele;
                // 获取全部的元素并且插入到表尾
                for (int i = 0; i < cnt; ++i) {
                    fin >> ele;
                    ListInsert(length + 1, ele);
                }
                // 输出提示信息
                std::cout << "初始化成功。\n";
            }
            // 注意记得关闭文件
            fin.close();
        }
        // 返回状态
        return OK;
    }

    // 销毁函数
    template<typename T>
    status linearList<T>::DestroyList() {
        // 如果listSize为0表示未进行初始化或者已经被销毁过。
        if (listSize == 0) {
            std::cerr << "表未初始化，无法进行销毁。\n";
            return ERROR;
        }
        // 只需要对空间进行清理，并把长度等信息置0即可。
        delete[] elem;
        length = 0;
        listSize = 0;
        // 返回销毁成功
        return OK;
    }

    // 清空一个表
    template<typename T>
    status linearList<T>::ClearList() {
        // 首先是判断表是否存在
        if (listSize == 0) {
            std::cerr << "表未被初始化，清空失败\n";
            return ERROR;
        }
        // 清空就是把长度设置为0
        length = 0;
        return OK;
    }
    
    // 判断是否为空表
    template<typename T>
    bool linearList<T>::ListEmpty() {
        // 首先判断是否是个未被初始化的表
        if (listSize == 0) {
            std::cerr << "表未被初始化。\n";
            return false;
        }
        // 表为空即长度为0
        return length == 0;
    }
    
    // 求表长的函数
    template<typename T>
    int linearList<T>::ListLength() {
        // 未初始化的表其实个人觉得应该认为表长为0
        // 首先判断是否是个未被初始化的表
        if (listSize == 0) {
            std::cerr << "表未被初始化。\n";
            return -1;
        }
        return length;
    }

    // 获取对应位置的元素
    template<typename T>
    status linearList<T>::GetElem(const int &index, T &e) {
        // 首先判断是否是个未被初始化的表
        if (listSize == 0) {
            std::cerr << "表未被初始化。\n";
            return ERROR;
        }
        // 判断下表是否超出范围
        if (index > length) {
            std::cerr << "下标超过表的长度。\n";
            return ERROR;
        } else if (index < 1) {
            std::cerr << "下标小于1。\n";
            return ERROR;
        }
        // 返回元素
        e = elem[index - 1];

        return OK;
    }

    // 定位元素的函数，参数为需要定位的元素和比较函数，需要存放的位置
    template<typename T>
    status linearList<T>::LocateElem(const T &e, 
                                     int &index, Compare<T> comp) {
        // 首先判断是否是个未被初始化的表
        if (listSize == 0) {
            std::cerr << "表未被初始化。\n";
            return ERROR;
        }
        // 当不满足时设置为0，直接在这里设置即可
        index = 0;
        // 由于元素为无序的，所以直接线性搜索即可，注意搜索的区间即可
        for (int i = 0; i < length; ++i) {
            // 如果此位置的元素满足要求，返回位置即可
            if (comp(e, elem[i])) {
                index = i + 1;
                return OK;
            }
        }
        // 返回执行状态
        return ERROR;
    }
    
    // 查找前驱元素，参数为需要查找的元素和对应的比较函数
    template<typename T>
    status linearList<T>::PriorElem(const T &cur,
                                    T &pre_e, Compare<T> comp) {
        // 首先判断是否是个未被初始化的表
        if (listSize == 0) {
            std::cerr << "表未被初始化。\n";
            return ERROR;
        }
        // 线性查找，结束条件为找到或者未找到
        for (int i = 0; i < length - 1; ++i) {
            // 如果i + 1处元素为cur，那么i处即为所找，不考虑元素重复的情况
            if (comp(cur, elem[i + 1])) {
                // 为参数赋值
                pre_e = elem[i];
                return OK;
            }
        }
        // 返回查找状态
        return ERROR;
    }
    
    // 查找后驱元素
    template<typename T>
    status linearList<T>::NextElem(const T &cur,
                                   T &next, Compare<T> comp) {
        // 首先判断是否是个未被初始化的表
        if (listSize == 0) {
            std::cerr << "表未被初始化。\n";
            return ERROR;
        }
        // 对元素进行一一比较
        for (int i = 1; i < length; ++i) {
            if (comp(cur, elem[i - 1])) {
                next = elem[i];
                return OK;
            }
        }
        // 返回错误状态
        return ERROR;
    }
    
    // 插入函数
    template<typename T>
    status linearList<T>::ListInsert(const int &index, const T &e) {
        // 首先判断是否是个未被初始化的表
        if (listSize == 0) {
            std::cerr << "表未被初始化。\n";
            return ERROR;
        }
        // 再判断插入位置是否合理
        if (index < 1 || index > length + 1) {
            std::cerr << "下标不合法。\n";
            return ERROR;
        }
        // 如果表满了则需要进行扩容
        if (length >= listSize) {
            largerList();
        }
        // 将对应位置的元素向后移动为插入的元素腾出空间
        for (int i = length; i >= index; --i) {
            elem[i] = elem[i - 1];
        }
        // 将元素放置好
        elem[index - 1] = e;
        // 最后长度加一
        ++length;
        return OK;
    }
    
    // 删除指定位置元素
    template<typename T>
    status linearList<T>::ListDelete(const int &index, T &e) {
        // 首先判断是否是个未被初始化的表
        if (listSize == 0) {
            std::cerr << "表未被初始化。\n";
            return ERROR;
        }
        // 判断参数是否合法
        if (index < 1 || index > length) {
            std::cerr << "下标不合法。\n";
            return ERROR;
        } 
        // 若下表合法将元素取出
        e = elem[index - 1];
        // 将对应位置元素前移
        for (int i = index - 1; i < length - 1; ++i) {
            elem[i] = elem[i + 1];
        }
        // 长度减一
        --length;
        // 返回运行结果
        return OK;
    }

    // 对表进行遍历，参数只需要使用的函数
    template<typename T>
    status linearList<T>::ListTraverse(Visit<T> visit) {
        // 首先判断是否是个未被初始化的表
        if (listSize == 0) {
            std::cerr << "表未被初始化。\n";
            return ERROR;
        }
        // 进行遍历
        for (int i = 0; i < length; ++i) {
            visit(elem[i]);
        }
        // 返回遍历状态
        return OK;
    }

    template<typename T>
    linearList<T>::~linearList() {
        // c++中delete空指针不会产生异常
        delete elem;
    }
    
    // 为列表扩容
    template<typename T>
    void linearList<T>::largerList() {
        // 先尝试开辟更大的空间
        T *temp = nullptr;
        try {
            temp = new T[listSize + LISTINCREMENT];
        } 
        // 开辟失败了会抛出异常，正确做法是结束程序
        catch (const std::bad_alloc &e) {
            std::cerr << "ERROR" << e << std::endl;
            exit(EXIT_FAILURE);
        }
        // 如果没有失败就把原来的元素复制过来
        for (int i = 0; i < length; ++i) {
            temp[i] = elem[i];
        }
        // 记得清理空间
        delete[] elem;
        // 为elem重新赋值
        elem = temp;
        // 调整容量
        listSize += LISTINCREMENT;
    }
    
    // 保存表的函数
    template<typename T>
    status linearList<T>::ListSave() {
        // 如果长度为0就或者未初始化不进行保存
        if (length == 0 || elem == nullptr) {
            std::cerr << "表为空，无法保存到文件。\n";
            return ERROR;
        }
        // 处理换行符
        getchar();
        // 得到文件名
        std::cout << "请输入文件名：";
        std::string str;
        std::getline(std::cin, str);
        // 打开文件输出流
        std::fstream fout;
        fout.open(str, std::ios_base::out);
        // 检测打开状态
        if (fout.is_open()) {
            std::cout << "打开文件成功。\n";
            // 先将长度信息保存到文件中
            fout << length << "\n";
            // 依次将表元素保存到文件中，具体保存的方法
            // 由对模板特例化中对<<运算符的重载决定
            for (int i = 0; i < length; ++i) {
                fout << elem[i] << "\n";
            }
            // 关闭文件流
            fout.close();
            return OK;
        } else {
            // 打开写入文件失败，报错并返回状态
            std::cerr << "文件打开失败。\n";
            return ERROR;
        }
    }
}

#endif //DATASTRUCTURE_LINEARLIST_H
