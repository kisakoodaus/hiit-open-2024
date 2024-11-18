#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
    // TODO: Write the checker
    auto lls = read_ints(2, 1, 1000000000000000000LL);
    int n = lls[0];
    if (n < 1 || n > 60) fail();
    end();
}
