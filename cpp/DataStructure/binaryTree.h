#ifndef DATASTRUCTURE_BINARY_TREE_H
#define DATASTRUCTURE_BINARY_TREE_H
#include <queue>
#include <vector>
#include "status.h"

// Binary tree node defination
template<typename ValueType>
struct Node {
    int key;
    // value in node
    ValueType value;
    // left children pointer
    Node<ValueType> *left = nullptr;
    // right children pointer
    Node<ValueType> *right = nullptr;
    // parent pointer
    Node<ValueType> *parent;

    Node() = delete;
    Node(const int key, ValueType value,
        Node<ValueType> *&parent)
        :value(value), parent(parent), key(key) {}
};

// Binary tree
template<typename ValueType, const ValueType NULL_VALUE>
class BinaryTree {
private:
    using NodeType = Node<ValueType>;
    // head node pointer
    NodeType *head = nullptr;
    // mark if the tree has been initalized
    bool initalized = false;
    int key = 0;
    // destroy the tree
    void freeTree(NodeType *&node) {
        if (node != nullptr) {
            freeTree(node->left);
            freeTree(node->right);
            delete node;
            node = nullptr;
        }
    }

    // get depth of tree
    int BiTreeDepth(const NodeType *node) {
        if (node == nullptr) {
            return 0;
        }

        int left = BiTreeDepth(node->left);
        int right = BiTreeDepth(node->right);
        return std::max(left, right) + 1;
    }

    // preorder traverse overload
    void PreOrderTraverse(const NodeType *node,
        const Visit<ValueType> &visit) {
        if (node != nullptr) {
            // visit node first
            visit(node->value);
            // left node
            PreOrderTraverse(node->left, visit);
            // right node
            PreOrderTraverse(node->right, visit);
        }
    }

    // inorder traverse overload
    void InOrderTraverse(const NodeType *node,
        const Visit<ValueType> &visit) {
        if (node != nullptr) {
            // inorder left child
            InOrderTraverse(node->left, visit);
            // visit node value
            visit(node->value);
            // visit right node value
            InOrderTraverse(node->right, visit);
        }
    }

    void PostOrderTraverse(const NodeType *node,
        const Visit<ValueType> &visit) {
        if (node != nullptr) {
            // visit left node
            PostOrderTraverse(node->left, visit);
            // visit right node
            PostOrderTraverse(node->right, visit);
            // visit node value
            visit(node->value);
        }
    }

    NodeType *find_by_key(NodeType *node, const int key) {
        if (node != nullptr) {

            if (node->key == key) {
                return node;
            }

            auto left = find_by_key(node->left, key);
            if (left != nullptr) {
                return left;
            }
            auto right = find_by_key(node->right, key);
            if (right != nullptr) {
                return right;
            }
        }

        return nullptr;
    }

    void CreateBiTree(NodeType *&node, NodeType *parent,
        std::vector<ValueType> values, size_t &index) {
        if (index < values.size() && values[index] != NULL_VALUE) {
            node = new NodeType(key++, values[index], parent);
            CreateBiTree(node->left, node, values, ++index);
            CreateBiTree(node->right, node, values, ++index);
        }
    }

    void display(const NodeType *node) {
        if (node != nullptr) {
            std::cout << "key: " << node->key << ", value: " << node->value << "\n";
            display(node->left);
            display(node->right);
        }
    }

    void InsertChildren(NodeType *&node, NodeType *&c_node, const LR &lr) {
        if (c_node != nullptr) {
            auto &chi_node = lr == LR::L ? node->left : node->right;

            chi_node = new NodeType(key++, c_node->value, node);
            InsertChildren(chi_node, c_node->left, LR::L);
            InsertChildren(chi_node, c_node->right, LR::R);
        }
    }

public:
    status InitBiTree() {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return ERROR;
        }
        // nothing to do
        initalized = true;
        return OK;
    }

    status DestroyBiTree() {
        // clear the space used and set initalized to false
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return ERROR;
        }

        freeTree(head);
        head = nullptr;
        initalized = false;
        key = 0;

        return OK;
    }

    status CreateBiTree() {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }

        std::cout << "Please enter the defination of tree: ";
        ValueType value;
        std::vector<ValueType> values;
        getchar();
        while (value = getchar()) {
            if (value != '\n') {
                values.push_back(value);
            }
            else {
                break;
            }
        }

        std::cout << values.size() << "\n";
        size_t index = 0;
        CreateBiTree(head, nullptr, values, index);

        return OK;
    }

    status ClearBiTree() {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return ERROR;
        }

        freeTree(head);
        key = 0;
        return OK;
    }

    status BiTreeEmpty() {
        if (!initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return true;
        }

        // just check if the head is nullptr
        return head == nullptr;
    }

    // get the depth of tree
    int BiTreeDepth() {
        if (!initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return 0;
        }

        return BiTreeDepth(head);
    }

    NodeType *Root() {
        if (!initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return nullptr;
        }

        // return head pointer
        return head;
    }

    ValueType Value(const int key) {
        if (!initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return NULL_VALUE;
        }

        auto node = find_by_key(head, key);
        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << key << "!\n";
            return NULL_VALUE;
        }

        return node->value;
    }

    status Assign(const int key, const ValueType value) {
        if (!initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return ERROR;
        }

        auto node = find_by_key(head, key);

        if (node == nullptr) {
            std::cerr << "The tree has no node with key: " << key << "!\n";
            return ERROR;
        }

        node->value = value;
        return OK;
    }

    NodeType *Parent(const int key) {
        if (!initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return nullptr;
        }

        auto node = find_by_key(head, key);
        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << key << "!\n";
            return nullptr;
        }

        return node->parent;
    }

    NodeType *LeftChildren(const int key) {
        if (!initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return nullptr;
        }

        auto node = find_by_key(head, key);
        if (node == nullptr) {
            std::cerr << "The tree has no node with key: " << key << "!\n";
            return nullptr;
        }

        return find_by_key(head, key)->left;
    }

    NodeType *RightChildren(const int key) {
        if (!initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return nullptr;
        }

        auto node = find_by_key(head, key);

        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << key << "!\n";
            return nullptr;
        }

        return find_by_key(head, key)->right;
    }

    NodeType *LeftSibling(const int key) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }

        auto node = find_by_key(head, key);

        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << key << "!\n";
            return nullptr;
        }

        if (node->parent == nullptr) {
            std::cerr << "Node is head pointer! no sibling.\n";
            return nullptr;
        }

        if (node->parent->left == node) {
            std::cout << "This node has no left sibling.\n";
            return nullptr;
        }

        return node->parent->left;
    }

    NodeType *RightSibling(const int key) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }

        auto node = find_by_key(head, key);

        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << key << "!\n";
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

    status InsertChildren(const int key, const LR &lr,
        BinaryTree<ValueType, NULL_VALUE> &tree) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }

        NodeType *node = find_by_key(head, key);

        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << key << "!\n";
            return ERROR;
        }
        
        if (lr == LR::L && node->left != nullptr || lr == LR::R && node->right != nullptr) {
            std::cout << "The children tree is not null!\n";
            return ERROR;
        }
        InsertChildren(node, tree.head, lr);

        return OK;
    }

    status DeleteChild(const int key, const LR &lr) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }

        auto node = find_by_key(head, key);

        if (node == nullptr) {
            std::cout << "The tree has no node with key: " << key << "!\n";
            return ERROR;
        }
        freeTree(lr == LR::L ? node->left : node->right);

        return OK;
    }

    // preorder tarverse the tree
    status PreOrderTraverse(const Visit<ValueType> &visit) {
        if (!initalized) {
            std::cerr << "This binary tree has not been initalized.\n";
            return ERROR;
        }
        PreOrderTraverse(head, visit);

        return OK;
    }

    status InOrderTraverse(const Visit<ValueType> &visit) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }

        InOrderTraverse(head, visit);
        return OK;
    }

    status PostOrderTraverse(const Visit<ValueType> &visit) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }
        PostOrderTraverse(head, visit);
        return OK;
    }

    status LevelOrderTraverse(const Visit<ValueType> &visit) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }

        std::queue<NodeType*> nodes;
        nodes.push(head);
        while (!nodes.empty()) {
            const NodeType* node = nodes.front();
            nodes.pop();
            visit(node->value);
            node->left != nullptr ? nodes.push(node->left) : 0;
            node->right != nullptr ? nodes.push(node->right) : 0;
        }

        return OK;
    }

    friend std::istream &operator>>(std::istream &is,
        BinaryTree<ValueType, NULL_VALUE> &tree) {
        if (!tree.initalized) {
            tree.initalized = true;
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

