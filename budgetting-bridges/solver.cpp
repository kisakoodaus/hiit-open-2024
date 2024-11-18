#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;
 
vector<int> k[1<<18];
vector<int> s[1<<18];
vector<pair<int, int>> st;
 
bool same (int a, int b) {
    while (k[a].back() != a) a = k[a].back();
    while (k[b].back() != b) b = k[b].back();
    return a == b;
}
 
void join (int a, int b) {
    //cout<<"JOIN "<<a<<" "<<b<<endl;
    while (k[a].back() != a) a = k[a].back();
    while (k[b].back() != b) b = k[b].back();
    if (s[a].back() > s[b].back()) {
        s[a].push_back(s[a].back() + s[b].back());
        s[b].push_back(s[b].back());
        k[b].push_back(a);
        k[a].push_back(a);
    } else {
        s[b].push_back(s[a].back() + s[b].back());
        s[a].push_back(s[a].back());
        k[a].push_back(b);
        k[b].push_back(b);
    }
    st.push_back({a, b});
}
 
void undo (int a, int b) {
    //cout<<"UNDO "<<a<<" "<<b<<endl;
    s[a].pop_back();
    s[b].pop_back();
    k[a].pop_back();
    k[b].pop_back();
}
 
int main () {
    int n, m, kk;
    cin>>n>>m>>kk;
    for (int i = 1; i <= n; i++) {
        k[i].push_back(i);
        s[i].push_back(1);
    }

    map<pair<int, int>, int> costs;
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin>>a>>b>>c;
        if (a > b) swap(a, b);
        costs[{a, b}] = c; 
        edges.push_back({c, {a, b}});
    }
    sort(edges.begin(), edges.end());
    int ei = 0;

    bool ok[kk];
    vector<pair<int, pair<int, int>>> qedges[kk];
    int qptr[kk]; 
    set<pair<int, int>> queries;
    for (int i = 0; i < kk; i++) {
        ok[i] = true;
        qptr[i] = 0;
        int b;
        cin>>b;
        for (int j = 0; j < b; j++) {
            int v, w;
            cin>>v>>w;
            if (v > w) swap(v, w);
            int c = costs[{v, w}];
            queries.insert({c, i});
            qedges[i].push_back({c, {v, w}});
        }
        sort(qedges[i].begin(), qedges[i].end());
    }

    while (!queries.empty()) {
        auto query = *queries.begin();
        queries.erase(queries.begin());
        int qc = query.first;
        int qi = query.second;
        while (ei != m && edges[ei].first < qc) {
            int a = edges[ei].second.first;
            int b = edges[ei].second.second;
            if (!same(a, b)) {
                join(a, b);
            }
            ei++;
        }
        int cnt = 0;
        while (qptr[qi] != (int)qedges[qi].size() && qedges[qi][qptr[qi]].first == qc) {
            int a = qedges[qi][qptr[qi]].second.first;
            int b = qedges[qi][qptr[qi]].second.second;
            if (!same(a, b)) {
                join(a, b);
                cnt++;
            } else {
                ok[qi] = false;
            }
            qptr[qi]++;
        }
        while (cnt) {
            undo(st.back().first, st.back().second);
            st.pop_back();
            cnt--;
        }
    }
    for (int i = 0; i < kk; i++) {
        if (ok[i]) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}