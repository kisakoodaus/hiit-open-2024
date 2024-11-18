#include <iostream>
#include <vector>

#define ll long long

using namespace std;

int main() {
    ll n;
    cin>>n;
    vector<ll> t;
    ll cum = 1;
    ll inc = 2;
    while (cum <= n) {
        if (cum == n) {
            cout<<1<<endl;
            return 0;
        }
        t.push_back(cum);
        cum += inc;
        inc++;
    }
    int r = (int)t.size() - 1;
    for (int l = 0; l < (int)t.size(); l++) {
        while (t[l] + t[r] > n && r > 0) r--;
        if (t[l] + t[r] == n) {
            cout<<2<<endl;
            return 0;
        }
    }
    cout<<3<<endl;
}
