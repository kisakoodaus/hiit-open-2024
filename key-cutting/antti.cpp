#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int d = 0, c = 0;
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while (v.size() && v.back() > x) v.pop_back();
        if (x == 0) continue;
        if (v.size() == 0 || v.back() < x) {
            v.push_back(x);
            c++;
        }
    }
    cout << c << "\n";
}
