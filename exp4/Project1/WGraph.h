#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>


using namespace std;

class WGraph {
private:
    int n;  // ͼ�нڵ������
    vector<vector<int>> graph;  // �ڽӾ����ʾͼ
    vector<pair<int, pair<int, int>>> edges;  // �ߵļ��� (Ȩ��, (u, v))
    bool isUndirected;  // ͼ�����ͱ�־��true ��ʾ����ͼ��false ��ʾ����ͼ
public:
    // ���캯������ʼ��ͼ�Ĵ�С
    WGraph(int nodes, bool undirected = true) : n(nodes), isUndirected(undirected), graph(nodes, vector<int>(nodes, INT_MAX)) {}

    // ��ӱ�
    void addEdge(int u, int v, int weight) {
        graph[u][v] = weight;
        edges.push_back({ weight, {u, v} });
        // ���������ͼ������Ҫ��ӷ����
        if (isUndirected) {
            graph[v][u] = weight;  // ��������ͼ����ӷ����
        }
    }

    // ��ӡͼ���ڽӾ���
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

    // Dijkstra�㷨
    void dijkstra(int start) {
        vector<int> dist(n, INT_MAX);  // �洢���·��
        vector<int> prev(n, -1);  // �洢·���е�ǰ���ڵ�
        dist[start] = 0;

        vector<bool> visited(n, false);  // ��ǽڵ��Ƿ��Ѿ�����
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;  // ��С��

        pq.push({ 0, start });  // ����㿪ʼ

        while (!pq.empty()) {
            int u = pq.top().second;  // ��ǰ�ڵ�
            int d = pq.top().first;   // ��ǰ�ڵ�ľ���
            pq.pop();

            if (visited[u]) continue;  // ����Ѿ����ʹ�������

            visited[u] = true;

            // �����ڽӽڵ�ľ���
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] != INT_MAX && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    prev[v] = u;  // ��¼ǰ���ڵ�
                    pq.push({ dist[v], v });
                }
            }
        }

        // ������·��
        for (int i = 0; i < n; ++i) {
            if (dist[i] == INT_MAX) {
                cout << "�� " << i << " ���ɴ�" << endl;
            }
            else {
                cout << "���·���ӵ� " << start << " ���� " << i << ": " << dist[i] << endl;
                cout << "·��: ";
                printPath(prev, start, i);
                cout << endl;
            }
        }
    }

    // ͨ��ǰ���ڵ������ӡ·��
    void printPath(vector<int>& prev, int start, int end) {
        if (end == -1) {
            cout << "��·��" << endl;
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

    // Kruskal�㷨
    void kruskalMST() {
        // ���ߵ�Ȩ����������
        sort(edges.begin(), edges.end());

        vector<int> parent(n);
        vector<int> rank(n, 0);

        // ��ʼ��ÿ���ڵ�ĸ��ڵ�Ϊ�Լ�
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        vector<pair<int, int>> mstEdges;  // �洢��С�������ı�
        int mstWeight = 0;  // ��¼��С����������Ȩ��

        // �������бߣ�ѡ���γɻ��ı�
        for (auto& edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            // ����u��v�ĸ��ڵ�
            int root_u = findParent(u, parent);
            int root_v = findParent(v, parent);

            // ���u��v�ĸ��ڵ㲻��ͬ��˵�������γɻ���������С������
            if (root_u != root_v) {
                unionSets(u, v, parent, rank);
                mstEdges.push_back({ u, v });
                mstWeight += weight;
            }
        }

        
        cout << "��С֧���� (Kruskal):" << endl;
        for (auto& edge : mstEdges) {
            cout << edge.first << " - " << edge.second << endl;
        }
        cout << "MST����Ȩ��: " << mstWeight << endl;
    }

    // ���Ҹ��ڵ�
    int findParent(int u, vector<int>& parent) {
        if (parent[u] == u) return u;
        return parent[u] = findParent(parent[u], parent);  // ·��ѹ��
    }

    // �ϲ���������
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

    //��С֧������prim��:
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

        cout << "��С֧������prim��:" << endl;
        for (auto& edge : mstEdges) {
            cout << edge.first << " - " << edge.second << endl;
        }
        cout << "MST����Ȩ��: " << mstWeight << endl;
    }

};
