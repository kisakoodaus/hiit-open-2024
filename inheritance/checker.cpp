#include "cseslib.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>

int main()
{
    int n = read_int(1, 40);
    long long maxv = (1ll << n) - 2;
    std::vector<long long> input = read_ints(n, 1, maxv);
    long long sum = std::accumulate(input.begin(), input.end(), 0ll);
    if (sum > maxv)
        fail();

    end();
}
