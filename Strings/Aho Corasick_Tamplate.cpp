//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

struct AhoCorasick {
    const int Alpha = 128;
    vector<string> pattern;
    vector<int> patIdx;
    vector<vector<int> > child;
    vector<int> patId, childSz, fail, nxt;
    vector<vector<char> > childChr;
    int nodeCnt;

    AhoCorasick(vector<string> &_pattern) : pattern(_pattern) {
        patIdx.resize(_pattern.size());
        nodeCnt = 0;

        child.clear();
        childChr.clear();
        patId.clear();
        childSz.clear();
        fail.clear();
        nxt.clear();

        addNode();

        Build();
    }

    int addNode() {
        child.push_back(vector<int>(Alpha, -1));
        childChr.push_back(vector<char>(Alpha, 0));
        patId.push_back(-1);
        childSz.push_back(0);
        fail.push_back(-1);
        nxt.push_back(-1);
        return nodeCnt++;
    }

    int insert(const char *s, int idx) {
        int cur;

        for (cur = 0; *s; s++) {
            int &nxt = child[cur][*s];

            if (!~nxt) {
                nxt = addNode(), childChr[cur][childSz[cur]++] = *s;
            }

            cur = nxt;
        }

        if (!~patId[cur]) {
            patId[cur] = idx;
        }

        return patId[cur]; // if this Pattern exixt return old index
    }

    int getFailure(int f, char c) {
        while (!~child[f][c]) f = fail[f];
        f = child[f][c];
        return f;
    }

    void computeFail() {
        queue<int> Q;

        for (int i = 0; i < Alpha; i++) {
            int &c = child[0][i];

            if (~c) {
                Q.push(c), fail[c] = 0;
            } else {
                c = 0;
            }
        }

        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();

            for (int j = 0; j < childSz[cur]; j++) {
                char c =  childChr[cur][j];
                int ch = child[cur][c];
                Q.push(ch);
                fail[ch] = nxt[ch] = getFailure(fail[cur], c);
            }
        }
    }

    int NXT(int u) {
        int v = nxt[u];

        return !~v or ~patId[v] ? v : nxt[u] = NXT(v);
    }

    void Build() {
        for (int i = 0; i < pattern.size(); ++i) {
            patIdx[i] = insert(pattern[i].c_str(), i);
        }

        computeFail();
    }

    vector<vector<int> > Match(const string &str) { // for Every Pattern add index in STR (pattern -> i end in this position)
        vector<vector<int> > ret(pattern.size());

        for (int cur = 0, i = 0; i < str.size(); i++) {
            cur = getFailure(cur, str[i]);

            for (int j = cur; ~j; j = NXT(j)) {
                if (~patId[j]) {
                    ret[patId[j]].emplace_back(i);
                }
            }
        }

        return ret;
    }
};

int main() {
    vector<string> pat;
    string str;
    int q;

    cin >> str >> q;
    pat.resize(q);

    for (auto &s:pat) {
        cin >> s;
    }

    AhoCorasick aho = AhoCorasick(pat);

    auto vec = aho.Match(str);

    for (int i = 0; i < q; ++i) {
        puts((vec[aho.patIdx[i]].size()) ? "Yes" : "No");
    }

    return 0;
}
