#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

int n;
ll x[40];
ll s[40];
int w[40];

vector<ll> vv;

#define D 12

void pre(int k, ll d) {
    if (k == n) {
        vv.push_back(d);
        return;
    }
    pre(k+1, d);
    pre(k+1, d+x[k]);
    pre(k+1, d-x[k]);
}

void go(int k, ll d, bool f) {
    if (n-k == D && !binary_search(vv.begin(), vv.end(), d)) return;
    if (k == n) {
        if (d == 0 && f) {
            for (int i = 0; i < n; i++) {
                if (w[i] == 1) cout << x[i] << " ";
            }
            cout << "\n";
            for (int i = 0; i < n; i++) {
                if (w[i] == 2) cout << x[i] << " ";
            }
            cout << "\n";
            exit(0);
        }
        return;
    }
    if (abs(d) > s[k]) return;
    w[k] = 0;
    go(k+1, d, f);
    w[k] = 1;
    go(k+1, d+x[k], 1);
    w[k] = 2;
    if (f) go(k+1, d-x[k], 1);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i];

    sort(x, x+n);
    reverse(x, x+n);
    s[n-1] = x[n-1];
    for (int i = n-2; i >= 0; i--) s[i] = s[i+1]+x[i];

    if (n >= D) pre(n-D, 0);
    sort(vv.begin(),vv.end());

    go(0, 0, 0);
}
