//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 5;
typedef int vTyp;
extern struct Node nodes[N];
enum Dir {L, R};

struct Node {
    vTyp val;
    int sz, freq;
    int chld[2], par;

    Node() {
        val = 0;
        sz = freq = 0;
        chld[L] = chld[R] = par = 0;
    }

    Node(vTyp v) {
        val = v;
        sz = freq = 1;
        chld[L] = chld[R] = par = 0;
    }

    void Push_Up() {
        sz = freq;
        for (int &i:chld) {
            sz += nodes[i].sz;
        }
    }
} nodes[N];

struct SplayTree {
    int root, freeList[N], freeListSz, nxtNodeId;
    void init() {
        root = 0;
        nxtNodeId = 1;
        freeListSz = 0;
    }

    inline int GetFreeNode() { // New Node
        if (freeListSz) {
            return freeList[--freeListSz];
        }

        return nxtNodeId++;
    }

    inline void MakeFreeNode(int nodeId) { // Delete Node
        freeList[freeListSz++] = nodeId;
    }

    inline Dir GetDir(int p, int ch) {
        return (Dir)(nodes[p].chld[R] == ch);
    }

    inline void SetChild(int p, int ch, Dir d) {
        if (ch) {
            nodes[ch].par = p;
        }

        if (p) {
            nodes[p].chld[d] = ch;
            nodes[p].Push_Up();
        }
    }

/*
 *         gp
 *         |
 *         |
 *         p
 *        / \d
 *       a  q
 *         / \
 *        b   c
 */
    inline void Rotate(int p, Dir d) {
        int gp = nodes[p].par;
        int q = nodes[p].chld[d];

        SetChild(p, nodes[q].chld[!d], d);
        SetChild(q, p, (Dir)!d);
        SetChild(gp, q, GetDir(gp, p));
    }

/*
 *         gp
 *         |
 *         |
 *         q
 *        / \
 *       p   c
 *      / \
 *     a   b
 */

    inline void Splay(int nodeId, int &root) { // nodeId -> Make This Node Root
        while (nodes[nodeId].par) {
            int p = nodes[nodeId].par;
            int gp = nodes[p].par;
            Dir pDir = GetDir(p, nodeId);
            Dir gpDir = GetDir(gp, p);

            if (!gp) { // Zig
                Rotate(p, pDir);
            } else if (pDir == gpDir) { // Zig - Zig
                Rotate(gp, gpDir);
                Rotate(p, pDir);
            } else { // Zig - Zag
                Rotate(p, pDir);
                Rotate(gp, gpDir);
            }
        }

        root = nodeId;
    }

    inline void GetNode(vTyp v, int &root) {
        int nodeId = root;

        while (v != nodes[nodeId].val) {
            Dir dir = (Dir)(v > nodes[nodeId].val);

            if (!nodes[nodeId].chld[dir]) {
                break;
            }

            nodeId = nodes[nodeId].chld[dir];
        }

        Splay(nodeId, root);
    }

    inline int MinMaxNodeId(int root, Dir dir) {
        if (!root) {
            return root;
        }

        while (nodes[root].chld[dir])
            root = nodes[root].chld[dir];
        return root;
    }

    inline void Insert(vTyp v, int &root) {
        if (!root) {
            root = GetFreeNode();
            nodes[root] = Node(v);
            return;
        }

        GetNode(v, root);

        if (nodes[root].val == v) {
            nodes[root].freq++;
            nodes[root].sz++;
        } else {
            int id = GetFreeNode();
            nodes[id] = Node(v);

            Dir dir = (Dir)(v > nodes[root].val);
            SetChild(id, nodes[root].chld[dir], dir);
            SetChild(root, 0, dir);
            SetChild(id, root, (Dir)!dir);
            root = id;
        }
    }

    inline void Erase(vTyp v, int &root) {
        GetNode(v, root);

        if (nodes[root].val != v) {
            return;
        }

        if (nodes[root].freq > 1) {
            nodes[root].freq--;
            nodes[root].sz--;
        } else {
            int lt = nodes[root].chld[L];
            int rt = nodes[root].chld[R];
            SetChild(0, lt, L);
            SetChild(0, rt, R);
            MakeFreeNode(root);

            if (lt == 0) {
                root = rt;
                return;
            }

            if (rt == 0) {
                root = lt;
                return;
            }

            int minRtId = MinMaxNodeId(rt, L);
            Splay(minRtId, rt);
            SetChild(rt, lt, L);
            root = rt;
        }
    }

    inline int Count(vTyp v, int &root) {
        GetNode(v, root);

        if (root && nodes[root].val == v) {
            return nodes[root].freq;
        }

        return 0;
    }

    inline int Lower_Bound(vTyp v, int &root) {
        if (!root) {
            return 0;
        }

        GetNode(v, root);
        int lfsz = nodes[nodes[root].chld[L]].sz;

        if (nodes[root].val >= v) {
            return lfsz;
        }

        return lfsz + nodes[root].freq;
    }

    inline vTyp GetByIndex(int idx, int &root) {
        if (idx >= nodes[root].sz) { // Invalid Case
            return -1;
        }

        int nodeId = root;
        vTyp ret = 0;

        while (true) {
            int lfsz = nodes[nodes[nodeId].chld[L]].sz;

            if (idx < lfsz) {
                nodeId = nodes[nodeId].chld[L];
                continue;
            }

            lfsz += nodes[nodeId].freq;

            if (idx >= lfsz) {
                idx -= lfsz;
                nodeId = nodes[nodeId].chld[R];
                continue;
            }

            ret = nodes[nodeId].val;
            break;
        }
        Splay(nodeId, root);
        return ret;
    }

    void print(int rt, int dpth = 0) {
        if (!rt) {
            return;
        }

        print(nodes[rt].chld[L], dpth + 1);
        printf("%s%2d,%2d\n", string(dpth * 4, ' ').c_str(), nodes[rt].val, nodes[rt].sz);
        print(nodes[rt].chld[R], dpth + 1);
    }

    /* Using Function */

    inline void Insert(vTyp v) {
        Insert(v, root);
    }

    inline void Erase(vTyp v) {
        Erase(v, root);
    }

    inline int Count(vTyp v) {
        return Count(v, root);
    }

    inline vTyp operator [](int idx) { // Zero-Based
        if (idx >= 0 && idx < Size()) {
            return GetByIndex(idx, root);
        }

        //puts("Invalid");
        return -1;
    }

    inline int Lower_Bound(vTyp v) { // Zero-Based
        return Lower_Bound(v, root);
    }

    inline int Upper_Bound(vTyp v) { // Zero-Based
        return Lower_Bound(v + 1, root);
    }

    inline int Size() {
        return nodes[root].sz;
    }
} SP;


int main() {
    return 0;
}
