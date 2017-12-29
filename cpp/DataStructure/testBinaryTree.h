#ifndef DATASTRUCTURE_TESTBINARYTREE_H
#define DATASTRUCTURE_TESTBINARYTREE_H
// 包含要测试的数据类型头文件
#include "binaryTree.h"
// 设置值类型为char型
using ValueType = char;
// 空字符设置为'#'
const ValueType NULL_VALUE = '#';
// 测试主函数
void testBinaryTree() {
    constexpr int size = 100;
    // 选择的操作
    int operation = -1;
    // 一个辅助变量
    ValueType value = 0;
    // 结点类型指针
    Node<ValueType> *temp_node = nullptr;
    // 定义一棵二叉树
    BinaryTree<ValueType, NULL_VALUE> trees[size];
    int tree_index = 0;
    int temp_tree_index = 0;
    // visit函数
    Visit<ValueType> visit = [](const ValueType &t) {std::cout << t << std::endl; };
    // 默认键为-1
    int key = -1;
    // 左右选择
    LR lr = LR::L;
    int position = 0;
    // 插入子树时的临时树
    BinaryTree<ValueType, NULL_VALUE> temp_tree;
    // 用户选择的选项
    std::string choice;
    while (operation != 0) {
        // 清屏
        cls();
        // 打印菜单
        std::cout << "";
        std::cout << "               Menu for Binary Tree\n\n";
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
        std::cout << "      21.ChangeBiTree\n";
        std::cout << "      0.Exit\n";
        std::cout << "---------------------------------------------------\n";
        std::cout << "Current using tree: " << tree_index << "\n\n";
        std::cout << " Please select your selection: ";
        std::cin >> choice;
        // 将字符串转为数字
        operation = std::stoi(choice);
        auto &tree = trees[tree_index];
        switch (operation) {
        case 1:
            std::cout << "InitBiTree Function\n";
            if (tree.InitBiTree() == OK) {
                std::cout << "Initalize tree succefully.\n";
            }
            else {
                std::cout << "Initalize tree failed.\n";
            }
            wait();
            break;
        case 2:
            std::cout << "DestroyBiTree Function\n";
            if (tree.DestroyBiTree() == OK) {
                std::cout << "Destroy tree successfully.\n";
            }
            else {
                std::cout << "Destroy tree failed.\n";
            }
            wait();
            break;
        case 3:
            std::cout << "CreateBiTree Function\n";
            if (tree.CreateBiTree() == OK) {
                std::cout << "Create tree successfully.\n";
            }
            else {
                std::cout << "Create tree failed.\n";
            }
            wait();
            break;
        case 4:
            std::cout << "ClearBiTree Function\n";
            if (tree.ClearBiTree() == OK) {
                std::cout << "Clear tree successfully.\n";
            }
            else {
                std::cout << "Clear tree failed.\n";
            }
            wait();
            break;
        case 5:
            std::cout << "BiTreeEmpty Funtion\n";
            if (tree.BiTreeEmpty()) {
                std::cout << "This tree is empty.\n";
            }
            else {
                std::cout << "This tree is not empty.\n";
            }
            wait();
            break;
        case 6:
            std::cout << "BiTreeDepth Function\n";
            key = tree.BiTreeDepth();
            std::cout << "Tree's depth is: " << key << "\n";
            wait();
            break;
        case 7:
            std::cout << "Root Function\n";
            temp_node = tree.Root();
            if (temp_node != nullptr) {
                std::cout << "Get root from tree, value: "
                    << temp_node->value << "\n";
            }
            else {
                std::cout << "Get root from tree failed.\n";
            }
            wait();
            break;
        case 8:
            std::cout << "Value Functin\n";
            tree.displsy();
            std::cout << "Please input key of the node: ";
            std::cin >> key;
            value = tree.Value(key);
            std::cout << "Get value: " << value << "\n";
            wait();
            break;
        case 9:
            std::cout << "Assign Funciton\n";
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
            std::cout << "Parent Function\n";
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
            std::cout << "LeftChildren Function\n";
            tree.displsy();
            std::cout << "Please enter the key of node: ";
            std::cin >> key;
            temp_node = tree.LeftChildren(key);
            if (temp_node != nullptr) {
                std::cout << "Get node's left node, value: "
                    << temp_node->value << std::endl;
            }
            else {
                std::cout << "Get left node failed.\n";
            }
            wait();
            break;
        case 12:
            std::cout << "RightChildren Function\n";
            tree.displsy();
            std::cout << "Please enter the key of node: ";
            std::cin >> key;
            temp_node = tree.RightChildren(key);
            if (temp_node != nullptr) {
                std::cout << "Get the right children, value: "
                    << temp_node->value << std::endl;
            }
            wait();
            break;
        case 13:
            std::cout << "LeftSibling Function\n";
            tree.displsy();
            std::cout << "Please enter the key of node: ";
            std::cin >> key;
            temp_node = tree.LeftSibling(key);
            if (temp_node != nullptr) {
                std::cout << "Get the left sibling of node, value: "
                    << temp_node->value << "\n";
            }
            else {
                std::cout << "Get the left sibling filed.\n";
            }
            wait();
            break;
        case 14:
            std::cout << "RightSibling Function\n";
            tree.displsy();
            std::cout << "Please enter the key of node: ";
            std::cin >> key;
            temp_node = tree.RightSibling(key);
            if (temp_node != nullptr) {
                std::cout << "Get the right sibling of node, value: "
                    << temp_node->value << "\n";
            }
            else {
                std::cout << "Get right siblling failed.\n";
            }
            wait();
            break;
        case 15:
            std::cout << "InsertChild Function\n";
            tree.displsy();
            std::cout << "Please enter key of node: ";
            std::cin >> key;
            std::cout << "Please enter the tree: ";
            std::cin >> temp_tree;
            std::cout << "insert into left or right(0:left, 1:right):";
            std::cin >> position;
            lr = position == 0 ? LR::L : LR::R;
            if (tree.InsertChild(key, lr, temp_tree) == OK) {
                std::cout << "Insert child success.\n";
            }
            else {
                std::cout << "Insert child failed.\n";
            }
            wait();
            break;
        case 16:
            std::cout << "DeleteChild Functin\n";
            tree.displsy();
            std::cout << "Please enter key of node: ";
            std::cin >> key;
            std::cout << "Delete left or right(0:left, 1:right):";
            std::cin >> position;
            lr = position == 0 ? LR::L : LR::R;
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
        case 21:
            std::cout << "ChangeBiTree Function\n";
            std::cout << "Please enter index of tree: ";
            std::cin >> temp_tree_index;
            if (temp_tree_index < 0 || temp_tree_index >= 100) {
                std::cout << "Index out of bounds.\n";
            }
            else {
                tree_index = temp_tree_index;
            }
            break;
        case 0:
            break;
        default:
            break;
        }
    }
    std::cout << "Good Bye.\n";
}

#endif // DATASTRUCTURE_TESTBINARYTREE_H
