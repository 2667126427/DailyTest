#ifndef DATASTRUCTURE_BINARY_TREE_H
#define DATASTRUCTURE_BINARY_TREE_H
#include "status.h"

// Binary tree node defination
template<typename T>
struct Node {
    // value in node
    T value;
    // left children pointer
    Node<T> *left = nullptr;
    // right children pointer
    Node<T> *right = nullptr;
    // parent pointer
    Node<T> *parent;

    Node() = delete;
    Node(const T &value, const Node<T> *&parent) 
        :value(value), parent(parent) {}
};

// Binary tree
template<typename T>
class BinaryTree {
private:
    // head node pointer
    Node<T> *head = nullptr;
    // mark if the tree has been initalized
    bool initalized = false;
    // destroy the tree
    void freeTree(const Node *&node) {
        if (node != nullptr) {
            freeTree(node->left);
            freeTree(node->right);
            delete node;
            node = nullptr;
        }
    }

    // get depth of tree
    int BiTreeDepth(const Node *&node) {
        if (node == nullptr) {
            return 0;
        }

        int left = BiTreeDepth(node->left);
        int right = BiTreeDepth(node->right);
        return std::max(left, right) + 1;
    }

    // create binary tree function overload
    void CreateBiTree(Node *&node) {
        int t = value;
        std::cin >> value;
        if (value == -1) {
            node = nullptr;
        }
        else {
            node->value = value;
            CreateBiTree(node->left);
            CreateBiTree(node->right);
        }
    }

    // preorder traverse overload
    void PreOrderTraverse(const Node<T> *&node, const Visit<T> &visit) {
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
    void InOrderTraverse(const Node<T> *&node, const Visit<T> &visit) {
        if (node != nullptr) {
            // inorder left child
            InOrderTraverse(node->left, visit);
            // visit node value
            visit(node->value);
            // visit right node value
            InOrderTraverse(node->right, visit);
        }
    }

    void PostOrderTraverse(const Node<T> *&node, const Visit<T> &visit) {
        if (node != nullptr) {
            // visit left node
            PostOrderTraverse(node->left, visit);
            // visit right node
            PostOrderTraverse(node->right, visit);
            // visit node value
            visit(node->value);
        }
    }

public:
    status InitBiTree() {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return ERROR;
        }
        // nothing to do
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

        return OK;
    }

    status CreateBiTree() {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return ERROR;
        }

        // first free the old tree
        freeTree(head);
        std::cout << "enter -1 to means space.\n";
        CreateBiTree(head);

        return OK;
    }

    status ClearBiTree() {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return ERROR;
        }

        freeTree(head);
        return OK;
    }

    status BiTreeEmpty() {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return true;
        }

        // just check if the head is nullptr
        return head == nullptr;
    }

    // get the depth of tree
    int BiTreeDepth() {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return 0;
        }
        return BiTreeDepth(head);
    }

    Node *Root() {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return nullptr;
        }

        // return head pointer
        return head;
    }

    const T Value(const Node<T> *&node) {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            T t;
            return t;
        }

        if (node == nullptr) {
            T t;
            // return a default value
            return t;
        }
        // return the node value
        return node->value;
    }

    status Assign(const Node<T> *&node, const T &value) {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return ERROR;
        }

        // warning: null pointer operation
        if (node == nullptr) {
            std::cerr << "The parameter is null!\n";
            return ERROR;
        }
        // set the given value
        node->value = value;
        return OK;
    }

    Node<T> *Parent(const Node<T> *&node) {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return nullptr;
        }

        if (node == nullptr) {
            std::cerr << "Parameter node is null!\n";
            return nullptr;
        }

        return node->parent;
    }

    Node<T> *LeftChildren(const Node<T> *&node) {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return nullptr;
        }
        
        if (node == nullptr) {
            std::cerr << "The parameter is null!\n";
            return nullptr;
        }

        return node->left;
    }

    Node<T> *RightChildren(const Node<T> *&node) {
        if (initalized) {
            std::cerr << "The binary tree has been initalized.\n";
            return nullptr;
        }

        if (node == nullptr) {
            std::cerr << "The parameter is null!\n";
            return nullptr;
        }

        return node->right;
    }

    // left brother
    Node<T> *LeftSibling(const Node<T> *&node) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }
        if (node == nullptr) {
            std::cerr << "Parameter is null!\n";
            return nullptr;
        }

        if (node->parent->left == node) {
            std::cerr << "Parameter node is left child.\n";
            return nullptr;
        }
        // node is head pointer, its parent pointer is nullptr
        if (node->parent == nullptr) {
            std::cerr << "Node is head pointer! no sibling.\n";
            return nullptr;
        }

        return node->parent->left;
    }

    Node<T> *RightSibling(const Node<T> *&node) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return nullptr;
        }
        if (node == nullptr) {
            std::cerr << "Parameter is null!\n";
            return nullptr;
        }

        if (node->parent->right == node) {
            std::cerr << "Parameter node is left child.\n";
            return nullptr;
        }
        // node is head pointer, its parent pointer is nullptr
        if (node->parent == nullptr) {
            std::cerr << "Node is head pointer! no sibling.\n";
            return nullptr;
        }

        return node->parent->right;
    }

    // TODO
    status InsertChildren(Node<T> *&node, const LR &lr, BinaryTree<T> &tree) {

    }
    // TODO
    status DeleteChild(Node<T> *&node, const LR &lr) {

    }

    // preorder tarverse the tree
    status PreOrderTraverse(const Visit<T> &visit) {
        if (!initalized) {
            std::cerr << "This binary tree has not been initalized.\n";
            return ERROR;
        }
        PreOrderTraverse(head, visit);

        return OK;
    }

    status InOrderTraverse(const Visit<T> &visit) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }

        InOrderTraverse(head, visit);
        return OK;
    }

    status PostOrderTraverse(const Visit<T> &visit) {
        if (!initalized) {
            std::cerr << "The binary tree has not been initalized.\n";
            return ERROR;
        }
        PostOrderTraverse(head, visit);
        return OK;
    }
};

#endif // !DATASTRUCTURE_BINARY_TREE_H
