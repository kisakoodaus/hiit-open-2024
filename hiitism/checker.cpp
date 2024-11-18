#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
    auto line = read_ints(2, 1, 1000);
    for (int i = 0; i < line[0]; i++) {
        read_str(line[1], line[1], ".HIT");
    }
    end();
}
