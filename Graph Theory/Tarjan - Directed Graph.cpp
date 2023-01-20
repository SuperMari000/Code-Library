//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

const int N = 1e4 + 5, M = 1e6 + 5;

#define neigh(adj, u, e, v) for (int e = adj.head[u], v; ~e && (v = adj.to[e], 1); e = adj.nxt[e])
struct ADJ {
    int head[N], nxt[M], to[M], n, ne;

    void init(int nNodes) {
        ne = 0;
        n = nNodes;
        memset(head, -1, n * sizeof head[0]);
    }

    void addEdge(int f, int t) {
        to[ne] = t;
        nxt[ne] = head[f];
        head[f] = ne++;
    }

    void addBiEdge(int f, int t) {
        addEdge(f, t);
        addEdge(t, f);
    }

    int addNode() {
        head[n] = -1;
        return n++;
    }
} adj, Cgraph;


int vis[N], vid, stk[N], stkSz, compId[N], ncp, lw[N], dfsTime[N], curTime;

void tarjanDFS(int u) {
    vis[u] = vid;
    stk[stkSz++] = u;
    lw[u] = dfsTime[u] = curTime++;
    compId[u] = -1;

    neigh(adj, u, e, v) {
        if (vis[v] != vid) {
            tarjanDFS(v); // white
            lw[u] = min(lw[u], lw[v]);
        } else if (compId[v] == -1) { // Gray
            lw[u] = min(lw[u], lw[v]);
        }
    }

    if (lw[u] == dfsTime[u]) {
        do {
            compId[stk[--stkSz]] = ncp;
        } while (stk[stkSz] != u);

        ncp++;
    }
}

void Tarjan() {
    ++vid;
    ncp = curTime = 0;

    for (int i = 0; i < adj.n; ++i) {
        if (vis[i] != vid) {
            tarjanDFS(i);
        }
    }

    Cgraph.init(ncp);

    for (int u = 0; u < adj.n; ++u) {
        neigh(adj, u, e, v) {
            if (compId[u] == compId[v]) continue; // intera comp edge

            Cgraph.addEdge(compId[u], compId[v]);
        }
    }
}

int main() {
    return 0;
}
