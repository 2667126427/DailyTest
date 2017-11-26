//
// Created by yaning on 11/17/17.
//

#ifndef DATASTRUCTURE_LINEARLIST_H
#define DATASTRUCTURE_LINEARLIST_H

#include <iostream>
#include <fstream>
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
        // 先清理上次剩余的链表
        if (elem != nullptr) delete elem;
        // 申请空间
        elem = new T[LIST_INIT_SIZE];
        // 申请失败抛出异常
        if (elem == nullptr) {
            std::cerr << "Out of memory\n";
            return ERROR;
        }
        // 设置表的大小和容量
        listSize = LIST_INIT_SIZE;
        length = 0;

        char ch = '\0';
        std::cout << "是否从文件初始化(y/n)：";
        std::cin >> ch;
        if (ch == 'y') {
            getchar();
            std::cout << "请输入要使用的初始化的文件名：";
            std::string str;
            std::getline(std::cin, str);
            std::fstream fin;
            fin.open(str, std::ios_base::in);
            if (!fin.is_open()) {
                std::cerr << "文件打开错误。\n";
                return ERROR;
            } else {
                int cnt = 0;
                fin >> cnt;
                T ele;
                for (int i = 0; i < cnt; ++i) {
                    fin >> ele;
                    ListInsert(length + 1, ele);
                }
                std::cout << "初始化成功。\n";
            }
            fin.close();
        }

        return OK;
    }

    template<typename T>
    status linearList<T>::DestroyList() {
        if (listSize == 0) {
            std::cerr << "表未初始化，无法进行销毁。\n";
            return ERROR;
        }
        delete elem;
        length = 0;
        listSize = 0;
        return OK;
    }

    template<typename T>
    status linearList<T>::ClearList() {
        // 清空就是把长度设置为0
        if (listSize == 0) {
            std::cerr << "表未初始化，无法清理。\n";
            return ERROR;
        }
        length = 0;
        return OK;
    }

    template<typename T>
    bool linearList<T>::ListEmpty() {
        // 表为空即长度为0
        return length == 0;
    }

    template<typename T>
    int linearList<T>::ListLength() {
        return length;
    }

    template<typename T>
    status linearList<T>::GetElem(const int &index, T &e) {
        if (ListEmpty()) {
            std::cerr << "表为空。\n";
        }
        if (index > length) {
            std::cerr << "下标超过表的长度。\n";
            return ERROR;
        } else if (index < 1) {
            std::cerr << "下标小于1。\n";
            return ERROR;
        }
        e = elem[index - 1];

        return OK;
    }

    template<typename T>
    status linearList<T>::LocateElem(const T &e, int &index, Compare<T> comp) {
        for (int i = 0; i < length; ++i) {
            if (comp(e, elem[i])) {
                index = i + 1;
                return OK;
            }
        }

        return ERROR;
    }

    template<typename T>
    status linearList<T>::PriorElem(const T &cur, T &pre_e, Compare<T> comp) {
        for (int i = 0; i < length - 1; ++i) {
            if (comp(cur, elem[i + 1])) {
                pre_e = elem[i];
                return OK;
            }
        }

        return ERROR;
    }

    template<typename T>
    status linearList<T>::NextElem(const T &cur, T &next, Compare<T> comp) {
        for (int i = 1; i < length; ++i) {
            if (comp(cur, elem[i - 1])) {
                next = elem[i];
                return OK;
            }
        }

        return ERROR;
    }

    template<typename T>
    status linearList<T>::ListInsert(const int &index, const T &e) {
        if (index < 1) {
            std::cerr << "下标应该大于0。\n";
            return ERROR;
        } else if (index > length + 1) {
            std::cerr << "下标应该小于表的长度加一\n";
            return ERROR;
        }
        if (length >= listSize) {
            largerList();
        }
        // 1 2 3 4, ex: 1, 1
        for (int i = length; i >= index; --i) {
            elem[i] = elem[i - 1];
        }
        elem[index - 1] = e;
        ++length;
        return OK;
    }

    template<typename T>
    status linearList<T>::ListDelete(const int &index, T &e) {
        if (index < 1) {
            std::cerr << "下标应该大于0。\n";
            return ERROR;
        } else if (index > length) {
            std::cerr << "下标应该小于表的长度加一\n";
            return ERROR;
        }
        // 1 2 3 4, ex: 1, i from 0 to 2
        e = elem[index - 1];
        for (int i = index - 1; i < length - 1; ++i) {
            elem[i] = elem[i + 1];
        }
        --length;

        return OK;
    }

    template<typename T>
    status linearList<T>::ListTraverse(Visit<T> visit) {
        if (ListEmpty()) {
            std::cerr << "表为空，无法遍历。\n";
            return ERROR;
        }

        for (int i = 0; i < length; ++i) {
            visit(elem[i]);
        }

        return OK;
    }

    template<typename T>
    linearList<T>::~linearList() {
        delete elem;
    }

    template<typename T>
    void linearList<T>::largerList() {
        auto *temp = new T[listSize + LISTINCREMENT];
        if (temp == nullptr) {
            std::cerr << "Out of memory";
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < length; ++i) {
            temp[i] = elem[i];
        }
        delete elem;
        elem = temp;
        listSize += LISTINCREMENT;
    }

    template<typename T>
    status linearList<T>::ListSave() {
        if (length == 0) {
            std::cerr << "表为空，无法保存到文件。\n";
            return ERROR;
        }
        getchar();
        std::cout << "请输入文件名：";
        std::string str;
        std::getline(std::cin, str);
        std::fstream fout;
        fout.open(str, std::ios_base::out);
        if (fout.is_open()) {
            std::cout << "打开文件成功。\n";
            fout << length << "\n";
            for (int i = 0; i < length; ++i) {
                fout << elem[i] << "\n";
            }
            fout.close();
            return OK;
        } else {
            std::cerr << "文件打开失败。\n";
            fout.close();
            return ERROR;
        }
    }
}

#endif //DATASTRUCTURE_LINEARLIST_H
