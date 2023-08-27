//
//  main.cpp
//
// #pragma GCC optimize ("O3")
#include "bits/stdc++.h"
using namespace std;

const int N = 4e3 + 1;
int n, k;

int arr[N][N], pre[N][N];
int dp[2][N], bestI[2][N];


void preProcess() {
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            arr[i][j] += arr[i][j - 1];
        }
    }

    for (int l = 0; l < n; ++l) {
        for (int r = l + 1; r < n; ++r) {
            pre[l][r] += pre[l][r - 1];
            pre[l][r] += (arr[r][r] - (l - 1 >= 0 ? arr[r][l - 1] : 0));
        }
    }
}

int solve() {
    fill(dp[0], dp[0] + n, 1e9);
    bestI[0][n] = bestI[1][n] = n - 1;

    for (int lvl = 1; lvl <= k; ++lvl) {
        int cur = lvl & 1;
        int prv = cur ^ 1;

        for (int r = n - 1; r >= lvl - 1; --r) {
            for (int l = bestI[prv][r]; l <= bestI[cur][r + 1]; ++l) {
                int curValue = pre[l][r];

                if (l == 0) {
                    dp[cur][r] = curValue;
                    bestI[cur][r] = l;
                    continue;
                }

                if (dp[prv][l - 1] + curValue <= dp[cur][r]) {
                    dp[cur][r] = dp[prv][l - 1] + curValue;
                    bestI[cur][r] = l;
                }
            }
        }
    }

    return dp[k & 1][n - 1];
}

inline int readInt(int &x) {
    char c, r = 0;

    x = 0;

    for (;;) {
        c = getchar();

        if ((c < 0) && (!r)) {
            return (0);
        }

        if ((c >= '0') && (c <= '9')) {
            x = x * 10 + c - '0', r = 1;
        } else if (r) {
            break;
        }
    }

    return x;
}

int main() {
    readInt(n);
    readInt(k);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            readInt(arr[i][j]);
        }
    }

    preProcess();

    printf("%d", solve());

    return 0;
}
