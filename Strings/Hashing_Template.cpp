//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

struct Hashing {
    const int Mod1 = 127657753, Mod2 = 987654319;
    const int Base1 = 137, Base2 = 277;
    int invBase1, invBase2;
    vector<pair<int, int> > Pw, invPw;
    Hashing(const int MAXN) : Pw(MAXN + 1), invPw(MAXN + 1) {
        invBase1 = Power(Base1, Mod1 - 2, Mod1);
        invBase2 = Power(Base2, Mod2 - 2, Mod2);
        PreProcess(MAXN + 1);
    }

    int Power(int n, int p, int Mod) {
        int ret = 1;

        while (p) {
            if (p & 1) {
                ret = 1ll * ret * n % Mod;
            }

            n = 1ll * n * n % Mod;
            p >>= 1;
        }
        return ret;
    }

    void PreProcess(int N) {
        Pw[0] = make_pair(1, 1);

        for (int i = 1; i < N; ++i) {
            Pw[i].first = 1LL * Pw[i - 1].first * Base1 % Mod1;
            Pw[i].second = 1LL * Pw[i - 1].second * Base2 % Mod2;
        }

        invPw[0] = make_pair(1, 1);

        for (int i = 1; i < N; ++i) {
            invPw[i].first = 1LL * invPw[i - 1].first * invBase1 % Mod1;
            invPw[i].second = 1LL * invPw[i - 1].second * invBase2 % Mod2;
        }
    }

    string str; //0-based
    vector<pair<int, int> > hash; // 1-Based
    int strSz;

    void init(string &_s) {
        strSz = (int)_s.size();
        str = _s;
        hash.clear();
        assert(strSz < Pw.size());
        build();
    }

    void build() {
        hash.push_back(make_pair(0, 0));

        for (int i = 0; i < strSz; ++i) {
            pair<int, int> p;
            p.first = (hash[i].first + 1LL * Pw[i].first * str[i] % Mod1) % Mod1;
            p.second = (hash[i].second + 1LL * Pw[i].second * str[i] % Mod2) % Mod2;
            hash.push_back(p);
        }
    }

    pair<int, int> get_hash(int l, int r) {
        if (l > r || r > strSz || l < 1) {
            return make_pair(-1, -1);
        }

        pair<int, int> p;
        p.first = 1LL * (hash[r].first - hash[l - 1].first + Mod1) * invPw[l - 1].first % Mod1;
        p.second = 1LL * (hash[r].second - hash[l - 1].second + Mod2) * invPw[l - 1].second % Mod2;
        return p;
    }

    pair<int, int> get_hash() {
        return get_hash(1, strSz);
    }
};



int main() {
    return 0;
}
