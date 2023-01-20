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

int vis[N], vid, stk[N], stkSz, isArt[N], isBridge[M], lw[N], dfsTime[N], curTime, ncp, compId[N];
int tarjanDFS(int u, int pe) {
    vis[u] = vid;
    stk[stkSz++] = u;
    lw[u] = dfsTime[u] = curTime++;
    int compSz = 1;

    neigh(adj, u, e, v) {
        if (e == pe) {
            continue;
        }

        if (vis[v] != vid) {
            compSz += tarjanDFS(v, e ^ 1);
            lw[u] = min(lw[u], lw[v]);

            if (lw[v] >= dfsTime[u] && (~pe || dfsTime[v] > dfsTime[u] + 1)) {
                isArt[u] = vid;
            }

            if (lw[v] > dfsTime[u]) {
                isBridge[e] = isBridge[e ^ 1] = vid;
            }
        } else {
            lw[u] = min(lw[u], dfsTime[v]);
        }
    }

    if (lw[u] == dfsTime[u]) {
        do{
            compId[stk[--stkSz]] = ncp;
        }while (stk[stkSz] != u);
        ncp++;
    }

    return compSz;
}

void Tarjan() {
    ++vid;
    ncp = curTime = 0;

    for (int i = 0; i < adj.n; ++i) {
        if (vis[i] != vid) {
            stkSz = 0;
            tarjanDFS(i, -1);
        }
    }

    Cgraph.init(ncp);

    for (int u = 0; u < adj.n; ++u) {
        if (compId[u] == -1) {
            continue;
        }

        neigh(adj, u, e, v) {
            if (compId[u] != compId[v]) {
                Cgraph.addEdge(compId[u], compId[v]);
            }
        }
    }
}

int main() {
    return 0;
}
