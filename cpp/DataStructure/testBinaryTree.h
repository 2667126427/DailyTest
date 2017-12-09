#ifndef DATASTRUCTURE_TESTBINARYTREE_H
#define DATASTRUCTURE_TESTBINARYTREE_H

#include "binaryTree.h"

void testBinaryTree() {
    int operation = -1;
    constexpr int size = 100;
    int list_index = 0;
    int temp_list_index = 0;
    int value = 0;
    BinaryTree<int> tree[size];
    Compare<int> comp = [](const int &a, const int &b)->bool {return a == b; };
    Visit<int> visit = [](const int &t) {std::cout << t << std::endl; };

    enum Operation {
        exit, 
    };

    while (operation != 0) {
        cls();
        std::cout << "\n\n";
        std::cout << "        Menu for Binary Tree\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "      1.               2.\n";
        std::cout << "      3.               4.\n";
        std::cout << "      5.               6.\n";
        std::cout << "      7.               8.\n";
        std::cout << "      9.               10.\n";
        std::cout << "      11.              12.\n";
        std::cout << "      13.              14.\n";
        std::cout << "      15.              16.\n";
        std::cout << "      17.              18.\n";
        std::cout << "      19.              20.\n";
        std::cout << "      21.              22.\n\n";
        std::cout << "    current binary tree: " << list_index << "\n";
        std::cout << "Please select your selection: ";
        std::cin >> operation;
        switch (operation) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break; 
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 3:
            break;
        case 3:
            break;
        case 3:
            break;
        case 3:
            break;
        case 3:
            break;
        case 3:
            break;
        case 3:
            break;
        case 3:
            break;
        default:
            break;
        }
    }
}

#endif // DATASTRUCTURE_TESTBINARYTREE_H
