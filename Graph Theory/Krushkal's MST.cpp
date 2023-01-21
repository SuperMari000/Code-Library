//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

struct DSU {
    vector<int> par, sz, rnk;
    int comp; //connected components

    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), comp(n) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int u) {
        if (u == par[u]) return u;
        return par[u] = find(par[u]);
    }

    bool isSame(int u, int v) {
        return find(u) == find(v);
    }

    bool join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (rnk[u] < rnk[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        rnk[u] += (rnk[u] == rnk[v]);
        comp--;
        return true;
    }
};

long long MST(int nNodes, vector<array<int, 3>> edges){
    DSU dsu(nNodes);
    sort(edges.begin(), edges.end(), [](array<int, 3> &s, array<int, 3> &f){
        return s.back() < f.back();
    });
    
    long long ans = 0;
    for(auto [u, v, cost]:edges){
        if(dsu.join(u, v)){
            ans += cost;
        }
    }
    return ans;
}



int main() {
    return 0;
}
