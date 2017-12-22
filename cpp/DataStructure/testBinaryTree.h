#ifndef DATASTRUCTURE_TESTBINARYTREE_H
#define DATASTRUCTURE_TESTBINARYTREE_H

#include <string>
#include "binaryTree.h"
using ValueType = char;

const ValueType NULL_VALUE = '#';

void testBinaryTree() {
    int operation = -1;
    constexpr int size = 100;
    int tree_index = 0;
    int temp_tree_index = 0;
    ValueType value = 0;
    Node<ValueType> *temp_node;
    BinaryTree<ValueType, NULL_VALUE> trees[size];
    Compare<ValueType> comp = [](const ValueType &a, const ValueType &b)
        ->bool {return a == b; };
    Visit<ValueType> visit = [](const ValueType &t) {std::cout << t << std::endl; };

    int key = -1;
    LR lr = LR::L;
    BinaryTree<ValueType, NULL_VALUE> temp_tree;
    std::string choice;
    while (operation != 0) {
        cls();
        std::cout << "\n\n";
        std::cout << "        Menu for Binary Tree\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "      1.InitBiTree         2.DestroyBiTree\n";
        std::cout << "      3.CreateBiTree       4.ClearBiTree\n";
        std::cout << "      5.BiTreeEmpty        6.BiTreeDepth\n";
        std::cout << "      7.Root               8.Value\n";
        std::cout << "      9.Assign             10.Parent\n";
        std::cout << "      11.LeftChild         12.RightChild\n";
        std::cout << "      13.LeftSibling       14.RightSibling\n";
        std::cout << "      15.InsertChild       16.DeleteChild\n";
        std::cout << "      17.PreOrderTraverse  18.InOrderTraverse\n";
        std::cout << "      19.PostOrderTraverse 20.LevelOrderTraverse\n";
        std::cout << "      0.Exit\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "    current binary tree: " << tree_index << "\n";
        std::cout << " Please select your selection: ";
        std::cin >> choice;
        operation = std::stoi(choice);
        auto &tree = trees[tree_index];
        switch (operation) {
        case 1:
            if (tree.InitBiTree() == OK) {
                std::cout << "Initalize tree succefully.\n";
            }
            else {
                std::cout << "Initalize tree failed.\n";
            }
            wait();
            break;
        case 2:
            if (tree.DestroyBiTree() == OK) {
                std::cout << "Destroy tree successfully.\n";
            }
            else {
                std::cout << "Destroy tree failed.\n";
            }
            wait();
            break;
        case 3:
            if (tree.CreateBiTree() == OK) {
                std::cout << "Create tree successfully.\n";
            }
            else {
                std::cout << "Create tree failed.\n";
            }
            wait();
            break;
        case 4:
            if (tree.ClearBiTree() == OK) {
                std::cout << "Clear tree successfully.\n";
            }
            else {
                std::cout << "Clear tree failed.\n";
            }
            wait();
            break;
        case 5:
            if (tree.BiTreeEmpty()) {
                std::cout << "This tree is empty.\n";
            }
            else {
                std::cout << "This tree is not empty.\n";
            }
            wait();
            break;
        case 6:
            std::cout << "Tree's depth is: "
                << tree.BiTreeDepth() << "\n";
            wait();
            break;
        case 7:
            temp_node = tree.Root();
            if (temp_node != nullptr) {
                std::cout << "Got root from tree, value: "
                    << temp_node->value << "\n";
            }
            else {
                std::cout << "Get root from tree failed.\n";
            }
            wait();
            break;
        case 8:
            tree.displsy();
            std::cout << "Please input key of the node: ";
            std::cin >> key;
            value = tree.Value(key);
            std::cout << "Got value: " << value << "\n";
            wait();
            break;
        case 9:
            tree.displsy();
            std::cout << "Please input the key of node: ";
            std::cin >> key;
            std::cout << "Please input the value to assign: ";
            std::cin >> value;
            if (tree.Assign(key, value) == OK) {
                std::cout << "Assign value successfully.\n";
            }
            else {
                std::cout << "Assign value failed.\n";
            }
            wait();
            break;
        case 10:
            tree.displsy();
            std::cout << "Please enter the key of node: ";
            std::cin >> key;
            temp_node = tree.Parent(key);
            if (temp_node == nullptr) {
                std::cout << "Get the parent node failed.\n";
            }
            else {
                std::cout << "Get the parent node, value: "
                    << temp_node->value << std::endl;
            }
            wait();
            break;
        case 11:
            tree.displsy();
            std::cout << "Please enter the key of node: ";
            std::cin >> key;
            temp_node = tree.LeftChildren(key);
            if (temp_node != nullptr) {
                std::cout << "Got node's left node, value: "
                    << temp_node->value << std::endl;
            }
            else {
                std::cout << "Get left node failed.\n";
            }
            wait();
            break;
        case 12:
            tree.displsy();
            std::cout << "Please enter the key of node: ";
            std::cin >> key;
            temp_node = tree.RightChildren(key);
            if (temp_node != nullptr) {
                std::cout << "Got the right children, value: "
                    << temp_node->value << std::endl;
            }
            wait();
            break;
        case 13:
            tree.displsy();
            std::cout << "Please enter the key of node: ";
            std::cin >> key;
            temp_node = tree.LeftSibling(key);
            if (temp_node != nullptr) {
                std::cout << "Got the left sibling of node, value: "
                    << temp_node->value << "\n";
            }
            else {
                std::cout << "Get the left sibling filed.\n";
            }
            wait();
            break;
        case 14:
            tree.displsy();
            std::cout << "Please enter the key of node: ";
            std::cin >> key;
            temp_node = tree.RightSibling(key);
            if (temp_node != nullptr) {
                std::cout << "Got the right sibling of node, value: "
                    << temp_node->value << "\n";
            }
            else {
                std::cout << "Get right siblling failed.\n";
            }
            wait();
            break;
        case 15:
            tree.displsy();
            std::cout << "Please enter key of node: ";
            std::cin >> key;
            std::cout << "Please enter the tree: ";
            std::cin >> temp_tree;
            std::cout << "insert into left or right(0:left, 1:right):";
            std::cin >> temp_tree_index;
            lr = temp_tree_index == 0 ? LR::L : LR::R;
            if (tree.InsertChildren(key, lr, temp_tree) == OK) {
                std::cout << "Insert childern success.\n";
            }
            else {
                std::cout << "Insert children failed.\n";
            }
            wait();
            break;
        case 16:
            tree.displsy();
            std::cout << "Please enter key of node: ";
            std::cin >> key;
            std::cout << "Delete left or right(0:left, 1:right):";
            std::cin >> temp_tree_index;
            lr = temp_tree_index == 0 ? LR::L : LR::R;
            if (tree.DeleteChild(key, lr) == OK) {
                std::cout << "Delete child success.\n";
            }
            else {
                std::cout << "Delete child failed.\n";
            }
            wait();
            break;
        case 17:
            std::cout << "PreOrderTraverse Function\n";
            if (tree.PreOrderTraverse(visit) == OK) {
                std::cout << "PreOrderTreverse successfully.\n";
            }
            else {
                std::cout << "PreOrderTreverse failed.\n";
            }
            wait();
            break;
        case 18:
            std::cout << "InOrderTraverse Function\n";
            if (tree.InOrderTraverse(visit) == OK) {
                std::cout << "InOrderTreverse successfully.\n";
            }
            else {
                std::cout << "InOrderTreverse failed.\n";
            }
            wait();
            break;
        case 19:
            std::cout << "InOrderTreverse Function\n";
            if (tree.PostOrderTraverse(visit) == OK) {
                std::cout << "PostOrderTraverse successfully.\n";
            }
            else {
                std::cout << "PostOrderTraverse failed.\n";
            }
            wait();
            break;
        case 20:
            std::cout << "LevelOrderTraverse Function\n";
            if (tree.LevelOrderTraverse(visit) == OK) {
                std::cout << "LevelOrderTraverse successfully.\n";
            }
            else {
                std::cout << "LevelOrderTraverse failed.\n";
            }
            wait();
            break;
        case 0:
            break;
        default:
            break;
        }
    }
}

#endif // DATASTRUCTURE_TESTBINARYTREE_H
