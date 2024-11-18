#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;
    int cl = 0, cr = 0, cu = 0, cd = 0;
    for (auto x : s) {
        if (x == 'L') cl++;
        if (x == 'R') cr++;
        if (x == 'U') cu++;
        if (x == 'D') cd++;
    }
    cout << min(cl,cr)+min(cu,cd) << "\n";
}
