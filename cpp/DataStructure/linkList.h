//
// Created by yaning on 11/24/17.
//

#ifndef DATASTRUCTURE_LINKLIST_H
#define DATASTRUCTURE_LINKLIST_H
#define LEN 100

#include "status.h"

namespace DS {

    template<typename T = int>
    class LinkedList {
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

    private:
        struct Node {
            T value;
            Node *next;

            Node() = delete;

            explicit Node(const T &value) : value(value), next(nullptr) {}
        };

        Node *head = nullptr;
        int length = 0;
    };

    template<typename T>
    status LinkedList<T>::InitaList() {
        return OK;
    }

    template<typename T>
    status LinkedList::DestroyList() {
        if (head == nullptr) {
            std::cerr << "表为空表，不可摧毁。\n";
            return ERROR;
        }
        Node *temp = head;
        Node *pre;
        while (temp != nullptr) {
            pre = temp->next;
            delete temp;
            temp = pre;
        }
        head = nullptr;
        return OK;
    }

    template<typename T>
    status LinkedList::ClearList() {
        DestroyList();
        return 0;
    }

    template<typename T>
    status LinkedList::ListDelete(const int &index, T &e) {
        if (head == nullptr) {
            std::cerr << "表为空，不可删除元素。\n";
            return ERROR;
        }
        if (index <= 0 || index > length) {
            std::cerr << "下标超出范围，请检查输入。\n";
            return ERROR;
        }

        return 0;
    }

    template<typename T>
    status LinkedList::ListInsert(const int &index, const T &e) {
        return 0;
    }

    template<typename T>
    bool LinkedList::ListEmpty() {
        return false;
    }

    template<typename T>
    int LinkedList::ListLength() {
        return 0;
    }

    template<typename T>
    status LinkedList::GetElem(const int &index, T &e) {
        return 0;
    }

    template<typename T>
    status LinkedList::LocateElem(const T &e, int &index, Compare<T> comp) {
        return 0;
    }


    template<typename T>
    status LinkedList::ListTraverse(Visit<T> visit) {
        return 0;
    }

    template<typename T>
    status LinkedList::PriorElem(const T &cur, T &pre_e, Compare<T> comp) {
        return 0;
    }

    template<typename T>
    status LinkedList::NextElem(const T &cur, T &next, Compare<T> comp) {
        return 0;
    }

}


#endif //DATASTRUCTURE_LINKLIST_H
