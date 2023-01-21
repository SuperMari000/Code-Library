//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;


struct LCA {
    int LG, root, n;
    vector<vector<int> > adj;
    vector<int> depth;
    vector<vector<int> > spT;
    LCA(const vector<vector<int> > &adj_, const int &root_) : adj(adj_), root(root_) {
        n = (int)adj.size();
        depth = vector<int>(n, -1);

        LG = log2(n);
        spT = vector<vector<int> >(LG + 1, vector<int>(n, -1));

        dfs(root, -1, 0);
    }

    void dfs(int u, int p, int d) {
        depth[u] = d;
        spT[0][u] = p;

        for (int lvl = 1; lvl <= LG; ++lvl) {
            if (~spT[lvl - 1][u]) {
                spT[lvl][u] = spT[lvl - 1][spT[lvl - 1][u]];
            }
        }

        for (int v:adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
            }
        }
    }

    int get_LCA(int u, int v) {
        if (depth[u] > depth[v]) {
            swap(u, v);
        }

        for (int lvl = LG; ~lvl; --lvl) {
            if (~spT[lvl][v] && depth[spT[lvl][v]] >= depth[u]) {
                v = spT[lvl][v];
            }
        }

        if (u == v) {
            return u;
        }

        for (int lvl = LG; ~lvl; --lvl) {
            if (spT[lvl][u] != spT[lvl][v]) {
                u = spT[lvl][u];
                v = spT[lvl][v];
            }
        }

        return spT[0][u];
    }

    int get_distance(int u, int v) {
        int lca = get_LCA(u, v);

        return depth[u] + depth[v] - (depth[lca] << 1);
    }

    int kth_ancestor(int u, int k) { // 0th node is u
        assert(k <= depth[u]);

        for (int lvl = 0; lvl <= LG; lvl++) {
            if (k & (1 << lvl)) {
                u = spT[lvl][u];
            }
        }

        return u;
    }

    //kth node from u to v, 0th node is u
    int kth_path(int u, int v, int k) {
        int lca = get_LCA(u, v);
        int dist = depth[u] + depth[v] - (depth[lca] << 1);

        assert(k <= dist);

        if (depth[lca] + k <= depth[u]) {
            return kth_ancestor(u, k);
        }

        return kth_ancestor(v, dist - k);
    }

    bool is_ancestor(int par, int u) {
        return par == get_LCA(par, u);
    }
};


int main() {
    return 0;
}
