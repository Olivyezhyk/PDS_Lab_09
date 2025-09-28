#include "Graph.h"
#include <queue>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

bool readGraphFromFile(const string& filePath, vector<vector<unsigned int>>& graph) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Failed to open file. Please check the path." << endl;
        return false;
    }

    unsigned int n, m;
    file >> n >> m;
    graph.assign(n, {});

    for (unsigned int i = 0; i < m; i++) {
        unsigned int u, v;
        file >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    file.close();
    return true;
}


void printGraph(const vector<vector<unsigned int>>& graph) {
    cout << "Adjacency list of the graph:" << endl;
    for (unsigned int i = 0; i < graph.size(); ++i) {
        cout << i + 1 << ": ";
        for (unsigned int neighbor : graph[i]) {
            cout << neighbor + 1 << " ";
        }
        cout << endl;
    }
}

void printQueue(const queue<int>& q) {
    queue<int> temp = q;
    cout << "[";
    bool first = true;
    while (!temp.empty()) {
        if (!first) cout << ", ";
        cout << temp.front() + 1;
        temp.pop();
        first = false;
    }
    cout << "]";
}

void bfs(int start, const vector<vector<unsigned int>>& adjList) {
    vector<bool> visited(adjList.size(), false);
    vector<int> bfsNumber(adjList.size(), -1);
    queue<int> q;
    int bfsCount = 0;

    q.push(start);
    visited[start] = true;
    bfsNumber[start] = ++bfsCount;

    cout << setw(20) << "Current vertex"
        << setw(20) << "BFS number"
        << setw(20) << "Queue" << endl;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : adjList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                bfsNumber[neighbor] = ++bfsCount;
                q.push(neighbor);
            }
        }

        cout << setw(20) << current + 1
            << setw(20) << bfsNumber[current]
            << setw(20);
        printQueue(q);
        cout << endl;
    }
}

int main() {
    string filePath;
    cout << "Enter the path to the file: ";
    getline(cin, filePath);

    vector<vector<unsigned int>> graph;

    if (!readGraphFromFile(filePath, graph)) {
        return 1;
    }

    printGraph(graph);

    unsigned int startVertex;
    cout << "Enter the starting vertex number: ";
    cin >> startVertex;

    if (startVertex < 1 || startVertex > graph.size()) {
        cerr << "Error: vertex number is out of range." << endl;
        return 1;
    }

    cout << "Graph traversal protocol:" << endl;
    bfs(startVertex - 1, graph);

    return 0;
}
