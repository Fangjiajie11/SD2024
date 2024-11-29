#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
using namespace std;

class Graph {
private:
    unordered_map<int, list<int>> adjList;

public:
    void addVertex(int vertex) {
        adjList[vertex];
    }

    void addEdge(int source, int destination) {
        adjList[source].push_back(destination);
        adjList[destination].push_back(source); // ÎÞÏòÍ¼
    }

    list<int> getNeighbors(int vertex) {
        return adjList[vertex];
    }

    void printGraph() {
        for (auto& pair : adjList) {
            cout << pair.first << " -> ";
            for (int neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

void bfs(Graph& graph, int startVertex) {
    queue<int> q;
    set<int> visited;

    q.push(startVertex);
    visited.insert(startVertex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";

        for (int neighbor : graph.getNeighbors(current)) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
}

void dfsHelper(Graph& graph, int vertex, set<int>& visited) {
    visited.insert(vertex);
    cout << vertex << " ";

    for (int neighbor : graph.getNeighbors(vertex)) {
        if (visited.find(neighbor) == visited.end()) {
            dfsHelper(graph, neighbor, visited);
        }
    }
}

void dfs(Graph& graph, int startVertex) {
    set<int> visited;
    dfsHelper(graph, startVertex, visited);
}