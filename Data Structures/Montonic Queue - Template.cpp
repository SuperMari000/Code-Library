//
//  main.cpp
//
#include "bits/stdc++.h"
using namespace std;

template <typename T>
struct montonicStack {
    stack<pair<T, T> > st;

    void push(const T &v) {
        if (st.empty()) {
            st.emplace(v, v);
        } else {
            st.emplace(v, ::max(v, st.top().second));
        }
    }

    void pop() {
        st.pop();
    }

    size_t size() {
        return st.size();
    }

    bool empty() {
        return st.empty();
    }

    const T& top() {
        return st.top().first;
    }

    const T& max() {
        return st.top().second;
    }
};

template <typename T>
struct montonicQueue {
    montonicStack<T> add;
    montonicStack<T> rmv;

    void push(const T &v) {
        add.push(v);
    }

    void updateRmv() {
        if (rmv.size()) {
            return;
        }

        while (add.size()) {
            rmv.push(add.top());
            add.pop();
        }
    }

    void pop() {
        updateRmv();
        rmv.pop();
    }

    size_t size() {
        return add.size() + rmv.size();
    }

    bool empty() {
        return add.empty() && rmv.empty();
    }

    const T& front() {
        updateRmv();
        return rmv.top();
    }

    const T& max() {
        if (add.empty()) {
            return rmv.max();
        }

        if (rmv.empty()) {
            return add.max();
        }

        return ::max(rmv.max(), add.max());
    }
};


int main() {
    return 0;
}
