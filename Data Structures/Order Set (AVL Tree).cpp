//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

// Avl Tree
typedef int TN;
enum DIR {L, R};

struct Node {
    TN val;
    int freq, sz, hi;
    Node *chld[2];

    Node() : val(0), freq(0), sz(0), hi(0) {
        chld[L] = chld[R] = nullptr;
    }

    Node(TN v, Node *lt = nullptr, Node *rt = nullptr) {
        val = v;
        sz = freq = 1;
        hi = 1;
        chld[L] = lt;
        chld[R] = rt;
    }

    void Push_Up() {
        sz = freq;
        hi = 0;

        for (int i = 0; i < 2; ++i) {
            sz += (chld[i] ? chld[i]->sz : 0);
            hi = max(hi, chld[i] ? chld[i]->hi : 0);
        }

        ++hi;
    }

    int Balance_Factor() {
        return (chld[R] ? chld[R]->hi : 0) - (chld[L] ? chld[L]->hi : 0);
    }
};


struct AvlTree {
    Node *root;
    AvlTree() : root(nullptr) {
    }

    ~AvlTree() {
        Clear(root);
    }

    void Clear(Node *&root) {
        if (root == nullptr) {
            return;
        }

        Clear(root->chld[L]);
        Clear(root->chld[R]);
        delete root;
    }

/*

     p
    / \
   q   c  dir=1
   / \
   a   b

      q
     / \
    a   p
       / \
      b  c
 */

    void SetChild(Node *&par, Node *ch, int dir) {
        par->chld[dir] = ch;
        par->Push_Up();
    }

    void Rotate(Node *&p, int dir) {
        Node *q = p->chld[!dir];

        SetChild(p, q->chld[dir], !dir);
        SetChild(q, p, dir);
        p = q;
    }

    void Balance(Node *&root) {
        int curBF = root->Balance_Factor();

        if (curBF == 2) { // Left
            if (root->chld[R]->Balance_Factor() == -1) {
                Rotate(root->chld[R], R);
            }

            Rotate(root, L);
        }

        if (curBF == -2) { // Right
            if (root->chld[L]->Balance_Factor() == 1) {
                Rotate(root->chld[L], L);
            }

            Rotate(root, R);
        }
    }

    Node * MinMaxNode(Node *root, int dir) {
        if (root == nullptr) {
            return root;
        }

        while (root->chld[dir] != nullptr)
            root = root->chld[dir];
        return root;
    }

    void Insert(Node *&root, TN v) {
        if (root == nullptr) {
            root = new Node(v);
            return;
        }

        if (v == root->val) {
            root->freq++;
            root->sz++;
            return;
        }

        if (v > root->val) {
            Insert(root->chld[R], v);
        } else {
            Insert(root->chld[L], v);
        }

        Balance(root);
        root->Push_Up();
    }

    void Erase(Node *&root, TN v) {
        if (root == nullptr) {
            return;
        }

        if (v == root->val) {
            if (root->freq > 1) {
                root->freq--;
                root->sz--;
                return;
            }

            if (root->chld[L] == nullptr) {
                Node *temp = root->chld[R];
                delete root;
                root = temp;
                return;
            }

            if (root->chld[R] == nullptr) {
                Node *temp = root->chld[L];
                delete root;
                root = temp;
                return;
            }

            int curbf = root->Balance_Factor();
            Rotate(root, (curbf <= 0));
        }

        if (v > root->val) {
            Erase(root->chld[R], v);
        } else {
            Erase(root->chld[L], v);
        }

        Balance(root);
        root->Push_Up();
    }

    int Count(Node *root, TN v) {
        if (root == nullptr) {
            return 0;
        }

        if (v < root->val) {
            return Count(root->chld[L], v);
        }

        if (v > root->val) {
            return Count(root->chld[R], v);
        }

        return root->freq;
    }

    int Lower_Bound(Node *root, TN v) {
        if (root == nullptr) {
            return 0;
        }

        if (v < root->val) {
            return Lower_Bound(root->chld[L], v);
        }

        int lefsz = root->chld[L] ? root->chld[L]->sz : 0;

        if (v == root->val) {
            return lefsz;
        }

        return lefsz + root->freq + Lower_Bound(root->chld[R], v);
    }

    TN GetByIndex(Node *root, int idx) {
        if (root->sz <= idx) { // Ivalid Case
            return -1;
        }

        int lefsz = root->chld[L] ? root->chld[L]->sz : 0;

        if (idx < lefsz) {
            return GetByIndex(root->chld[L], idx);
        }

        lefsz += root->freq;

        if (idx >= lefsz) {
            return GetByIndex(root->chld[R], idx - lefsz);
        }

        return root->val;
    }

    void print(Node *rt, int dpth = 0) {
        if (rt == nullptr) {
            return;
        }

        print(rt->chld[L], dpth + 1);
        printf("%s%2d,%2d,%2d\n", string(dpth * 5, ' ').c_str(), rt->val, rt->sz, rt->hi);
        print(rt->chld[R], dpth + 1);
    }

    /* Using Function */

    void Insert(TN v) {
        Insert(root, v);
    }

    void Erase(TN v) {
        Erase(root, v);
    }

    int Count(TN v) {
        return Count(root, v);
    }

    TN operator [](int idx) { // Zero-Based
        if (idx >= 0 && idx < Size()) {
            return GetByIndex(root, idx);
        }

        puts("Invalid");
        return -1;
    }

    int Lower_Bound(TN v) { // Zero-Based
        return Lower_Bound(root, v);
    }

    int Upper_Bound(TN v) { // Zero-Based
        return Lower_Bound(root, v + 1);
    }

    int Size() {
        return root ? root->sz : 0;
    }

    TN Min() {
        if (!Size()) {
            puts("Empty Tree\n");
        }

        return MinMaxNode(root, L)->val;
    }

    TN Max() {
        if (!Size()) {
            cout << "Empty Tree\n";
        }

        return MinMaxNode(root, R)->val;
    }
};


int main() {
    return 0;
}
