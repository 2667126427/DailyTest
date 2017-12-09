#ifndef DATASTRUCTURE_STATUS_H
#define DATASTRUCTURE_STATUS_H


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE (-1)
#define MY_OVERFLOW (-2)

using status = int;

// clear the screen
void cls() {
    system("cls");
}

// insert into left or right
enum LR { L = 0, R = 1 };

// Compare function pointer defination
template<typename T>
using Compare = bool(*)(const T &a, const T &b);

// Visit function pointer defination
template<typename T>
using Visit = void(*)(const T &a);

#endif //DATASTRUCTURE_STATUS_H
