#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool isClique(vector<vector<int>>& graph, vector<int>& nodes) {
    int n = nodes.size();
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (!graph[nodes[i]][nodes[j]]) {
                return false;
            }
        }
    }
    return true;
}

int maxCliqueSize(vector<vector<int>>& graph, int n) {
    int maxClique = 1;
    for (int i = 0; i < (1<<n); i++) {
        vector<int> nodes;
        for (int j = 0; j < n; j++) {
            if (i & (1<<j)) {
                nodes.push_back(j);
            }
        }
        if (isClique(graph, nodes)) {
            maxClique = max(maxClique, (int)nodes.size());
        }
    }
    return maxClique;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }

    auto start = high_resolution_clock::now();
    int maxClique = maxCliqueSize(graph, n);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Maximum clique size: " << maxClique << endl;
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    return 0;
}
