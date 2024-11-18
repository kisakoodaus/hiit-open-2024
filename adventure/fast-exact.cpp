#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <array>

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
            cin >> d;
            d--;
            mask |= 1ll << d;
        }
        v[a].push_back({b,mask});
        v[b].push_back({a,mask});
    }
    // count, mask, first, second_last, last, id, prev
    priority_queue<array<ll,7>> q;
    vector<array<ll,7>> h;
    for (int i = 1; i <= n; i++) {
        array<ll,7> u = {0,0,i,0,i,(int)h.size(),-1};
        q.push(u);
        h.push_back(u);
    }
    ll steps = 0;
    while (true) {
        steps++;
        auto x = q.top(); q.pop();
        if (x[2] == x[4] && x[3] != 0) {
            cerr << "Using " << -x[0] << " colors, " << steps << " steps\n";
            int k = x[6];
            while (k != -1) {
                cout << h[k][4] << " ";
                k = h[k][6];
            }
            cout << "\n";
            return 0;
        }
        for (auto u : v[x[4]]) {
            if (u.first == x[3]) continue;
            if (u.first < x[2]) continue;
            auto uf = x[1] | u.second;
            auto ud = __builtin_popcountll(uf);
            array<ll,7> z = {-ud,uf,x[2],x[4],u.first,(int)h.size(),x[5]};
            q.push(z);
            h.push_back(z);
        }
    }
}
