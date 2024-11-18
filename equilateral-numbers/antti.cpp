#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

vector<ll> v;

int main() {
    ll n;
    cin >> n;

    for (ll a = 1; a <= 2e6; a++) {
        ll e = a*(a+1)/2;
        if (e == n) {
            cout << "1\n";
            return 0;
        }
        v.push_back(e);
    }

    int a = 0;
    int b = v.size()-1;
    while (a <= b) {
        while (v[a]+v[b] > n && b > a) b--;
        if (v[a]+v[b] == n) {
            cout << "2\n";
            return 0;
        }
        a++;
    }

    cout << "3\n"; // why is this correct??
}
