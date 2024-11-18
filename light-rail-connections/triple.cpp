#include <iostream>
#include <vector>

// creates a tree and prints each edge three times
// should fail

using namespace std;

int co[1111];

int id(int x) {
    while (x != co[x]) x = co[x];
    return x;
}

void merge(int a, int b) {
    a = id(a);
    b = id(b);
    co[b] = a;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) co[i] = i;
    vector<vector<int>> r;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        if (id(a) == id(b)) continue;
        merge(a,b);
        r.push_back({a,b});
    }
    int k = r.size();
    cout << k*3 << "\n";
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 3; j++) {
            cout << r[i][0] << " " << r[i][1] << "\n";
        }
    }
}
