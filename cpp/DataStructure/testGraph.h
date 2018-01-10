#ifndef DATASTRUCTURE_TESTGRAPH_H
#define DATASTRUCTURE_TESTGRAPH_H
#include "graph.h"

// 值类型定义
using ValueType = char;

void testGraph() {
    // 图
    Graph<ValueType> graph;
    // 边集合
    std::vector<std::pair<ValueType, ValueType>> edges;
    // 一条边
    std::pair<ValueType, ValueType> edge;
    // 顶点集合
    std::vector<ValueType> vertexes;
    // 单个顶点
    ValueType v1, v2;
    // 单个边顶点
    Graph<ValueType>::NodeType *node = nullptr;
    // 单个图顶点
    Graph<ValueType>::VertexType *vertex = nullptr;
    // 顶点值暂时变量
    ValueType value = '#';
    // 键值暂存变量
    int key = 0, node_key = 0;
    // 选择的操作
    int operation = -1;
    // 访问函数
    Visit<ValueType> visit = [](const auto &value) { std::cout << value << "\n"; };
    // 文件名
    std::string file_name;
    // 主循环
    while (operation != 0) {
        cls();
        std::cout << "                 Menu for Graph\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "     1.CreateGraph          2.DestroyGraph\n";
        std::cout << "     3.LocateVertex         4.GetVertex\n";
        std::cout << "     5.PutVertex            6.FirstAdjacentVertex\n";
        std::cout << "     7.NextAdjacentVertex   8.InsertVertex\n";
        std::cout << "     9.DeleteVertex         10.InsertArc\n";
        std::cout << "     11.DeleteArc           12.DFSTraverse\n";
        std::cout << "     13.BFSTraverse         14.LoadGraphFromFile\n";
        std::cout << "     15.DisplayLinkedList\n";
        std::cout << "     0.Exit\n";
        std::cout << "--------------------------------------------------\n\n";
        std::cout << "Please enter your selection: ";
        std::cin >> operation;
        switch (operation) {
        case 1:
            std::cout << "CreateGraph Function\n";
            input_vertexes(vertexes);
            input_edges(edges);
            std::cout << "End input.\n";
            if (graph.CreateGraph(vertexes, edges) == OK) {
                std::cout << "Create graph successfully.\n";
            }
            else {
                std::cout << "Create graph failed.\n";
            }
            wait();
            break;
        case 2:
            std::cout << "DeatroyGraph Function\n";
            if (graph.DestroyGraph() == OK) {
                std::cout << "Deatroy graph successfully.\n";
            }
            else {
                std::cout << "Destroy graph failed.\n";
            }
            wait();
            break;
        case 3:
            std::cout << "LocateVertex Function\n";
            graph.display_vertex();

            std::cout << "Please input key of node: ";
            std::cin >> key;
            std::cout << graph.LocateVertex(key) << "\n";
            wait();
            break;
        case 4:
            std::cout << "GetVertex Function\n";
            graph.display_vertex();
            std::cout << "PLease enter key of vertex: ";
            std::cin >> key;
            if (graph.GetVertex(value, key) == OK) {
                std::cout << "Get value: " << value << "\n";
            }
            else {
                std::cout << "Get value failed.\n";
            }
            wait();
            break;
        case 5:
            std::cout << "PutVertex Function\n";
            graph.display_vertex();
            std::cout << "PLease enter key of vertex: ";
            std::cin >> key;
            std::cout << "Pleas enter value to put: ";
            std::cin >> value;
            if (graph.PutVertex(value, key) == OK) {
                std::cout << "Put value into vertex successfully.\n";
            }
            else {
                std::cout << "Put value into vertex failed.\n";
            }
            wait();
            break;
        case 6:
            std::cout << "FirstAdjacentVertex Function\n";
            graph.display_vertex();
            std::cout << "PLease enter key of vertex: ";
            std::cin >> key;
            node = graph.FirstAdjacentVertex(key);
            if (node != nullptr) {
                std::cout << "Get vertex: " << node->value << "\n";
            }
            else {
                std::cout << "Get vertex failed.\n";
            }
            wait();
            break;
        case 7:
            std::cout << "NextAjcacentVertex Function\n";
            graph.display_vertex();
            std::cout << "PLease enter key of vertex: ";
            std::cin >> key;
            std::cout << "Please enter key of node: ";
            std::cin >> node_key;
            node = graph.NextAdjacentVertex(key, node_key);
            if (node != nullptr) {
                std::cout << "Get next adjacent vertext: "
                    << node->value << "\n";
            }
            else {
                std::cout << "Get next adjacent vertex failed.\n";
            }
            wait();
            break;
        case 8:
            std::cout << "InsertVertex Function\n";
            std::cout << "PLease enter value of vertex: ";
            std::cin >> value;
            if (graph.InsertVertex(value) == OK) {
                std::cout << "Insert vertex successfully.\n";
            }
            else {
                std::cout << "Insert vertex failed.\n";
            }
            wait();
            break;
        case 9:
            std::cout << "DeleteVertex Function\n";
            graph.display_vertex();
            std::cout << "PLease enter key of vertex: ";
            std::cin >> key;
            if (graph.DeleteVertex(key) == OK) {
                std::cout << "Delete vertex successfully.\n";
            }
            else {
                std::cout << "Delete vertex failed.\n";
            }
            wait();
            break;
        case 10:
            std::cout << "InsertVertex Function\n";
            std::cout << "PLease enter arc: ";
            std::cin >> edge.first >> edge.second;
            if (graph.InsertArc(edge) == OK) {
                std::cout << "Insert arc successfully.\n";
            }
            else {
                std::cout << "Insert arc failed.\n";
            }
            wait();
            break;
        case 11:
            std::cout << "DeleteArc Function\n";
            std::cout << "PLese enter two vertex of arc: ";
            std::cin >> v1 >> v2;
            if (graph.DeleteArc(v1, v2) == OK) {
                std::cout << "Delete arc successfully.\n";
            }
            else {
                std::cout << "Delete arc failed.\n";
            }
            wait();
            break;
        case 12:
            std::cout << "DFSTRaverse Function\n";
            if (graph.DFSTraverse(visit) == OK) {
                std::cout << "DFSTraverse successfully.\n";
            }
            else {
                std::cout << "DFSTraverse failed.\n";
            }
            wait();
            break;
        case 13:
            std::cout << "BFSTraverse Function\n";
            if (graph.BFSTraverse(visit) == OK) {
                std::cout << "BFSTraverse successfully.\n";
            }
            else {
                std::cout << "BFSTraverse failed.\n";
            }
            wait();
            break;
        case 14:
            std::cout << "Loadgraph Function\n";
            std::cout << "Please enter file name: ";
            std::cin >> file_name;
            graph.LoadGraphFromFile(file_name);
            wait();
            break;
        case 15:
            std::cout << "DisplayLinkedList Function\n";
            graph.display_linked_list();
            wait();
            break;
        case 0:
            break;
        default:
            break;
        }
    }

    std::cout << "Good Bye.\n";
}

#endif // !DATASTRUCTURE_TESTGRAPH_H
