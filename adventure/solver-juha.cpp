#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
 
struct dist {
    int i;
    int from;
    long long c;
};

struct comparator {
    bool operator()(dist a, dist b) {
        return __builtin_popcountll(a.c) > __builtin_popcountll(b.c);
    }
};

int main() {
    int n, m;
    cin>>n>>m;
    int e[n + 1];
    
    vector<pair<int, long long>> v[n + 1];
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin>>a>>b>>c;
        v[a].push_back({b, c});
        v[b].push_back({a, c});
    }
 
    int ans = m + 1;
    int best_x = 0;
    for (int x = 1; x <= n; x++) {
        for (int i = 0; i <= n; i++) {
            e[i] = 0;
        }

        priority_queue<dist, vector<dist>, comparator> q;
        q.push(dist{x, -1, 0});
        while (!q.empty()) {
            int i = q.top().i;
            int from = q.top().from;
            long long c = q.top().c;
            q.pop();
            if (e[i]) {
                int res = __builtin_popcountll(c) + e[i];
                if (res < ans) {
                    best_x = x;
                }
                ans = min(ans, res);
                continue;
            }
            e[i] += __builtin_popcountll(c);
            for (pair<int, long long> p : v[i]) {
                int j = p.first;
                if (j == from) continue;
                q.push(dist{j, i, c | (1LL<<p.second)});
            }
        }
    }

    int fromi[n + 1];
    for (int i = 0; i <= n; i++) {
        e[i] = 0;
        fromi[i] = 0;
    }
    vector<int> sol;

    priority_queue<dist, vector<dist>, comparator> q;
    q.push(dist{best_x, -1, 0});
    while (!q.empty()) {
        int i = q.top().i;
        int from = q.top().from;
        long long c = q.top().c;
        q.pop();
        if (e[i]) {
            int res = __builtin_popcountll(c) + e[i];
            if (res == ans) {
                int j = i;
                while (j != best_x) {
                    sol.push_back(j);
                    j = fromi[j];
                }
                sol.push_back(j);
                reverse(sol.begin(), sol.end());
                j = from;
                while (j != best_x) {
                    sol.push_back(j);
                    j = fromi[j];
                }
                for (int k : sol) {
                    cout<<k<<" ";
                }
                cout<<endl;
                return 0;
            }
            continue;
        }
        fromi[i] = from;
        e[i] += __builtin_popcountll(c);
        for (pair<int, long long> p : v[i]) {
            int j = p.first;
            if (j == from) continue;
            q.push(dist{j, i, c | (1LL<<p.second)});
        }
    }
}