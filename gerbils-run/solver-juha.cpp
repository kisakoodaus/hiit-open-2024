#include <iostream>
#include <vector>

using namespace std;

double pi = 3.1415926;

int main() {
    int r;
    cin>>r;
    double circ = 2 * r * pi;

    vector<double> ans;
    double x = -1;
    while (x + 3 < circ) {
        ans.push_back(x + 1);
        x += 2;
    }
    int id = 1;
    while (x + 2 < circ) {
        for (int i = id; i < (int)ans.size(); i++) {
            ans[i] += 0.5;
        }
        id++;
        x += 0.5;
    }
    for (double d : ans) {
        int i = (int)(d + 0.1);
        int h = abs(d - i) > 0.25 ? 1 : 0;
        cout<<(2 * i + h)<<"/2 "<<(2 + 2 * i + h)<<"/2"<<endl;
    }
}