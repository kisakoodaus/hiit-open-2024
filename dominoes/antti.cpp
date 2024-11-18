#include <iostream>

using namespace std;

int d[7][7];

int p[7];
int w[6][2];
int r;

void show() {
    for (int i = 0; i < r; i++) {
        int a = w[i][0];
        int b = w[i][1];
        for (int j = 1; j <= 6; j++) {
            if (b == j) continue;
            for (int k = 0; k < d[a][j]; k++) {
                cout << a << " " << j << " ";
            }
        }
        for (int k = 0; k < d[a][b]; k++) {
            cout << a << " " << b << " ";
        }
    }
    cout << "\n";
    exit(0);
}

void search(int k, int e) {
    if (k == r) show();
    for (int i = 1; i <= 6; i++) {
        if (i == e || p[i]) continue;
        p[i] = 1;
        for (int j = 1; j <= 6; j++) {
            if (d[i][j]) {
                w[k][0] = i;
                w[k][1] = j;
                search(k+1,j);
            }
        }
        p[i] = 0;
    }
}

int main() {
    int n;
    cin >> n;
    int s[7] = {0};
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        d[a][b]++;
        if (!s[a]) {
            s[a] = 1;
            r++;
        }
    }

    search(0, 0);
    cout << "Impossible\n";
}
