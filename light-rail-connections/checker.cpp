#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
    auto line = read_ints(2, 0, 1e4);
    int n = line[0];
    int m = line[1];
    if (n == 0 || n > 1000) fail();
    if (m < 0 || m > 10000) fail();
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        auto edge = read_ints(2, 1, n);
        int x = edge[0];
        int y = edge[1];
        if (edges.count({x,y}) || edges.count({y,x})) fail();
        edges.insert({x,y});
    }
    end();
}
