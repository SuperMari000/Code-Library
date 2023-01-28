//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

vector<int> buildPhi(int mxN) {
    vector<int> phi(mxN + 1);

    iota(phi.begin(), phi.end(), 0);

    for (int i = 2; i <= mxN; i += 1 + (i & 1)) {
        if (phi[i] == i) {
            for (int j = i; j <= mxN; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }

    return phi;
}

int main() {
    return 0;
}
