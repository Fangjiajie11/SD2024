#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include"Graph.h"
#include"WGraph.h"
using namespace std;
int main() {
    Graph graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);

    cout << "BFS: ";
    bfs(graph, 1);

    cout << "\nDFS: ";
    dfs(graph, 1);

    cout << endl;
    int n = 5;  // �ڵ������
    WGraph g(n,false);//����ͼ

    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 3);
    //g.printGraph();
    int start = 0;  
    g.dijkstra(start);
    cout << endl;


    WGraph g2(n, true);//����ͼ

    g2.addEdge(0, 1, 10);
    g2.addEdge(0, 4, 5);
    g2.addEdge(1, 2, 1);
    g2.addEdge(1, 4, 2);
    g2.addEdge(2, 3, 4);
    g2.addEdge(3, 4, 3);
    // ʹ��Kruskal�㷨������С������
    g2.kruskalMST();
    cout << endl;
    // ʹ��Prim�㷨������С������
    g2.primMST();  // �ӽڵ�0��ʼ
    return 0;
}