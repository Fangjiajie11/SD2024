#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>


using namespace std;

class WGraph {
private:
    int n;  
    vector<vector<int>> graph;  
    vector<pair<int, pair<int, int>>> edges;  
    bool isUndirected;  // 图的类型标志，true 表示无向图，false 表示有向图
public:
    WGraph(int nodes, bool undirected = true) : n(nodes), isUndirected(undirected), graph(nodes, vector<int>(nodes, INT_MAX)) {}

  
    void addEdge(int u, int v, int weight) {
        graph[u][v] = weight;
        edges.push_back({ weight, {u, v} });
        if (isUndirected) {
            graph[v][u] = weight;  
        }
    }

  
    void printGraph() {
        cout << "Graph (Adjacency Matrix):" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] == INT_MAX) {
                    cout << "INF ";
                }
                else {
                    cout << graph[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    // Dijkstra算法
    void dijkstra(int start) {
        vector<int> dist(n, INT_MAX);  
        vector<int> prev(n, -1);  
        dist[start] = 0;

        vector<bool> visited(n, false);  
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 

        pq.push({ 0, start });  

        while (!pq.empty()) {
            int u = pq.top().second;  
            int d = pq.top().first;   
            pq.pop();

            if (visited[u]) continue;  

            visited[u] = true;

            
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] != INT_MAX && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    prev[v] = u;  
                    pq.push({ dist[v], v });
                }
            }
        }

       
        for (int i = 0; i < n; ++i) {
            if (dist[i] == INT_MAX) {
                cout << "点 " << i << " 不可达" << endl;
            }
            else {
                cout << "最短路径从点 " << start << " 到点 " << i << ": " << dist[i] << endl;
                cout << "路径: ";
                printPath(prev, start, i);
                cout << endl;
            }
        }
    }

    
    void printPath(vector<int>& prev, int start, int end) {
        if (end == -1) {
            cout << "无路径" << endl;
            return;
        }

        stack<int> path;
        for (int v = end; v != start; v = prev[v]) {
            path.push(v);
        }
        path.push(start);

        while (!path.empty()) {
            cout << path.top() << " ";
            path.pop();
        }
    }

    // Kruskal算法
    void kruskalMST() {
        
        sort(edges.begin(), edges.end());

        vector<int> parent(n);
        vector<int> rank(n, 0);

        
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        vector<pair<int, int>> mstEdges;  
        int mstWeight = 0;  

        
        for (auto& edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            
            int root_u = findParent(u, parent);
            int root_v = findParent(v, parent);

            
            if (root_u != root_v) {
                unionSets(u, v, parent, rank);
                mstEdges.push_back({ u, v });
                mstWeight += weight;
            }
        }

        
        cout << "最小支撑树 (Kruskal):" << endl;
        for (auto& edge : mstEdges) {
            cout << edge.first << " - " << edge.second << endl;
        }
        cout << "MST的总权重: " << mstWeight << endl;
    }

   
    int findParent(int u, vector<int>& parent) {
        if (parent[u] == u) return u;
        return parent[u] = findParent(parent[u], parent);  
    }

  
    void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
        int root_u = findParent(u, parent);
        int root_v = findParent(v, parent);

        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            }
            else if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            }
            else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }

    //最小支撑树（prim）:
    void primMST() {
        
        vector<bool> inMST(n, false);

        
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

        
        inMST[0] = true;
        for (int v = 0; v < n; ++v) {
            if (graph[0][v] != INT_MAX) {
                pq.push({ graph[0][v], {0, v} });
            }
        }

       
        vector<pair<int, int>> mstEdges;
        int mstWeight = 0;

        while (!pq.empty()) {
            auto edge = pq.top();
            pq.pop();

            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            
            if (inMST[v]) continue;

            
            inMST[v] = true;
            mstEdges.push_back({ u, v });
            mstWeight += weight;

            
            for (int i = 0; i < n; ++i) {
                if (graph[v][i] != INT_MAX && !inMST[i]) {
                    pq.push({ graph[v][i], {v, i} });
                }
            }
        }

        cout << "最小支撑树（prim）:" << endl;
        for (auto& edge : mstEdges) {
            cout << edge.first << " - " << edge.second << endl;
        }
        cout << "MST的总权重: " << mstWeight << endl;
    }

};
