#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    if (n <= 3) {
        for (int i = 1; i <= n; i++) cout << i << " ";
        cout << "\n";
    } else {
        cout << n-2 << " ";
        for (int i = 1; i <= (n-2)/2; i++) cout << i << " ";
        cout << n-1 << " ";
        for (int i = (n-2)/2+1; i <= n-3; i++) cout << i << " ";
        cout << n << "\n";
    }
}
