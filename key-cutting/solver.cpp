#include <iostream>
#include <set>

using namespace std;

#define N (1<<17)

set<pair<int, int>> ind;
int m[2 * N];

void init(int k, int x) {
    k += N;
    m[k] = x;
    for (k /= 2; k >= 1; k /= 2) {
        m[k] = min(m[2 * k], m[2 * k + 1]);
    }
}

int low(int a, int b) {
    a += N; b += N;
    int s = 1000000001;
    while (a <= b) {
        if (a % 2 == 1) s = min(s, m[a++]);
        if (b % 2 == 0) s = min(s, m[b--]);
        a /= 2; b /= 2;
    }
    return s;
}

int solve(int l, int r) {
    if (r < l) return 0;
    int t = low(l, r);
    int ans = t > 0;
    auto p = ind.lower_bound({t, l});
    int li = l;
    while (p != ind.end() && p->second <= r && p->first == t) {
        if (li != p->second) {
            ans += solve(li, p->second - 1);
            li = p->second + 1;
        } else {
            li = p->second + 1;
        }
        ++p;
    }
    if (li <= r) ans += solve(li, r);
    return ans;
}

int main() {
    int n;
    cin>>n;
    int v[n];
    for (int i = 0; i < n; i++) {
        int x;
        cin>>x;
        init(i, x);
        ind.insert({x, i});
    }
    cout<<solve(0, n - 1)<<endl;
}
