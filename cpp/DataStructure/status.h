#ifndef DATASTRUCTURE_STATUS_H
#define DATASTRUCTURE_STATUS_H


#include <iostream>
#include <fstream>
#include <string>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE (-1)
#define MY_OVERFLOW (-2)

using status = int;

void cls() {
    system("cls");
}

template<typename T>
using Compare = bool (*)(const T &a, const T &b);
template<typename T>
using Visit = void (*)(const T &a);

#endif //DATASTRUCTURE_STATUS_H
