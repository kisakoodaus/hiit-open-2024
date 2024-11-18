#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

vector<int> v[1<<18];
int e[1<<18];

int dfs(int i) {
    if (e[i]) return 0;
    e[i] = 1;
    for (int j : v[i]) {
        e[i] += dfs(j);
    }
    return e[i];
}

int main() {
    auto line = read_ints(3, 1, 200000);
    int n = line[0];
    int m = line[1];
    int kk = line[2];

    set<pair<int, int>> sm;
    set<pair<int, int>> oo;
    for (int i = 0; i < m; i++) {
        line = read_ints(3, 1, 1000000000);
        int a = line[0];
        int b = line[1];
        int c = line[2];
        if (a == b) fail();
        if (a < 1 || a > n) fail();
        if (b < 1 || b > n) fail();
        v[a].push_back(b);
        v[b].push_back(a);
        oo.insert({a, b});
        if (a > b) swap(a, b);
        sm.insert({a, b});
    }
    if ((int)sm.size() != m) fail();
    if (dfs(1) != n) fail();

    int bs = 0;
    for (int i = 0; i < kk; i++) {
        int bb = read_int(1, 200000);
        set<pair<int, int>> ss;
        for (int j = 0; j < bb; j++) {
            line = read_ints(2, 1, n);
            int a = line[0];
            int b = line[1];
            if (a == b) fail();
            if (!oo.count({a, b})) fail();
            if (a > b) swap(a, b);
            ss.insert({a, b});
        }
        bs += bb;
        if ((int)ss.size() != bb) fail();
    }
    if (bs > 200000) fail();

    end();
}
