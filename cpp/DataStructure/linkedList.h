#ifndef DATASTRUCTURE_LINKEDLIST_H
#define DATASTRUCTURE_LINKEDLIST_H
// 包含所需头文件
#include "status.h"

<<<<<<< HEAD
// 使用模板
template<typename T = int>
// 定义类
class LinkedList {
private:
    // 结点类型
    struct Node {
        // 值
        T value;
        // 指向下一个文件的指针
        Node *next;
        // 删除默认构造函数
        Node() = delete;
        // 定义构造函数
        Node(const T &value) : value(value), next(nullptr) {}
    };
    // 定义头指针
    Node *head = nullptr;
    // 链表长度
    int length = 0;
    // 是否进行了初始化
    bool initaled = false;
public:
    // 初始化函数
    status InitaList() {
        // 已经初始化过的返回ERROR
        if (initaled) {
            // 输出错误信息
            std::cerr << "The list had been initalized.\n";
            return ERROR;
        }
        // 长度初始化为0
        length = 0;
        // 询问是否从文件初始化
        std::cout << "initalize from file(y/n):";
        char ch;
        // 输入选择
        std::cin >> ch;
        if (ch == 'y') {
            getchar();
            // 得到文件名
            std::cout << "Please enter name of the file: ";
            std::string file_name;
            std::getline(std::cin, file_name);
            // 打开文件流
            std::fstream fin(file_name, std::ios_base::in);
            // 查看打开是否成功
            if (fin.is_open()) {
                // 进行输入数据
                initaled = true;
                int cnt = 0;
                // 得到数据个数
                fin >> cnt;
                // 定义局部变量
                T temp;
                for (int i = 0; i < cnt; ++i) {
                    // 输入变量
                    fin >> temp;
                    // 插入到链表后面
                    ListInsert(length + 1, temp);
                }
                // 关闭文件流
=======
template<typename T = int>
class LinkedList {
private:
    struct Node {
        T value;
        Node *next;

        Node() = delete;

        Node(const T &value) : value(value), next(nullptr) {}
    };

    Node *head = nullptr;
    int length = 0;
    bool initaled = false;
public:
    status InitaList() {
        if (initaled) {
            std::cerr << "The list had been initalized.\n";
            return ERROR;
        }

        length = 0;
        std::cout << "initalize from file(y/n):";
        char ch;
        std::cin >> ch;
        if (ch == 'y') {
            getchar();
            std::cout << "Please enter name of the file: ";
            std::string file_name;
            std::getline(std::cin, file_name);
            std::fstream fin(file_name, std::ios_base::in);
            if (fin.is_open()) {
                initaled = true;
                int cnt = 0;
                fin >> cnt;
                T temp;
                for (int i = 0; i < cnt; ++i) {
                    fin >> temp;
                    ListInsert(length + 1, temp);
                }
>>>>>>> master
                fin.close();
                std::cout << "Initalize from file successfully.\n";
            }
            else {
<<<<<<< HEAD
                // 否则输出错误
=======
>>>>>>> master
                std::cerr << "Open file failed.\n";
                return ERROR;
            }
        }

        initaled = true;
        return OK;
    }

<<<<<<< HEAD
    // 销毁链表
    status DestroyList() {
        // 如果未初始化返回错误
=======
    status DestroyList() {
>>>>>>> master
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }

        Node *temp = head;
        Node *pre;
<<<<<<< HEAD
        // 清理所有链表空间
=======
>>>>>>> master
        while (temp != nullptr) {
            pre = temp->next;
            delete temp;
            temp = pre;
        }
<<<<<<< HEAD
        // 头指针置为空
        head = nullptr;
        // 长度置零
        length = 0;
        // 初始化置为false
=======
        head = nullptr;
        length = 0;
>>>>>>> master
        initaled = false;
        return OK;
    }

<<<<<<< HEAD
    // 清空链表
    status ClearList() {
        // 未初始化不能清空
=======
    status ClearList() {
>>>>>>> master
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
<<<<<<< HEAD
        // 唯一区别就是摧毁后的初始化状态为true
=======
>>>>>>> master
        DestroyList();
        initaled = true;
        return OK;
    }

<<<<<<< HEAD
    // 检测是否为空表
    bool ListEmpty() const {
        // 未初始化的默认是空表
=======
    bool ListEmpty() {
>>>>>>> master
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return true;
        }
<<<<<<< HEAD
        // 判断长度是否为0
        return length == 0;
    }

    // 得到链表长度
    int ListLength() const {
=======

        return length == 0;
    }

    int ListLength() {
>>>>>>> master
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return -1;
        }
<<<<<<< HEAD
        // 返回长度
        return length;
    }

    // 获取特定位置的元素
    status GetElem(const int &index, T &e) const {
        // 未初始化报错
=======

        return length;
    }

    status GetElem(const int &index, T &e) {
>>>>>>> master
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
<<<<<<< HEAD
        // 判断下标是否合法
=======
>>>>>>> master
        if (index < 0 || index > length) {
            std::cerr << "Index out of bounds.\n";
            return ERROR;
        }
<<<<<<< HEAD
        // 定义局部变量
        auto temp = head;
        // index处元素向后移动index-1次即可
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }
        // 获取值
=======
        auto temp = head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }
>>>>>>> master
        e = temp->value;

        return OK;
    }

<<<<<<< HEAD
    // 定位元素
    status LocateElem(const T &e, int &index, Compare<T> comp) const {
=======
    status LocateElem(const T &e, int &index, Compare<T> comp) {
>>>>>>> master
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
<<<<<<< HEAD
        // 局部头指针
        auto temp_ptr = head;
        // 遍历元素，看是否有comp为真的
        for (int i = 0; i < length; i++) {
            if (comp(e, temp_ptr->value)) {
                // 存在就返回下标
                index = i + 1;
                return OK;
            }
            // 指针后移
            temp_ptr = temp_ptr->next;
        }
        // 否则就是没有
=======
        auto temp_ptr = head;
        for (int i = 0; i < length; i++) {
            if (comp(e, temp_ptr->value)) {
                index = i + 1;
                return OK;
            }
            temp_ptr = temp_ptr->next;
        }
>>>>>>> master
        index = 0;
        return ERROR;
    }

<<<<<<< HEAD
    // 获取前驱元素
    status PriorElem(const T &cur, T &pre_e, Compare<T> comp) const {
=======
    status PriorElem(const T &cur, T &pre_e, Compare<T> comp) {
>>>>>>> master
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
<<<<<<< HEAD
        // 局部头指针
        auto temp_ptr = head;
        // 遍历元素
        while (temp_ptr != nullptr && temp_ptr->next != nullptr) {
            // 如果此处元素的后驱是给出的元素，返回此元素
=======
        auto temp_ptr = head;
        while (temp_ptr != nullptr && temp_ptr->next != nullptr) {
>>>>>>> master
            if (comp(temp_ptr->next->value, cur)) {
                pre_e = temp_ptr->value;
                return OK;
            }
        }

        return OK;
    }

<<<<<<< HEAD
    // 获得后驱
    status NextElem(const T &cur, T &next, Compare<T> comp) const {
=======
    status NextElem(const T &cur, T &next, Compare<T> comp) {
>>>>>>> master
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        auto temp_ptr = head;
<<<<<<< HEAD
        // 如果此元素满足comp为真，下一个即为所求元素
=======
>>>>>>> master
        while (temp_ptr != nullptr && temp_ptr->next != nullptr) {
            if (comp(temp_ptr->value, cur)) {
                next = temp_ptr->next->value;
                return OK;
            }
        }

        return OK;
    }

<<<<<<< HEAD
    // 插入元素
=======
>>>>>>> master
    status ListInsert(const int &index, const T &e) {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
<<<<<<< HEAD
        // 判断下标是否合法
=======
>>>>>>> master
        if (index < 1 || index > length + 1) {
            std::cerr << "Index out of bounds\n";
            return ERROR;
        }
<<<<<<< HEAD
        // 使用初始值新建结点
        auto t = new Node(e);
        // 插入到首元素位置特殊处理
=======
        auto t = new Node(e);
>>>>>>> master
        if (index == 1) {
            t->next = head;
            head = t;
        }
        else {
<<<<<<< HEAD
            // 向后移动到适当位置
=======
>>>>>>> master
            auto pre = head;
            for (int i = 0; i < index - 2; ++i) {
                pre = pre->next;
            }
<<<<<<< HEAD
            // 将t插入
            t->next = pre->next;
            pre->next = t;
        }
        // 长度加1
=======
            t->next = pre->next;
            pre->next = t;
        }
>>>>>>> master
        ++length;

        return OK;
    }

<<<<<<< HEAD
    // 删除元素
=======
>>>>>>> master
    status ListDelete(const int &index, T &e) {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
<<<<<<< HEAD
        // 判断下标合法性
=======
>>>>>>> master
        if (index < 1 || index > length) {
            std::cerr << "Index out of bounds\n";
            return ERROR;
        }

<<<<<<< HEAD
        // 删除首元素特殊处理
=======
>>>>>>> master
        if (index == 1) {
            Node *temp = head;
            head = head->next;
            e = temp->value;
            delete temp;
        }
        else {
            auto pre = head;
<<<<<<< HEAD
            // 后移适当位置，找到要删除元素的前驱
            for (int i = 0; i < index - 2; ++i) {
                pre = pre->next;
            }
            // 删除元素
=======
            // 1 2 3
            for (int i = 0; i < index - 2; ++i) {
                pre = pre->next;
            }

>>>>>>> master
            auto to_del = pre->next;
            pre->next = to_del->next;
            e = to_del->value;
            delete to_del;
        }
<<<<<<< HEAD
        // 长度减 1
=======
>>>>>>> master
        --length;

        return OK;
    }

<<<<<<< HEAD
    // 遍历元素
=======
>>>>>>> master
    status ListTraverse(Visit<T> visit) {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
<<<<<<< HEAD
        // 直接遍历即可
        auto temp_ptr = head;
        for (int i = 0; i < length; ++i) {
            // 使用visit指针
            visit(temp_ptr->value);
            // 指针后移
=======

        auto temp_ptr = head;
        for (int i = 0; i < length; ++i) {
            visit(temp_ptr->value);
>>>>>>> master
            temp_ptr = temp_ptr->next;
        }

        return OK;
    }

<<<<<<< HEAD
    // 将链表保存到文件中
=======
>>>>>>> master
    status ListSave() {
        if (!initaled) {
            std::cerr << "List is not initialized.\n";
            return ERROR;
        }
        getchar();
<<<<<<< HEAD
        // 得到文件名
        std::cout << "Please enter the file name: ";
        std::string file_name;
        std::cin >> file_name;
        // 打开输出文件流
        std::fstream fout(file_name, std::ios_base::out);
        // 先写入元素个数
        fout << length << "\n";
        // 遍历写入
=======
        std::cout << "Please enter the file name: ";
        std::string file_name;
        std::cin >> file_name;
        std::fstream fout;
        fout.open(file_name, std::ios_base::out);
        fout << length << "\n";
>>>>>>> master
        auto temp_ptr = head;
        for (int i = 0; i < length; ++i) {
            fout << temp_ptr->value << "\n";
            temp_ptr = temp_ptr->next;
        }
<<<<<<< HEAD
        // 关闭文件流保存文件
=======
>>>>>>> master
        fout.close();
        return OK;
    }

<<<<<<< HEAD
    // 析构函数
    ~LinkedList() {
        // 主要就是释放空间了
=======
    ~LinkedList() {
>>>>>>> master
        auto temp = head;
        while (temp != nullptr) {
            auto next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
    }
};
<<<<<<< HEAD
=======
//}


>>>>>>> master
#endif //DATASTRUCTURE_LINKEDLIST_H
