//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

vector<int> linearSieve(int mxN) {
    if (mxN < 2) {
        return vector<int>();
    }

    vector<int> isComp((mxN + 1) / 2 + 1);
    vector<int> primes = { 2 };

    for (int i = 3; i <= mxN; i += 2) {
        int &x = isComp[i >> 1];

        if (!x) {
            primes.push_back(i);
            x = i;
        }

        for (int j = 1; primes[j] <= mxN / i; j++) {
            isComp[(i * primes[j]) >> 1] = primes[j];

            if (primes[j] >= x) {
                break;
            }
        }
    }

    return primes;
}

vector<int> sieve(int mxN) {
    if (mxN < 2) {
        return vector<int>();
    }

    vector<bool> isComp(mxN + 1);
    vector<int> primes = { 2 };

    for (int i = 3; i <= mxN; i += 2) {
        if (isComp[i]) {
            continue;
        }

        primes.push_back(i);

        for (long long j = 1LL * i * i; j <= mxN; j += i + i) {
            isComp[j] = true;
        }
    }

    return primes;
}

int main() {
    return 0;
}
