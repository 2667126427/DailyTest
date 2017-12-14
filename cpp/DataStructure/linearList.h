#ifndef _LINEARLIST_H
#define _LINEARLIST_H

#include "status.h"

// 初始长度
#define LIST_INIT_SIZE 100
// 增长速率
#define LISTINCREMENT  10

// 定义模板参数
template<typename T>
// 类定义
class LinearList {
    // 私有变量及函数部分
private:
    // 数组的指针，初始化为nullptr
    T * elem = nullptr;
    // 表的长度，初始化为0
    int length = 0;
    // 表的容量，初始化为0
    int listSize = 0;

    // 扩大链表的函数，只允许内部调用，设置访问权限为private
    void largerList() {
        T *temp = nullptr;
        try {
            // 尝试开辟空间
            temp = new T[listSize + LISTINCREMENT];
        }// 失败抛出异常，异常处理
        catch (const std::bad_alloc &e) {
            // 输出错误信息
            std::cerr << "ERROR: " << e.what() << std::endl;
            // 程序系统面临崩溃，及时退出
            exit(EXIT_FAILURE);
        }
        // 否则表示空间分配完成，将原来的数据复制到新的地方
        for (int i = 0; i < length; ++i) {
            temp[i] = std::move(elem[i]);
        }
        // 释放原来的空间
        delete[] elem;
        // 移交指针
        elem = temp;
        // 容量增长
        listSize += LISTINCREMENT;
    }
public:
    // 公开函数部分

    // 初始化函数
    status InitaList() {
        // 已经进行了初始化
        if (listSize != 0) {
            std::cerr << "线性表已存在，初始化失败，请先进行销毁操作。\n" << std::endl;
            return ERROR;
        }
        // 初始化需要分配空间
        try {
            // new空间
            elem = new T[LIST_INIT_SIZE];
        }
        catch (const std::bad_alloc& e) {
            // 分配失败
            std::cerr << "Error: " << e.what() << std::endl;
            // 返回错误
            return ERROR;
        }
        // 表的容量即为LIST_INIT_SIZE
        listSize = LIST_INIT_SIZE;
        // 长度设为0
        length = 0;
        char ch;
        // 询问是否从文件初始化
        std::cout << "if initalize from file(y/n): ";
        std::cin >> ch;
        getchar();
        if (ch == 'y') {
            // 从文件初始化需要输入文件名
            std::cout << "Please enter file name: ";
            std::string file_name;
            // 得到文件名
            std::getline(std::cin, file_name);
            // 打开输入流
            std::fstream fin(file_name, std::ios_base::in);
            // 判断是否打开完成
            if (!fin.is_open()) {
                std::cerr << "Open file failed.\n";
                return ERROR;
            }
            else {
                int cnt = 0;
                // 输入文件中的元素数量
                fin >> cnt;
                // 局部元素
                T ele;
                // 进行插入操作
                for (int i = 0; i < cnt; ++i) {
                    fin >> ele;
                    ListInsert(length + 1, ele);
                }
                std::cout << "Initalize from file successfully.\n";
            }
            // 关闭文件流
            fin.close();
        }
        return OK;
    }

    // 销毁线性表
    status DestroyList() {
        // 如果未进行初始化
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        // 清理空间
        delete[] elem;
        // 置为空指针
        elem = nullptr;
        // 长度和容量置为0
        length = 0;
        listSize = 0;
        return OK;
    }

    // 清空线性表
    status ClearList() {
        // 未初始化
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        // 清空只需重置表长即可
        length = 0;
        return OK;
    }

    // 判断表是否为空
    bool ListEmpty() {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return true;
        }
        // 判断表长是否为0即可
        return length == 0;
    }

    // 获取表长
    int ListLength() {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return -1;
        }
        // 返回表长
        return length;
    }

    // 获取下表为index处的元素
    status GetElem(const int &index, T &e) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        // 判断下表合法性
        if (index > length || index < 1) {
            std::cerr << "Index out of bounds.\n";
            return ERROR;
        }
        // 直接获取
        e = elem[index - 1];

        return OK;
    }

    // 定位元素
    status LocateElem(const T &e, int &index, Compare<T> comp) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        // 下标初始化
        index = 0;
        // 遍历
        for (int i = 0; i < length; ++i) {
            if (comp(e, elem[i])) {
                index = i + 1;
                return OK;
            }
        }
        return ERROR;
    }

    // 获取元素前驱
    status PriorElem(const T &cur, T &pre_e, Compare<T> comp) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        // 遍历即可，注意范围
        for (int i = 0; i < length - 1; ++i) {
            if (comp(cur, elem[i + 1])) {
                pre_e = elem[i];
                return OK;
            }
        }
        return ERROR;
    }

    // 获取元素后驱
    status NextElem(const T &cur, T &next, Compare<T> comp) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        // 和前驱部分相同，遍历即可
        for (int i = 1; i < length; ++i) {
            if (comp(cur, elem[i - 1])) {
                next = elem[i];
                return OK;
            }
        }
        return ERROR;
    }

    // 插入元素
    status ListInsert(const int &index, const T &e) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        // 判断插入位置合法性
        if (index < 1 || index > length + 1) {
            std::cerr << "Index out of bounds.\n";
            return ERROR;
        }
        // 如果表已经满了，则需要扩容
        if (length >= listSize) {
            // 进行扩容
            largerList();
        }
        // 将对应元素依次向后移动
        for (int i = length; i >= index; --i) {
            elem[i] = elem[i - 1];
        }
        // 插入元素
        elem[index - 1] = e;
        // 长度要加1
        ++length;
        return OK;
    }

    // 删除元素
    status ListDelete(const int &index, T &e) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        // 判断下标合法性
        if (index < 1 || index > length) {
            std::cerr << "Index out of bounds.\n";
            return ERROR;
        }
        // 直接返回即可
        e = elem[index - 1];
        // 将后面的函数向前移
        for (int i = index - 1; i < length - 1; ++i) {
            elem[i] = elem[i + 1];
        }
        // 长度减1
        --length;
        return OK;
    }

    // 遍历线性表
    status ListTraverse(Visit<T> visit) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        // 依次遍历即可
        for (int i = 0; i < length; ++i) {
            visit(elem[i]);
        }
        return OK;
    }

    // 保存到文件
    status ListSave() {
        if (elem == nullptr) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        getchar();
        // 保存文件需要输入文件名
        std::cout << "Please enter file name: ";
        std::string file_name;
        // 输入文件名
        std::getline(std::cin, file_name);
        // 打开文件流
        std::fstream fout(file_name, std::ios_base::out);
        // 判断打开是否成功
        if (fout.is_open()) {
            std::cout << "Open file successfully.\n";
            // 先将长度写入到文件中
            fout << length << "\n";
            // 将元素写入
            for (int i = 0; i < length; ++i) {
                fout << elem[i] << "\n";
            }
            // 关闭文件流
            fout.close();
            std::cout << "Save successfully.\n";
            return OK;
        }
        else {
            std::cerr << "Open file failed.\n";
            return ERROR;
        }
    }

    // 析构函数，释放空间即可
    ~LinearList() {
        delete elem;
    }

};
#endif //_LINEARLIST_H