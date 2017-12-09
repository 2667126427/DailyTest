#ifndef _LINEARLIST_H
#define _LINEARLIST_H

#include "status.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

template<typename T>
class LinearList {
private:
    T * elem = nullptr;
    int length = 0;
    int listSize = 0;
    //using status = int;

    void largerList() {
        T *temp = nullptr;
        try {
            temp = new T[listSize + LISTINCREMENT];
        }
        catch (const std::bad_alloc &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < length; ++i) {
            temp[i] = elem[i];
        }
        delete[] elem;
        elem = temp;
        listSize += LISTINCREMENT;
    }
public:
    status InitaList() {
        if (elem != nullptr) {
            std::cerr << "线性表已存在，初始化失败，请先进行销毁操作。\n" << std::endl;
            return ERROR;
        }

        try {
            elem = new T[LIST_INIT_SIZE];
        }
        catch (const std::bad_alloc& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return ERROR;
        }
        listSize = LIST_INIT_SIZE;
        length = 0;
        char ch = '\0';
        std::cout << "if initalize from file(y/n): ";
        std::cin >> ch;
        getchar();
        if (ch == 'y') {
            std::cout << "Please enter file name: ";
            std::string file_name;
            std::getline(std::cin, file_name);
            std::fstream fin;
            fin.open(file_name, std::ios_base::in);
            if (!fin.is_open()) {
                std::cerr << "Open file failed.\n";
                return ERROR;
            }
            else {
                int cnt = 0;
                fin >> cnt;
                T ele;
                for (int i = 0; i < cnt; ++i) {
                    fin >> ele;
                    ListInsert(length + 1, ele);
                }
                std::cout << "Initalize from file successfully.\n";
            }
            fin.close();
        }
        return OK;
    }

    status DestroyList() {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        delete[] elem;
        elem = nullptr;
        length = 0;
        listSize = 0;
        return OK;
    }

    status ClearList() {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        length = 0;
        return OK;
    }

    bool ListEmpty() {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return false;
        }
        return length == 0;
    }

    int ListLength() {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return -1;
        }
        return length;
    }

    status GetElem(const int &index, T &e) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        if (index > length || index < 1) {
            std::cerr << "Index out of bounds.\n";
            return ERROR;
        }
        e = elem[index - 1];

        return OK;
    }

    status LocateElem(const T &e, int &index, Compare<T> comp) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        index = 0;
        for (int i = 0; i < length; ++i) {
            if (comp(e, elem[i])) {
                index = i + 1;
                return OK;
            }
        }
        return ERROR;
    }

    status PriorElem(const T &cur, T &pre_e, Compare<T> comp) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        for (int i = 0; i < length - 1; ++i) {
            if (comp(cur, elem[i + 1])) {
                pre_e = elem[i];
                return OK;
            }
        }
        return ERROR;
    }

    status NextElem(const T &cur, T &next, Compare<T> comp) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        for (int i = 1; i < length; ++i) {
            if (comp(cur, elem[i - 1])) {
                next = elem[i];
                return OK;
            }
        }
        return ERROR;
    }

    status ListInsert(const int &index, const T &e) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        if (index < 1 || index > length + 1) {
            std::cerr << "Index out of bounds.\n";
            return ERROR;
        }
        if (length >= listSize) {
            largerList();
        }
        for (int i = length; i >= index; --i) {
            elem[i] = elem[i - 1];
        }
        elem[index - 1] = e;
        ++length;
        return OK;
    }

    status ListDelete(const int &index, T &e) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        if (index < 1 || index > length) {
            std::cerr << "Index out of bounds.\n";
            return ERROR;
        }
        e = elem[index - 1];
        for (int i = index - 1; i < length - 1; ++i) {
            elem[i] = elem[i + 1];
        }
        --length;
        return OK;
    }

    status ListTraverse(Visit<T> visit) {
        if (listSize == 0) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        for (int i = 0; i < length; ++i) {
            visit(elem[i]);
        }
        return OK;
    }

    status ListSave() {
        if (elem == nullptr) {
            std::cerr << "List has not been initalized.\n";
            return ERROR;
        }
        getchar();
        std::cout << "Please enter file name: ";
        std::string str;
        std::getline(std::cin, str);
        std::fstream fout;
        fout.open(str, std::ios_base::out);
        if (fout.is_open()) {
            std::cout << "Open file successfully.\n";
            fout << length << "\n";
            for (int i = 0; i < length; ++i) {
                fout << elem[i] << "\n";
            }
            fout.close();
            std::cout << "Save successfully.\n";
            return OK;
        }
        else {
            std::cerr << "Open file failed.\n";
            return ERROR;
        }
    }

    ~LinearList() {
        delete elem;
    }

};
#endif //_LINEARLIST_H