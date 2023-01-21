//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

struct Manachar {
    string s;
    vector<int> mxPld;
    int n;

    Manachar(string &_str) {
        n = (int)_str.size();
        convert(_str);
        build();
    }

    void convert(string &str) {
        s = "#";

        for (char c:str) {
            s += c;
            s += '#';
        }

        s = "$" + s + "*";
    }

    void build() {
        int sz = (int)s.size();

        mxPld = vector<int>(sz, 0);
        int center = 0;

        for (int i = 1; i < sz; ++i) {
            int mirrorI = center - (i - center);
            int right = center + mxPld[center];

            int cur = 0;

            if (right > i) {
                cur = min(mxPld[mirrorI], right - i);
            }

            while (s[i + cur + 1] == s[i - cur - 1]) ++cur;

            mxPld[i] = cur;

            if (i + cur > right) {
                center = i;
            }
        }
    }

    int get_maxPld(int idx) { // 0-based
        if (idx < 0 || idx >= n) {
            return 0;
        }

        int pos = (idx + 1) << 1;
        return max(mxPld[pos - 1], mxPld[pos]);
    }
};

int main() {
    return 0;
}
