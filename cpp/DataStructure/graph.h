#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include "status.h"

// 图的模板定义
template<typename T>
class Graph {
private:
    template<typename T>
    struct Node {
        // 结点值定义
        T value;
        // 指向下个边结点的指针
        Node<T> *next = nullptr;
        // 构造函数
        Node<T>(const T &value) : value(value) {}
    };
    //using NodeType = Node<T>;
    template<typename T>
    struct Vertex {
        // 键：标识一个顶点
        int key;
        // 值域
        T value;
        // 和本结点相连的点的链表
        Node<T> *next_node = nullptr;
        // 下一个图结点的指针
        Vertex<T> *next_vertex = nullptr;
        // 构造函数
        Vertex<T>(const T &value, const int &key) : value(value), key(key) {}

        void add_node(const T &value) {
            if (next_node == nullptr) {
                next_node = new Node<T>(value);
            }
            else {
                auto temp_n = next_node;
                while (temp_n->next != nullptr) {
                    temp_n = temp_n->next;
                }
                temp_n->next = new Node<T>(value);
            }
        }
    };
    //using VertexType = Vertex<T>;
    int key = 0;
    // 建立从key到值的映射
    std::map<int, T> map;
    // 头顶点指针
    Vertex<T> *head = nullptr;
    // 是否初始化过
    bool initalized = false;
    // 释放图所占空间
    bool free_graph() {
        auto temp_v = head, next_v = temp_v;
        while (temp_v != nullptr) {
            next_v = temp_v->next_vertex;
            auto temp_n = temp_v->next_node, next_n = temp_n;
            while (temp_n != nullptr) {
                next_n = temp_n->next;
                delete(temp_n);
                temp_n = next_n;
            }
            delete(temp_v);
            temp_v = next_v;
        }

        return true;
    }
public:
    // 必须在这里设置下别名才能访问到
    using VertexType = Vertex<T>;
    using NodeType = Node<T>;
    // 建立图的函数
    status CreateGraph(const std::vector<T> &nodes,
        const std::vector<std::pair<T, T>> &edges) {
        if (initalized) {
            std::cout << "Your graph had been initialized, please destroy it before create.\n";
            return ERROR;
        }

        // 先将顶点处理了
        decltype(head) last_node = nullptr;
        // 键值映射先清空
        map.clear();
        for (size_t i = 0; i < nodes.size(); i++) {
            if (i == 0) {
                last_node = head = new VertexType(nodes[i], key++);
            }
            else {
                last_node = last_node->next_vertex = new VertexType(nodes[i], key++);
            }
            map[last_node->key] = last_node->value;
        }

        // 使用邻接表建图
        for (const auto &edge : edges) {
            auto v1 = edge.first, v2 = edge.second;
            VertexType *temp_v = head;
            while (temp_v != nullptr) {
                if (temp_v->value == v1) {
                    temp_v->add_node(v2);
                }
                else if (temp_v->value == v2) {
                    temp_v->add_node(v1);
                }
            }
        }
        // 初始化完成
        initalized = true;

        return OK;
    }

    // 销毁图的函数
    status DestroyGraph() {
        if (!initalized) {
            std::cerr << "This graph has not been initalized.\n";
            return ERROR;
        }

        if (free_graph()) {
            key = 0;
            initalized = false;
            return OK;
        }
        else {
            return ERROR;
        }
    }

    // 查找顶点的位置信息
    status LocateVertex(const T &vertex) {

        return ERROR;
    }

    // 通过key寻找结点
    status GetVertex(T &value, const int &ver_key) {
        if (!initalized) {
            std::cerr << "This graph has not been initalized.\n";
            return ERROR;
        }
        // 标记是否找到
        bool found = false;
        auto temp_v = head;
        // 遍历顶点集合
        while (temp_v != nullptr && !found) {
            if (temp_v->key == ver_key) {
                found = true;
                value = temp_v->value;
                break;
            }

            temp_v = temp_v->next_vertex;
        }

        return found ? OK : ERROR;
    }

    status PutVertex(const T &value, const int &ver_key) {
        if (!initalized) {
            std::cerr << "This graph has not been initalized.\n";
            return ERROR;
        }
        T find_value;
        if ((const auto &it = map.find(ver_key)) != map.cend()) {
            find_value = it->second;
            // 找到了就需要遍历了
            // 先把map更新一下
            map[ver_key] = value;
            auto temp_v = head;
            while (temp_v != nullptr) {
                // 顶点也要更新
                if (temp_v->value == find_value) {
                    temp_v->value = value;
                }
                auto temp_n = temp_v->next_node;
                while (temp_n != nullptr) {
                    // 找到了对应的node将值更新
                    if (temp_n->value == find_value) {
                        temp_n->value = value;
                        break;
                    }
                    // 后移
                    temp_n = temp_n->next;
                }
                // 向后移动
                temp_v = temp_v->next;
            }
        }
        else {
            // 没有找到，说明顶点集里没有参数给的
            return ERROR;
        }
        

        return OK;
    }

    NodeType *FirstAdjacentVertex(const int &ver_key) {
        if (!initalized) {
            std::cerr << "This graph has not been initalized.\n";
            return ERROR;
        }
        auto *vertex = head;
        while (vertex != nullptr) {
            if (vertex->key == ver_key) {
                return vertex->next_node;
            }
            vertex = vertex->next_vertex;
        }

        return nullptr;
    }

    NodeType *NextAdjacentVertex(const int &ver_key, const int &node_key) {
        if (!initalized) {
            std::cerr << "This graph has not been initalized.\n";
            return ERROR;
        }
        auto *nodes = FirstAdjacentVertex(ver_key);
        if ((auto & it = map.find(node_key)) != map.cend()) {
            T value = it->second;
            while (nodes != nullptr) {
                if (nodes->value == value) {
                    return nodes->next;
                }
                nodes = nodes->next;
            }
        }

        return nullptr;
    }

    status InsertVertex(const T &value) {
        if (!initalized) {
            std::cerr << "This graph has not been initalized.\n";
            return ERROR;
        }
        auto temp_v = head;
        while (temp_v->next != nullptr) {
            temp_v = temp_v->next_vertex;
        }

        temp_v->next_vertex = new VertexType(value, key++);
        map[temp_v->next_vertex->key] = value;

        return OK;
    }

    status DeleteVertex(const int &ver_key) {
        if (!initalized) {
            std::cerr << "This graph has not been initalized.\n";
            return ERROR;
        }

        T value;
        auto temp_v = head;
        // 删除结点有点麻烦，需要删除边和链表中的结点
        // 要删除的结点为首节点
        if (temp_v->key == ver_key) {
            head = head->next_vertex;
            value = temp_v->value;
        }
        else {
            while (temp_v->next_vertex != nullptr) {
                if (temp_v->next_vertex->value = value) {

                }
            }
        }

        return OK;
    }

    status InsertArc(const std::pair<T, T> &edge) {

        return OK;
    }

    status DeleteArc(const T &v1, const T &v2) {

        return OK;
    }

    status DFSTraverse(const Visit<T> &visit) {

        return OK;
    }

    status BFSTraverse(const Visit<T> &visit) {

        return OK;
    }

    void display() {
        auto temp_v = head;
        while (temp_v != nullptr) {
            std::cout << "key: " << temp_v->key << ", value: " << temp_v->value << "\n";
            temp_v = temp_v->next_vertex;
        }
    }
};

template<typename T>
void input_vertexes(std::vector<T> &vertexes) {
    std::cout << "PLease enter count of vertexes: ";
    size_t count = 0;
    std::cin >> count;
    T value;
    vertexes.clear();
    vertexes.reserve(count);
    std::cout << "PLease enter the value of vertexes: ";
    for (size_t i = 0; i < count; i++) {
        std::cin >> value;
        vertexes.push_back(value);
    }
    return;
}

template<typename T>
void input_edges(std::vector<std::pair<T, T>> &edges) {
    std::cout << "Please enter count of edges: ";
    size_t count = 0;
    std::cin >> count;
    T v1, v2;
    edges.clear();
    edges.reserve(count);
    std::cout << "Please enter these edges: ";
    for (size_t i = 0; i < count; i++) {
        std::cin >> v1 >> v2;
        edges.push_back(std::make_pair(v1, v2));
    }
    return;
}

#endif // !DATASTRUCTURE_GRAPH_H