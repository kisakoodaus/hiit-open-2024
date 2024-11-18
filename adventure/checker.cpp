#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
    int n = read_int();
    read_space();
    int m = read_int();
    read_newline();
    if (n < 3 || n > 1000)
        fail();
    if (m < n || m > 1000)
        fail();

    std::set<std::pair<int, int>> edges;

    for (int i = 0; i < m; i++)
    {
        int a = read_int();
        read_space();
        int b = read_int();
        read_space();
        int colcount = read_int();
        std::set<int> cols;
        for (int j = 0; j < colcount; j++)
        {
            read_space();
            int col = read_int();
            if (col < 1 || col > 64)
                fail();
            if (!cols.insert(col).second)
                fail();
        }
        read_newline();

        if (a < 1 || a > n)
            fail();
        if (b < 1 || b > n)
            fail();
        if (a == b)
            fail();
        if (colcount < 1 || colcount > 64)
            fail();
        // Make sure that the graph is simple
        if (b < a)
            std::swap(a, b);
        if (!edges.insert({a, b}).second)
            fail();
    }

    end();
}
