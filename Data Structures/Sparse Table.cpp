//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

struct SparseTable {
    vector<vector<int> > sp;
    vector<int> LOG;
    vector<int> arr;
    int n;
    SparseTable(vector<int> &_arr) : arr(_arr) {
        n = (int)_arr.size();

        LOG[0] = LOG[1] = 0;

        for (int i = 2; i < n + 1; ++i) {
            LOG[i] += LOG[i - 1] + !(i & (i - 1));
        }

        int LG = LOG[n];
        vector<vector<int> > sp(LG + 1, vector<int>(n));
        LOG = vector<int>(n + 1);

        build();
    }

    int f(int lfV, int rtV) {
        return max(lfV, rtV);
    }

    void build() { // O( n log(n) )
        sp[0] = arr;

        for (int j = 1; j <= LOG[n]; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                sp[i][j] = f(sp[i][j - 1], sp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int Query1(int l, int r) { // O(1)
        int len = r - l + 1;
        int lg = LOG[len];

        return f(sp[l][lg], sp[r - (1 << lg) + 1][lg]);
    }

    int Query2(int l, int r) { // O(Log)
        int lg = LOG[n];
        int ans = 0;

        for (int j = lg; ~j; --j) {
            if ((1 << j) <= (r - l + 1)) {
                ans = f(ans, sp[l][j]);
                l += (1 << j);
            }
        }

        return ans;
    }
};



int main() {
    return 0;
}
