#include <iostream>

using namespace std;

using ll = long long;

int main() {
    int n;
    ll k;
    cin >> n >> k;

    ll top = 1LL<<(n-1);
    if (top > k) {
        cout << "The truth is out there\n";
    } else {
        for (int i = 1; i <= n-1; i++) cout << "1 ";
        cout << 1+k-top << "\n";
    }
}
