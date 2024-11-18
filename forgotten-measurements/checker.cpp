#include "cseslib.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>

int main()
{
    string ss = read_str(1, 1000000, "ULDR");
    for (int i = 1; i < (int)ss.length(); i++) {
        if ((ss[i] == 'U' || ss[i] == 'D') == (ss[i - 1] == 'U' || ss[i - 1] == 'D')) fail();
    }
    end();
}
