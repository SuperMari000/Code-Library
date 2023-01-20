//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

int n, m;
vector<vector<int> > adj;
vector<int> vis;


bool dfs(int u) {
    vis[u] = 1;
    bool sycle = false;

    for (int v:adj[u]) {
        if (vis[v] == 0) {
            sycle |= dfs(v);
        }

        sycle |= (vis[v] == 1);
    }

    vis[u] = 2;
    return false;
}

int main() {
    cin >> n >> m;
    adj.resize(n);
    vis.resize(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v; // zero-based
        adj[u].push_back(v);
    }

    bool foundSycle = 0;

    for (int u = 0; u < n; ++u) {
        if (vis[u] == 0) {
            foundSycle |= dfs(u);
        }
    }

    cout << (foundSycle ? "Yes" : "No") << "\n";


    return 0;
}
