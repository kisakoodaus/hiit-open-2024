#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
string s[1000];
int g[1000][1000];
int fh[1000], fv[1000];
vector<int> vh[1000];
vector<int> vv[1000];
int ch[1000][3];
int cv[1000][3];
int th[1000], tv[1000];

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '.') {
                fh[i] = fv[j] = 1;
                continue;
            }
            if (s[i][j] == 'H') g[i][j] = 0;
            if (s[i][j] == 'I') g[i][j] = 1;
            if (s[i][j] == 'T') g[i][j] = 2;
            vh[i].push_back(j);
            vv[j].push_back(i);
            ch[i][g[i][j]]++;
            cv[j][g[i][j]]++;
            th[i]++; tv[j]++;
        }
    }
    vector<array<int,3>> r;
    while (true) {
        bool f = false;
        for (int i = 0; i < n; i++) {
            if (fh[i] || th[i] == 0) continue;
            for (int j = 0; j < 3; j++) {
                if (ch[i][j] == th[i]) {
                    for (auto x : vh[i]) {
                        if (g[i][x] == j) {
                            cv[x][j]--;
                            tv[x]--;
                        }
                        g[i][x] = 3;
                    }
                    ch[i][j] = th[i] = 0;
                    r.push_back({0,i,j});
                    f = true;
                    break;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            if (fv[i] || tv[i] == 0) continue;
            for (int j = 0; j < 3; j++) {
                if (cv[i][j] == tv[i]) {
                    for (auto x : vv[i]) {
                        if (g[x][i] == j) {
                            ch[x][j]--;
                            th[x]--;
                        }
                        g[x][i] = 3;
                    }
                    cv[i][j] = tv[i] = 0;
                    r.push_back({1,i,j});
                    f = true;
                    break;
                }
            }
        }
        if (!f) break;
    }
    bool w = true;
    for (int i = 0; i < n; i++) if (th[i] != 0) w = false;
    for (int i = 0; i < m; i++) if (tv[i] != 0) w = false;
    if (w) {
        cout << r.size() << "\n";
        reverse(r.begin(),r.end());
        for (auto x : r) {
            cout << "RC"[x[0]] << " " << (x[1]+1) << " " << "HIT"[x[2]] << "\n";
        }
    } else {
        cout << "Impossible\n";
    }
}
