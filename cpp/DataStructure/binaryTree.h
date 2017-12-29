#ifndef DATASTRUCTURE_BINARY_TREE_H
#define DATASTRUCTURE_BINARY_TREE_H
#include "status.h"

// 结点定义
template<typename ValueType>
struct Node {
    // 键域，方便二叉树使用
    int key;
    // 值域
    ValueType value;
    // 左孩子指针
    Node<ValueType> *left = nullptr;
    // 右孩子指针
    Node<ValueType> *right = nullptr;
    // 父节点指针
    Node<ValueType> *parent;
    // 禁止默认构造函数，防止父指针未被初始化
    Node() = delete;
    // 唯一的构造函数
    Node(const int key, const ValueType &value,
        Node<ValueType> *&parent)
        :value(value), parent(parent), key(key) {}
};

// 二叉树定义，需要传入存储的值类型和空值的表示
template<typename ValueType, const ValueType NULL_VALUE>
class BinaryTree {
private:
    using NodeType = Node<ValueType>;
    // 根结点定义
    NodeType *head = nullptr;
    // 标记树是否被初始化
    bool initalized = false;
    // key是键，内部为结点唯一分配，相当于ID
    int key = 0;
    // 释放二叉树空间
    void freeTree(NodeType *&node) {
        if (node != nullptr) {
            // 先递归调用释放子树
            freeTree(node->left);
            freeTree(node->right);
            // 释放当前结点
            delete node;
            // 置为null
            node = nullptr;
        }
    }

    // 重载函数，获取树的深度
    int BiTreeDepth(const NodeType *node) {
        // 当前结点不为空才继续
        if (node != nullptr) {
            // 获取左右结点最深的，加一返回
            int left = BiTreeDepth(node->left);
            int right = BiTreeDepth(node->right);
            return std::max(left, right) + 1;
        }
        // 递归终止条件
        // 为空结束返回0
        return 0;
    }

    // 重载前序遍历
    void PreOrderTraverse(const NodeType *node,
        const Visit<ValueType> &visit) {
        // 结点为空为递归终止条件
        if (node != nullptr) {
            // 前序遍历先遍历当前结点
            visit(node->value);
            // 依次左右结点
            PreOrderTraverse(node->left, visit);
            PreOrderTraverse(node->right, visit);
        }
    }

    // 重载中序遍历
    void InOrderTraverse(const NodeType *node,
        const Visit<ValueType> &visit) {
        // 递归终止同前序遍历
        if (node != nullptr) {
            // 左中右顺序遍历
            InOrderTraverse(node->left, visit);
            visit(node->value);
            InOrderTraverse(node->right, visit);
        }
    }

    // 重载后序遍历，详细内容同上
    void PostOrderTraverse(const NodeType *node,
        const Visit<ValueType> &visit) {
        if (node != nullptr) {
            // 顺序左右中
            PostOrderTraverse(node->left, visit);
            PostOrderTraverse(node->right, visit);
            visit(node->value);
        }
    }

    // 根据key寻找结点，返回值为找到的结点指针或者nullptr
    NodeType *find_by_key(NodeType *node, const int key) {
        // 同样递归终止条件为指针参数为空
        if (node != nullptr) {
            // 找到就返回指针
            if (node->key == key) {
                return node;
            }
            // 向左边寻找
            auto left = find_by_key(node->left, key);
            if (left != nullptr) {
                return left;
            }
            // 向右边寻找
            auto right = find_by_key(node->right, key);
            if (right != nullptr) {
                return right;
            }
        }
        // 默认返回nullptr
        return nullptr;
    }

    // 对建树进行重载的函数
    void CreateBiTree(NodeType *&node, NodeType *parent,
        std::vector<ValueType> values, size_t &index) {
        // 当前下标参数未超出vector范围并且此处值不为空
        if (index < values.size() && values[index] != NULL_VALUE) {
            // 将node赋值为新开辟的结点，key进行自增
            node = new NodeType(key++, values[index], parent);
            // 递归进行左右构建
            CreateBiTree(node->left, node, values, ++index);
            CreateBiTree(node->right, node, values, ++index);
        }
    }

    // 展示现有树的结点，输出key及对应的值
    void display(const NodeType *node) {
        if (node != nullptr) {
            std::cout << "key: " << node->key << ", value: " << node->value << "\n";
            // 递归对左右进行调用
            display(node->left);
            display(node->right);
        }
    }

    // 重载插入子树操作
    void InsertChild(NodeType *&node, const NodeType *insert_node, const LR &lr) {
        // 此操作将给出的子树进行整棵复制而不是直接接入，防止外部释放子树后出现问题
        // 参数为要进行赋值的结点引用
        if (insert_node != nullptr) {
            // 获取插入位置是左还是右
            auto &chi_node = lr == LR::L ? node->left : node->right;
            // 对获取到的结点赋值
            chi_node = new NodeType(key++, insert_node->value, node);
            // 递归复制
            InsertChild(chi_node, insert_node->left, LR::L);
            InsertChild(chi_node, insert_node->right, LR::R);
        }
    }

public:
    // 初始化树的函数
    status InitBiTree() {
        // 首先判断树是否已被初始化
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return ERROR;
        }
        // 将初始化标志设置为true
        initalized = true;
        return OK;
    }

    // 销毁树的函数
    status DestroyBiTree() {
        // 常规检测
        if (initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }
        // 释放空间
        freeTree(head);
        // 更改初始化状态
        initalized = false;
        // key归0
        key = 0;

        return OK;
    }

    // 使用值序列建树的函数
    status CreateBiTree() {
        // 检测是否被初始化
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }
        // 提示输入树的
        std::cout << "Please enter the defination of tree: ";
        // 管它有木有默认构造函数。。。
        ValueType value;
        // 设置一个值类型的vector
        std::vector<ValueType> values;
        getchar();
        //getchar();
        // 尝试得到值序列
        while (value = getchar()) {
            // 没按回车就继续
            if (value != '\n') {
                values.push_back(value);
                continue;
            }
            break;
        }
        // 输出读入的元素个数
        std::cout << "Read " << values.size() << " value elements\n";
        size_t index = 0;
        // 使用序列建树
        CreateBiTree(head, nullptr, values, index);

        return OK;
    }

    // 将树清空的函数
    status ClearBiTree() {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }
        // 清理空间
        freeTree(head);
        // key归0
        key = 0;
        return OK;
    }

    // 判断树是否为空的函数
    status BiTreeEmpty() {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return true;
        }

        // 判断深度是否为0即可
        return BiTreeDepth() == 0;
    }

    // 得到树的深度，或者说高度
    int BiTreeDepth() {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return 0;
        }
        // 直接对根节点使用重载的函数
        return BiTreeDepth(head);
    }
    // 获取根节点
    NodeType *Root() const {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }

        // 可以直接返回根结点
        return head;
    }

    // 获取key对应的结点的值
    ValueType Value(const int _key) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return NULL_VALUE;
        }
        // 先寻找结点指针
        auto node = find_by_key(head, _key);
        // 为空说明不存在
        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << _key << "!\n";
            return NULL_VALUE;
        }
        // 返回结点的值
        return node->value;
    }

    // 对结点进行赋值操作
    status Assign(const int _key, const ValueType &value) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }
        // 先寻找对应结点指针
        auto node = find_by_key(head, _key);

        if (node == nullptr) {
            std::cerr << "The tree has no node with key: " << _key << "!\n";
            return ERROR;
        }

        // 赋值
        node->value = value;
        return OK;
    }

    // 寻找结点的父结点
    NodeType *Parent(const int _key) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }

        // 先寻找一下key对应的结点
        auto node = find_by_key(head, _key);
        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << _key << "!\n";
            return nullptr;
        }

        // node不为空就存在父节点
        return node->parent;
    }

    // 返回对应结点的左孩子指针
    NodeType *LeftChildren(const int _key) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }
        // 先找到前结点
        auto node = find_by_key(head, _key);
        if (node == nullptr) {
            std::cerr << "The tree has no node with key: " << _key << "!\n";
            return nullptr;
        }
        // 返回左孩子
        return node->left;
    }

    // 逻辑同上
    NodeType *RightChildren(const int _key) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }

        auto node = find_by_key(head, _key);

        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << _key << "!\n";
            return nullptr;
        }

        return node->right;
    }

    // 获取左兄弟结点
    NodeType *LeftSibling(const int _key) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }
        // 先找到当前结点
        auto node = find_by_key(head, _key);
        // 判断是否为空
        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << _key << "!\n";
            return nullptr;
        }
        // 判断父结点是否为空
        if (node->parent == nullptr) {
            std::cerr << "Node is head pointer! no sibling.\n";
            return nullptr;
        }
        // 判断此节点是否就是父节点的左孩子
        if (node->parent->left == node) {
            std::cout << "This node has no left sibling.\n";
            return nullptr;
        }
        // 返回左兄弟结点
        return node->parent->left;
    }

    // 基本思路同上
    NodeType *RightSibling(const int _key) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }

        auto node = find_by_key(head, _key);

        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << _key << "!\n";
            return nullptr;
        }

        if (node->parent == nullptr) {
            std::cerr << "Node is head pointer! no sibling.\n";
            return nullptr;
        }

        if (node->parent->right == node) {
            std::cout << "This node has no right sibling.\n";
            return nullptr;
        }

        return node->parent->right;
    }

    // 插入子树函数
    status InsertChild(const int _key, const LR &lr,
        const BinaryTree<ValueType, NULL_VALUE> &tree) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }
        // 获取key对应结点指针
        NodeType *node = find_by_key(head, _key);

        if (node == nullptr) {
            std::cerr << "The tree has no node with key: " << _key << "!\n";
            return ERROR;
        }

        if (tree.head == nullptr) {
            return OK;
        }

        if (tree.head->right != nullptr) {
            std::cerr << "Right node of tree's head node is not empty.\n";
            return ERROR;
        }

        NodeType *rest_node = nullptr;
        if (lr == LR::L) {
            rest_node = node->left;
            node->left = new NodeType(key++, tree.head->value, node);
            if (rest_node != nullptr) {
                rest_node->parent = node->left;
                node->left->right = rest_node;
            }
            InsertChild(node->left, tree.head->left, LR::L);
        }
        else {
            rest_node = node->right;
            node->right = new NodeType(key++, tree.head->value, node);
            if (rest_node != nullptr) {
                rest_node->parent = node->right;
                node->right->right = rest_node;
            }
            InsertChild(node->right, tree.head->right, LR::R);
        }

        return OK;
    }

    // 删除子树，操作类似于插入
    status DeleteChild(const int _key, const LR &lr) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }

        auto node = find_by_key(head, _key);
        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << _key << "!\n";
            return ERROR;
        }

        freeTree(lr == LR::L ? node->left : node->right);

        return OK;
    }

    // 前序遍历
    status PreOrderTraverse(const Visit<ValueType> &visit) {
        if (!initalized) {
            std::cerr << "This binary tree has not been initalized.\n";
            return ERROR;
        }
        PreOrderTraverse(head, visit);

        return OK;
    }

    // 中序遍历
    status InOrderTraverse(const Visit<ValueType> &visit) {
        if (!initalized) {
            std::cerr << "This binary tree has not been initalized.\n";
            return ERROR;
        }
        InOrderTraverse(head, visit);

        return OK;
    }

    // 后序遍历
    status PostOrderTraverse(const Visit<ValueType> &visit) {
        if (!initalized) {
            std::cerr << "This binary tree has not been initalized.\n";
            return ERROR;
        }
        PostOrderTraverse(head, visit);

        return OK;
    }

    // 层序遍历
    status LevelOrderTraverse(const Visit<ValueType> &visit) {
        if (!initalized) {
            std::cerr << "This binary tree has not been initalized.\n";
            return ERROR;
        }
        // 需要借助队列
        std::queue<NodeType*> nodes;
        // 将头节点压入nodes
        nodes.push(head);
        while (!nodes.empty()) {
            // 得到最后的压入的结点
            const NodeType* node = nodes.front();
            // 将其弹出队列
            nodes.pop();
            // 访问值
            visit(node->value);
            // 压入左右非空结点
            if (node->left != nullptr) {
                nodes.push(node->left);
            }
            if (node->right != nullptr) {
                nodes.push(node->right);
            }
        }

        return OK;
    }

    // 重载输入运算符
    friend std::istream &operator>>(std::istream &is,
        BinaryTree<ValueType, NULL_VALUE> &tree) {
        if (!tree.initalized) {
            tree.InitBiTree();
            tree.CreateBiTree();
        }
        else {
            tree.ClearBiTree();
            tree.CreateBiTree();
        }

        return is;
    }

    void displsy() {
        display(head);
    }
};

#endif // !DATASTRUCTURE_BINARY_TREE_H

