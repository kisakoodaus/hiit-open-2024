#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    int n;
    ll k;
    cin >> n >> k;

    vector<ll> v;
    v.push_back(k);
    for (int i = 1; i <= n-1; i++) {
        vector<ll> u;
        u.push_back(v[0]/2);
        for (auto x : v) u.push_back(x-u.back());
        v = u;
    }

    bool fail = false;
    for (auto x : v) if (x <= 0) fail = true;

    if (fail) {
        cout << "The truth is out there\n";
    } else {
        for (auto x : v) cout << x << " ";
        cout << "\n";
    }
}
