#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include "status.h"

// 图的模板定义
template<typename T>
class Graph {
private:
    // 结点定义
    template<typename U>
    struct Node {
        // 结点值定义
        U value;
        // 指向下个边结点的指针
        Node<U> *next = nullptr;
        // 构造函数
        explicit Node<U>(const U &value) : value(value) {}
    };

    // 顶点定义
    template<typename U>
    struct Vertex {
        // 键：标识一个顶点
        int key;
        // 值域
        U value;
        // 和本结点相连的点的链表
        Node<U> *next_node = nullptr;
        // 下一个图结点的指针
        Vertex<U> *next_vertex = nullptr;

        // 构造函数
        Vertex<U>(const U &value, const int &key) 
            : value(value), key(key) {}
        // 添加结点
        bool add_node(const U &value) {
            if (next_node == nullptr) {
                next_node = new Node<U>(value);
                return true;
            }
            else {
                auto temp_n = next_node;
                while (temp_n->next != nullptr) {
                    if (temp_n->next->value == value) {
                        return false;
                    }
                    temp_n = temp_n->next;
                }
                temp_n->next = new Node<U>(value);
                return true;
            }

            return false;
        }
        // 删除结点
        bool remove_node(const U &value) {
            if (next_node != nullptr) {
                if (next_node->value == value) {
                    auto t = next_node;
                    next_node = next_node->next;
                    delete (t);
                    return true;
                }
                else {
                    auto temp_n = next_node;
                    while (temp_n->next != nullptr) {
                        if (temp_n->next->value == value) {
                            auto t = temp_n->next;
                            temp_n->next = t->next;
                            delete (t);
                            return true;
                        }
                        temp_n = temp_n->next;
                    }
                }
            }

            return false;
        }
    };

    //using VertexType = Vertex<T>;
    int key = 0;
    // 建立从key到值的映射
    std::map<int, T> map;
    // 头顶点指针
    Vertex<T> *head = nullptr;
    // 是否初始化过
    bool initialized = false;

    // 释放图所占空间
    bool free_graph() {
        auto temp_v = head, next_v = temp_v;
        while (temp_v != nullptr) {
            next_v = temp_v->next_vertex;
            auto temp_n = temp_v->next_node, next_n = temp_n;
            while (temp_n != nullptr) {
                next_n = temp_n->next;
                delete (temp_n);
                temp_n = next_n;
            }
            delete (temp_v);
            temp_v = next_v;
        }

        head = nullptr;

        return true;
    }

    // 根据结点值查找结点指针，找不到就返回空指针
    Vertex<T> *find_vertex_by_value(const T &value) const {
        auto temp_v = head;
        // 遍历查找
        while (temp_v != nullptr) {
            if (temp_v->value == value) {
                return temp_v;
            }
            // 向后移动指针避免死循环
            temp_v = temp_v->next_vertex;
        }
        // 查找失败返回空指针
        return nullptr;
    }

    // 释放结点空间
    void freeVertex(const Vertex<T> *vertex) {
        auto temp_n = vertex->next_node, next_n = temp_n;
        // 遍历结点邻接表，释放空间
        while (temp_n != nullptr) {
            next_n = temp_n->next;
            // delete空间
            delete (temp_n);
            temp_n = next_n;
        }

        // 释放当前结点空间
        delete (vertex);
    }

    // 深度遍历函数
    status DFSTraverse(const Vertex<T> *vertex, 
        std::map<T, bool> &visited, 
        const Visit<T> &visit) const {
        // 先访问当前节点值
        visit(vertex->value);
        // 获取当前顶点的结点邻接表
        auto temp_n = vertex->next_node;
        while (temp_n != nullptr) {
            // 结点值未遍历就递归进行DFS
            if (!visited[temp_n->value]) {
                visited[temp_n->value] = true;
                DFSTraverse(find_vertex_by_value(temp_n->value), 
                    visited, visit);
            }
            // 结点指针后移，防止死循环
            temp_n = temp_n->next;
        }

        return OK;
    }

    // 广度遍历
    status BFSTraverse(const Vertex<T> *vertex,
        std::map<T, bool> &visited,
        const Visit<T> &visit) const {
        // 使用队列遍历存储未遍历的结点的指针
        std::queue<const Vertex<T>*> vertexes;
        // 结点入队列
        vertexes.push(vertex);
        visited[vertex->value] = true;
        // 队列非空继续遍历
        while (!vertexes.empty()) {
            const auto v = vertexes.front();
            visit(v->value);
            auto temp_n = v->next_node;
            // 将当前结点非空的结点全部加入
            while (temp_n != nullptr) {
                if (!visited[temp_n->value]) {
                    vertexes.push(find_vertex_by_value(temp_n->value));
                    visited[temp_n->value] = true;
                }
                temp_n = temp_n->next;
            }
            // 已经访问过的结点pop掉
            vertexes.pop();
        }

        return OK;
    }

public:
    // 必须在这里设置下别名才能在别的文件访问到
    using VertexType = Vertex<T>;
    using NodeType = Node<T>;

    // 建立图的函数
    status CreateGraph(const std::vector<T> &nodes,
        const std::vector<std::pair<T, T>> &edges) {
        if (initialized) {
            std::cout << "Your graph had been initialized,\
                please destroy it before create.\n";
            return ERROR;
        }

        // 先将顶点处理了
        decltype(head) last_node = nullptr;
        // 键值映射先清空
        map.clear();
        for (size_t i = 0; i < nodes.size(); i++) {
            // 首个结点将head设置为第一个vertex的地址
            if (i == 0) {
                last_node = head = new Vertex<T>(nodes[i], key++);
            }
            else {
                // 正常添加
                last_node = last_node->next_vertex = 
                    new Vertex<T>(nodes[i], key++);
            }
            // map及时添加key对应的value
            map[last_node->key] = last_node->value;
        }

        // 使用邻接表建图
        for (const auto &edge : edges) {
            auto v1 = edge.first, v2 = edge.second;
            VertexType *temp_v = head;
            // 遍历顶点的集合，添加结点
            while (temp_v != nullptr) {
                if (temp_v->value == v1) {
                    temp_v->add_node(v2);
                }
                else if (temp_v->value == v2) {
                    temp_v->add_node(v1);
                }
                // 指针后移
                temp_v = temp_v->next_vertex;
            }
        }
        // 初始化完成
        initialized = true;

        return OK;
    }

    // 销毁图的函数
    status DestroyGraph() {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }
        // 释放图
        if (free_graph()) {
            key = 0;
            initialized = false;
            map.clear();
            return OK;
        }
        else {
            return ERROR;
        }
    }

    // 查找顶点的位置信息
    int LocateVertex(const int &ver_key) {
        if (!initialized) {
            std::cerr << "This graph has not been initaialized.\n";
            return -1;
        }
        // 未找到表明顶点不在此图中
        auto it = map.find(ver_key);
        if (it != map.cend()) {
            // 找到返回结点的key
            return ver_key;
        }

        return -1;
    }

    // 通过key寻找结点
    status GetVertex(T &value, const int &ver_key) {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }
        // 寻找结点值
        auto it = map.find(ver_key);
        if (it != map.cend()) {
            value = it->second;
            return OK;
        }

        return ERROR;
    }

    // 为结点赋值
    status PutVertex(const T &value, const int &ver_key) {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }
        T find_value;
        // 得到迭代器
        auto it = map.find(ver_key);
        // 如果找到了需要将所有这个结点的值更新一遍
        if (it != map.cend()) {
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
                temp_v = temp_v->next_vertex;
            }
        }
        else {
            // 没有找到，说明顶点集里没有参数给的
            return ERROR;
        }

        return OK;
    }

    // 寻找第一邻接点
    NodeType *FirstAdjacentVertex(const int &ver_key) {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }
        // 遍历寻找顶点
        auto *vertex = head;
        while (vertex != nullptr) {
            if (vertex->key == ver_key) {
                // 找到后直接返回其邻接表中第一个结点的指针即可
                return vertex->next_node;
            }
            vertex = vertex->next_vertex;
        }
        // 未找到返回空指针
        return nullptr;
    }

    // 寻找下一邻接点
    NodeType *NextAdjacentVertex(const int &ver_key, const int &node_key) {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }
        // 直接寻找第一个邻接点，重用代码
        auto *nodes = FirstAdjacentVertex(ver_key);
        auto it = map.find(ver_key);
        if (it != map.cend()) {
            // 寻找给出临界点的值
            auto node_iter = map.find(node_key);
            if (node_iter == map.cend()) {
                return nullptr;
            }
            T value = node_iter->second;
            while (nodes != nullptr) {
                // 返回下一邻接点
                if (nodes->value == value) {
                    return nodes->next;
                }
                // 指针后移
                nodes = nodes->next;
            }
        }
        // 查找失败返回空指针
        return nullptr;
    }

    // 插入顶点
    status InsertVertex(const T &value) {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }
        // 图为空的情况添加新结点为头指针
        if (head == nullptr) {
            head = new Vertex<T>(value, key++);
            // map更新值
            map[head->key] = value;

            return OK;
        }

        auto temp_v = head;
        // 寻找最后的顶点，在其后接上加入的顶点
        while (temp_v->next_vertex != nullptr) {
            temp_v = temp_v->next_vertex;
        }

        temp_v->next_vertex = new Vertex<T>(value, key++);
        // 更新map
        map[temp_v->next_vertex->key] = value;

        return OK;
    }

    // 删除顶点
    status DeleteVertex(const int &ver_key) {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }

        // 寻找顶点是否存在于当前图
        auto it = map.find(ver_key);
        if (it == map.cend()) {
            return ERROR;
        }
        // 删除map中顶点的值
        T value = it->second;
        map.erase(it);

        auto temp_v = head;
        // 删除结点有点麻烦，需要删除边和链表中的结点
        // 要删除的结点为首节点
        if (temp_v->key == ver_key) {
            head = head->next_vertex;
            freeVertex(temp_v);
        }
        else {
            // 要删除的顶点不是头结点
            while (temp_v->next_vertex != nullptr) {
                if (temp_v->next_vertex->value == value) {
                    auto t = temp_v->next_vertex;
                    temp_v->next_vertex = t->next_vertex;
                    freeVertex(t);
                }
                temp_v = temp_v->next_vertex;
            }
        }
        // 删除图里的点
        temp_v = head;
        while (temp_v != nullptr) {
            temp_v->remove_node(value);
            temp_v = temp_v->next_vertex;
        }

        return OK;
    }

    // 插入弧
    status InsertArc(const std::pair<T, T> &edge) {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }
        // 得到边的两个顶点
        auto v1 = edge.first, v2 = edge.second;

        auto temp_v = head;
        // 遍历删除
        while (temp_v != nullptr) {
            if (temp_v->value == v1) {
                temp_v->add_node(v2);
            }
            else if (temp_v->value == v2) {
                temp_v->add_node(v1);
            }
            // 指针后移
            temp_v = temp_v->next_vertex;
        }

        return OK;
    }

    // 删除弧
    status DeleteArc(const T &v1, const T &v2) {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }
        // 标记删除是否成功
        bool del = false;
        auto temp_v = head;
        while (temp_v != nullptr) {
            if (temp_v->value == v1) {
                // 配对删除
                del = temp_v->remove_node(v2);
            }
            else if (temp_v->value == v2) {
                del = temp_v->remove_node(v1);
            }
            temp_v = temp_v->next_vertex;
        }
        // 删除成功返回OK
        return del ? OK : ERROR;
    }

    // 深度遍历
    status DFSTraverse(const Visit<T> &visit) const {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }
        std::map<T, bool> visited;
        auto temp_v = head;
        if (head != nullptr) {
            // 建立map
            while (temp_v != nullptr) {
                visited[temp_v->value] = false;
                temp_v = temp_v->next_vertex;
            }
            temp_v = head;
            // 循环调用DFS，因为图不一定相连
            while (temp_v != nullptr) {
                if (!visited[temp_v->value]) {
                    visited[temp_v->value] = true;
                    DFSTraverse(temp_v, visited, visit);
                }
                temp_v = temp_v->next_vertex;
            }
        }

        return OK;
    }

    // 广度遍历
    status BFSTraverse(const Visit<T> &visit) {
        if (!initialized) {
            std::cerr << "This graph has not been initialized.\n";
            return ERROR;
        }

        std::map<T, bool> visited;
        auto temp_v = head;
        if (head != nullptr) {
            // 建立map
            while (temp_v != nullptr) {
                visited[temp_v->value] = false;
                temp_v = temp_v->next_vertex;
            }
            // temp_v设置为head
            temp_v = head;
            while (temp_v != nullptr) {
                // 循环使用BFS，避免因为图不连通导致无法遍历完全
                if (!visited[temp_v->value]) {
                    BFSTraverse(head, visited, visit);
                }
                temp_v = temp_v->next_vertex;
            }
        }

        return OK;
    }

    // 显示结点的key和value
    void display_vertex() {
        auto temp_v = head;
        while (temp_v != nullptr) {
            std::cout << "key: " << temp_v->key 
                << ", value: " << temp_v->value << "\n";
            temp_v = temp_v->next_vertex;
        }
    }

    // 显示邻接表形式的图遍历
    void display_linked_list() {
        auto temp_v = head;
        while (temp_v != nullptr) {
            auto temp_n = temp_v->next_node;
            std::cout << temp_v->value;
            while (temp_n != nullptr) {
                std::cout << "->" << temp_n->value;
                temp_n = temp_n->next;
            }
            std::cout << "\n";
            temp_v = temp_v->next_vertex;
        }
    }
    // 从文件加载图
    bool LoadGraphFromFile(const std::string &file_name) {
        std::fstream in(file_name, std::ios_base::in);
        if (in.is_open()) {
            size_t count = 0;
            T v1, v2;
            initialized = true;
            DestroyGraph();
            initialized = true;
            in >> count;
            for (size_t i = 0; i < count; i++) {
                in >> v1;
                InsertVertex(v1);
            }

            in >> count;
            for (size_t i = 0; i < count; i++) {
                in >> v1 >> v2;
                InsertArc(std::make_pair(v1, v2));
            }

            in.close();
            std::cout << "Load successfully.\n";
            return true;
        }
        else {
            return false;
        }
    }
};

// 输入结点集合
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
}

// 输入边集合
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
}

#endif // !DATASTRUCTURE_GRAPH_H
