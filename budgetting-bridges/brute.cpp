#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using ll = long long;

int co[200001];
int si[200001];

int id(int x) {
    while (x != co[x]) x = co[x];
    return x;
}

void merge(int a, int b) {
    a = id(a);
    b = id(b);
    if (a == b) return;
    if (si[a] < si[b]) swap(a,b);
    si[a] += si[b];
    co[b] = a;
}

ll mst(int n, vector<array<int,4>> e) {
    for (int i = 1; i <= n; i++) {
        co[i] = i;
        si[i] = 1;
    }
    sort(e.begin(),e.end());
    ll c = 0;
    for (auto u : e) {
        if (id(u[2]) == id(u[3])) {
            if (u[0] == 0) return -1;
        } else {
            merge(u[2],u[3]);
            c += u[1];
        }
    }
    return c;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<array<int,4>> e;
    map<array<int,4>,int> f;
    for (int i = 0; i < m; i++) {
        int v, w, c;
        cin >> v >> w >> c;
        e.push_back({1,c,v,w});
        f[{v,w}] = i;
    }

    ll c = mst(n,e);
    for (int i = 0; i < k; i++) {
        int b;
        cin >> b;
        vector<int> v(b);
        for (int j = 0; j < b; j++) {
            int x, y;
            cin >> x >> y;
            v[j] = f[{x,y}];
        }
        for (auto x : v) e[x][0] = 0;
        ll u = mst(n,e);
        if (u == c) cout << "YES\n";
        else cout << "NO\n";
        for (auto x : v) e[x][0] = 1;
    }
}
