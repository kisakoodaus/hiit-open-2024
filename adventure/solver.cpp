#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long;

int n, m;

vector<pair<int,ll>> v[111111];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        ll mask = 0;
        while (c-->0) {
            int d;
            cin>>d;
            d--;
            mask |= 1ll << d;
        }
        v[a].push_back({b,mask});
        v[b].push_back({a,mask});
    }
    priority_queue<pair<pair<int,ll>,vector<int>>> q;
    for (int i = 1; i <= n; i++) {
        q.push({{0,0},{i}});
    }
    ll steps=0;
    while (true) {
        steps++;
        auto x = q.top(); q.pop();
        int d = -x.first.first;
        ll f = x.first.second;
        vector<int> p = x.second;
        int k = p.size();
        if (k > 1 && p[0] == p[k-1]) {
            cerr<<"Using "<<d<<" colors, "<<steps<<" steps\n";
            for (int i = 0; i < k-1; i++) {
                cout << p[i] << " ";
            }
            cout << "\n";
            break;
        }
        int a = p[k-1];
        int e = k > 1 ? p[k-2] : 0;
        for (auto u : v[a]) {
            if (u.first == e) continue;
            if (u.first < p[0]) continue;
            auto uf = f | u.second;
            auto ud = __builtin_popcountll(uf);
            p.push_back(u.first);
            q.push({{-ud,uf},p});
            p.pop_back();
        }
    }
}
