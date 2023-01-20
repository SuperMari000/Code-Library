//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

struct LCA {
    typedef pair<int, int> Pii;

    struct SparseTable {
        vector<vector<Pii> > spT;
        vector<int> LOG;
        int len;

        void init(vector<Pii> &tour) {
            len = (int)tour.size();

            LOG = vector<int>(len + 1, 0);

            for (int i = 2; i <= len; ++i) {
                LOG[i] += LOG[i - 1] + !(i & (i - 1));
            }

            build(tour);
        }

        void build(vector<Pii> &tour) {
            if (tour.empty()) {
                return;
            }

            int K = LOG[len];
            spT = vector<vector<Pii> >(K + 1, vector<Pii> (len));

            spT[0] = tour;

            for (int lvl = 1; lvl <= K; ++lvl) {
                for (int i = 0; i + (1 << lvl) <= len; ++i) {
                    spT[lvl][i] = min(spT[lvl - 1][i],
                                      spT[lvl - 1][i + (1 << (lvl - 1))]);
                }
            }
        }

        Pii query(int l, int r) {
            int lg = LOG[r - l + 1];

            return min(spT[lg][l], spT[lg][r - (1 << lg) + 1]);
        }
    } SP;

    vector<vector<int> > adj;
    vector<int> depth, firstIn;
    vector<Pii> tour;
    int root, n;
    LCA(const vector<vector<int> > &adj_, const int &root_) : adj(adj_), root(root_) {
        n = (int)adj.size();
        depth = firstIn = vector<int>(n, -1);

        dfs(root, -1, 0);
        SP.init(tour);
    }

    void dfs(int u, int p, int d) {
        depth[u] = d;
        firstIn[u] = (int)tour.size();
        tour.push_back(make_pair(depth[u], u));

        for (int v:adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
                tour.push_back(make_pair(depth[u], u));
            }
        }
    }

    int get_LCA(int u, int v) {
        if (firstIn[u] > firstIn[v]) {
            swap(u, v);
        }

        return SP.query(firstIn[u], firstIn[v]).second;
    }

    int get_distance(int u, int v) {
        int lca = get_LCA(u, v);

        return depth[u] + depth[v] - (depth[lca] << 1);
    }

    bool is_ancestor(int par, int u) {
        return par == get_LCA(par, u);
    }
};

int main() {
    return 0;
}
