#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
    // TODO: Write the checker
    int n = read_int(1, 1e5);
    for (int i = 0; i < n; i++) {
        auto d = read_ints(2, 1, 6);
        if (d[0] == d[1]) fail();
    }
    end();
}
