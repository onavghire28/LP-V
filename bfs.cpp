#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V = 0) {
        this->V = V;
        adj.resize(V);
    }

    void createGraph() {
        cout << "Enter number of vertices: ";
        cin >> V;

        adj.clear();
        adj.resize(V);

        int E;
        cout << "Enter number of edges: ";
        cin >> E;

        cout << "Enter edges (u v):\n";
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u); // undirected graph
        }
    }

    void displayGraph() {
        if (V == 0) {
            cout << "Graph not created yet!\n";
            return;
        }

        cout << "\nGraph (Adjacency List):\n";
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int j : adj[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
    }

    void parallelBFS(int start) {
        if (V == 0) {
            cout << "Create graph first!\n";
            return;
        }

        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nParallel BFS Traversal: ";

        while (!q.empty()) {
            int size = q.size();

            #pragma omp parallel for
            for (int i = 0; i < size; i++) {
                int node = -1;

                #pragma omp critical
                {
                    if (!q.empty()) {
                        node = q.front();
                        q.pop();
                        cout << node << " ";
                    }
                }

                if (node != -1) {
                    for (int neighbor : adj[node]) {
                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                q.push(neighbor);
                            }
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    void parallelDFSUtil(int node, vector<bool> &visited) {
        bool alreadyVisited = false;

        #pragma omp critical
        {
            if (visited[node]) {
                alreadyVisited = true;
            } else {
                visited[node] = true;
                cout << node << " ";
            }
        }

        if (alreadyVisited) return;

        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); i++) {
            int neighbor = adj[node][i];

            if (!visited[neighbor]) {
                parallelDFSUtil(neighbor, visited);
            }
        }
    }

    void parallelDFS(int start) {
        if (V == 0) {
            cout << "Create graph first!\n";
            return;
        }

        vector<bool> visited(V, false);
        cout << "\nParallel DFS Traversal: ";
        parallelDFSUtil(start, visited);
        cout << endl;
    }
};

int main() {
    Graph g;
    int choice, start;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Create Graph\n";
        cout << "2. Display Graph\n";
        cout << "3. Parallel BFS\n";
        cout << "4. Parallel DFS\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            g.createGraph();
            break;

        case 2:
            g.displayGraph();
            break;

        case 3:
            cout << "Enter starting vertex: ";
            cin >> start;
            g.parallelBFS(start);
            break;

        case 4:
            cout << "Enter starting vertex: ";
            cin >> start;
            g.parallelDFS(start);
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}