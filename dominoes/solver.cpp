#include <iostream>
#include <algorithm>
#include <utility>
#include <deque>

#define pii pair<int, int>
#define F first
#define S second

using namespace std;

int main() {
    int n;
    cin>>n;
    
    pii p[n];
    for (int i = 0; i < n; i++) {
        cin>>p[i].F>>p[i].S;
    }

    for (int i = 0; i < n; i++) {
        if (p[i].F != p[0].F || p[i].S != p[0].S) goto two; 
    }
    for (int i = 0; i < n; i++) {
        cout<<p[i].F<<" "<<p[i].S<<" ";
    }
    cout<<endl;
    return 0;

    two:;
    for (int i = 0; i < n; i++) {
        if ((p[i].F != p[0].F || p[i].S != p[0].S) && (p[i].S != p[0].F || p[i].F != p[0].S)) goto more; 
    }
    cout<<"Impossible"<<endl;
    return 0;

    more:;
    deque<pii> d;
    sort(p, p + n);
    d.push_back(p[0]);
    int l = 1;
    int r = n - 1;
    while (l <= r) {
        if (d.back().S != p[l].F) {
            d.push_back(p[l++]);
        } else if (d.front().F != p[l].S) {
            d.push_front(p[l++]);
        } else if (d.back().S != p[r].F) {
            d.push_back(p[r--]);
        } else if (d.front().F != p[r].S) {
            d.push_front(p[r--]);
        } else {
            while (d.back().S == p[l].F && d.front().F == p[l].S) {
                pii x = d.back();
                d.pop_back();
                d.push_front(x);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        pii x = d.front();
        d.pop_front();
        cout<<x.F<<" "<<x.S<<" ";
    }
    cout<<endl;
}
