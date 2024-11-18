#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

int n, m;

vector<int> v[1111];
int g[1111];
int z[1111];
int w[1111][1111];
vector<int> p;

int pc = 100;
vector<int> pp;

void go(int s, int e) {
    if (z[s]) {
        p.push_back(s);
        int i = p.size()-1;
        vector<int> u;
        ll f = 0;
        while (true) {
            u.push_back(p[i]);
            f |= 1LL<<w[p[i]][p[i-1]];
            i--;
            if (p[i] == s) break;
        }
        int c = __builtin_popcountll(f);
        if (c < pc) {
            pc = c;
            pp = u;
        }
        p.pop_back();
        return;
    }
    if (g[s]) return;
    g[s] = 1;
    z[s] = 1;
    p.push_back(s);

    for (auto x : v[s]) {
        if (x == e) continue;
        go(x, s);
    }

    z[s] = 0;
    p.pop_back();
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        w[a][b] = w[b][a] = c;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for (int x = 1; x <= n; x++) {
        for (int i = 1; i <= n; i++) g[i] = z[i] = 0;
        p.clear();
        go(x,0);
    }
    for (auto x : pp ) cout << x << " ";
    cout << "\n";
}
