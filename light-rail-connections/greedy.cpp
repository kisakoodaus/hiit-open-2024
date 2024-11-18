#include <iostream>
#include <vector>
#include <algorithm>

// always creates a solution that has at most 2*n connections
// this should not work?

using namespace std;

int n, m;
int d[1111];
vector<vector<int>> v;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        d[a]++; d[b]++;
        v.push_back({a,b});
    }

    int k = v.size();
    while (k > n*2) {
        int pu = -1;
        int pi = -1;
        for (int i = 0; i < k; i++) {
            int u = min(d[v[i][0]], d[v[i][1]]);
            if (u > pu) {
                pu = u;
                pi = i;
            }
        }
        d[v[pi][0]]--;
        d[v[pi][1]]--;
        swap(v[pi], v[k-1]);
        k--;
    }

    cout << k << "\n";
    for (int i = 0; i < k; i++) {
        cout << v[i][0] << " " << v[i][1] << "\n";
    }
}
