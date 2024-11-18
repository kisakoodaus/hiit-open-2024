#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin>>s;
    int u, l, d, r;
    u = l = d = r = 0;
    for (char c : s) {
        if (c == 'U') u++;
        if (c == 'L') l++;
        if (c == 'D') d++;
        if (c == 'R') r++;
    }
    cout<<(min(u, d) + min(l, r))<<endl;
}
