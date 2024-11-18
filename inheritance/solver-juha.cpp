#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long
#define N 20

using namespace std;

ll ls[1<<N];
ll rs[1<<N];

int main() {
    int n;
    cin>>n;
    ll l[(n + 1) / 2];
    ll r[(n + 1) / 2];
    for (int i = 0; i < (n + 1) / 2; i++) {
        cin>>l[i];
    }
    for (int i = 0; i < n / 2; i++) {
        cin>>r[i];
    }

    ll lb = 1;
    ll ub = (1LL<<n) - 2;

    if (n % 2) {
        r[n / 2] = (1LL<<n);
        n++;
    }

    n /= 2;

    for (int mask = 0; mask < (1<<n); mask++) {
        ll sum = 0;
        for (int j = 0; j < n; j++) {
            if (mask & (1<<j)) sum += l[j];
        }
        ls[mask] = sum;
    }
    for (int mask = 0; mask < (1<<n); mask++) {
        ll sum = 0;
        for (int j = 0; j < n; j++) {
            if (mask & (1<<j)) sum += r[j];
        }
        rs[mask] = sum;
    }
    sort(ls, ls + (1<<n));
    sort(rs, rs + (1<<n));

    while (lb != ub) {
        ll mid = (lb + ub) / 2;
        ll count = 0;
        ll rl = (1<<n) - 1;
        ll rr = (1<<n) - 1;
        for (int lp = 0; lp < (1<<n); lp++) {
            while (rl != -1 && ls[lp] + rs[rl] >= lb) rl--;
            while (rr != -1 && ls[lp] + rs[rr] > mid) rr--;
            count += rr - rl;
        }
        if (count > mid - lb + 1) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    ll target = lb;
    ll rl = (1<<n) - 1;
    ll rr = (1<<n) - 1;
    vector<int> lsol, rsol;
    for (int lp = 0; lp < (1<<n); lp++) {
        while (rl != -1 && ls[lp] + rs[rl] >= target) rl--;
        while (rr != -1 && ls[lp] + rs[rr] > target) rr--;
        if (rr != rl) {
            ll lt = ls[lp];
            ll rt = target - lt;
            for (int mask = 0; mask < (1<<n); mask++) {
                ll sum = 0;
                for (int j = 0; j < n; j++) {
                    if (mask & (1<<j)) sum += l[j];
                }
                if (sum == lt) lsol.push_back(mask);
            }
            for (int mask = 0; mask < (1<<n); mask++) {
                ll sum = 0;
                for (int j = 0; j < n; j++) {
                    if (mask & (1<<j)) sum += r[j];
                }
                if (sum == rt) rsol.push_back(mask);
            }
            if (lsol.size() > 1 || rsol.size() > 1) {
                lsol.push_back(lsol.back());
                rsol.push_back(rsol.back());
                break;
            }
        }
    }

    int lx = lsol[0] & lsol[1];
    int rx = rsol[0] & rsol[1];
    for (int i = 0; i < n; i++) {
        if ((1<<i) & (lsol[0] ^ lx)) cout<<l[i]<<" ";
    }
    for (int i = 0; i < n; i++) {
        if ((1<<i) & (rsol[0] ^ rx)) cout<<r[i]<<" ";
    }
    cout<<endl;
    for (int i = 0; i < n; i++) {
        if ((1<<i) & (lsol[1] ^ lx)) cout<<l[i]<<" ";
    }
    for (int i = 0; i < n; i++) {
        if ((1<<i) & (rsol[1] ^ rx)) cout<<r[i]<<" ";
    }
    cout<<endl;
}