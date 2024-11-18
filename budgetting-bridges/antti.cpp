#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define INF 999999999

int co[202020];
int si[202020];

int id(int x) {
    while (x != co[x]) x = co[x];
    return x;
}

vector<array<int,4>> mem;

void merge(int a, int b) {
    a = id(a);
    b = id(b);
    if (a == b) return;
    if (si[a] < si[b]) swap(a,b);
    mem.push_back({a, si[a], b, co[b]});
    si[a] += si[b];
    co[b] = a;
}

void undo(int c) {
    int un = mem.size();
    for (int i = 0; i < c; i++) {
        auto u = mem[un-i-1];
        si[u[0]] = u[1];
        co[u[2]] = u[3];
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    map<array<int,2>,int> weight;
    vector<array<int,4>> events;
    for (int i = 0; i < m; i++) {
        int v, w, c;
        cin >> v >> w >> c;
        weight[{v,w}] = c;
        events.push_back({c,INF,v,w});
    }
    vector<int> cnt(k);
    for (int i = 0; i < k; i++) {
        int b;
        cin >> b;
        for (int j = 0; j < b; j++) {
            int v, w;
            cin >> v >> w;
            events.push_back({weight[{v,w}],i,v,w});
        }
        cnt[i] = b;
    }
    sort(events.begin(),events.end());

    for (int i = 1; i <= n; i++) {
        co[i] = i; si[i] = 1;
    }
    int ec = 0, ep = INF;
    for (auto e : events) {
        if (ep != e[1]) {
            if (ep != INF) {
                cnt[ep] -= ec;
                undo(ec);
            }
            ec = 0;
            ep = e[1];
        }
        if (id(e[2]) != id(e[3])) {
            merge(e[2],e[3]);
            ec++;
        }
    }

    for (int i = 0; i < k; i++) {
        if (cnt[i] == 0) cout << "YES\n";
        else cout << "NO\n";
    }
}
