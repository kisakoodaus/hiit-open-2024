#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define ll long long

using namespace std;

int main() {
    srand(time(0));
    int n;
    cin>>n;
    ll v[n];
    for (int i = 0; i < n; i++) {
        cin>>v[i];
    }
    set<pair<ll, ll>> col;
    ll mask1;
    ll mask2;
    while (true) {
        ll mask = 0;
        ll sum = 0;
        for (ll i = 0; i < n; i++) {
            if (rand() & 1) {
                sum += v[i];
                mask ^= (1LL<<i);
            }
        }
        auto p = col.lower_bound({sum, 0});
        if (p != col.end() && p->first == sum && p->second != mask) {
            mask1 = mask;
            mask2 = p->second;
            break;
        }
        col.insert({sum, mask});
    }

    ll x = mask1 & mask2;
    for (ll i = 0; i < n; i++) {
        if ((1LL<<i) & (mask1 ^ x)) cout<<v[i]<<" ";
    }
    cout<<endl;
    for (ll i = 0; i < n; i++) {
        if ((1LL<<i) & (mask2 ^ x)) cout<<v[i]<<" ";
    }
    cout<<endl;
}