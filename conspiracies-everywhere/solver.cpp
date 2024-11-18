#include <iostream>

using namespace std;

int main() {
    long long n, k;
    cin>>n>>k;
    if ((1LL<<(n - 1)) > k) {
        cout<<"The truth is out there"<<endl;
    } else {
        cout<<(k - (1LL<<(n - 1)) + 1);
        for (int i = 1; i < n; i++) {
            cout<<" "<<1;
        }
        cout<<endl;
    }
}