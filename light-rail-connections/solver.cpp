#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;
 
int k[1<<18];
int s[1<<18];
 
bool same (int a, int b) {
    while (k[a] != a) a = k[a];
    while (k[b] != b) b = k[b];
    return a == b;
}
 
void join (int a, int b) {
    while (k[a] != a) a = k[a];
    while (k[b] != b) b = k[b];
    if (s[a] > s[b]) {
        s[a] = s[a] + s[b];
        s[b] = s[b];
        k[a] = a;
        k[b] = a;
    } else {
        s[b] = s[a] + s[b];
        s[a] = s[a];
        k[a] = b;
        k[b] = b;
    }
}
 
int main () {
    int n, m;
    cin>>n>>m;
    set<pair<int, int>> used;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin>>u>>v;
        edges.push_back({u, v});
    }

    for (int t = 0; t < 3; t++) {
        for (int i = 1; i <= n; i++) {
            k[i] = i;
            s[i] = 1;
        }
        for (pair<int, int> e : edges) {
            if (used.count(e)) continue;
            if (same(e.first, e.second)) continue;
            join(e.first, e.second);
            used.insert(e);
        }
    }

    cout<<used.size()<<endl;
    for (pair<int, int> e : used) cout<<e.first<<" "<<e.second<<endl;
}