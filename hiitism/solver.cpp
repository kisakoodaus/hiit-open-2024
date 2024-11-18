#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int w, h;
    cin>>h>>w;
    int ch[w];
    int ci[w];
    int ct[w];
    int rh[h];
    int ri[h];
    int rt[h];
    char c[h][w];
    int nz = h * w;
    for (int i = 0; i < h; i++) {
        rh[i] = ri[i] = rt[i] = 0;
    }
    for (int i = 0; i < w; i++) {
        ch[i] = ci[i] = ct[i] = 0;
    }
    for (int i = 0; i < h; i++) {
        string s;
        cin>>s;
        for (int j = 0; j < w; j++) {
            c[i][j] = s[j];
            if (s[j] == 'H') {
                ch[j]++;
                rh[i]++;
            }
            if (s[j] == 'I') {
                ci[j]++;
                ri[i]++;
            }
            if (s[j] == 'T') {
                ct[j]++;
                rt[i]++;
            }
            if (s[j] == '.') {
                nz--;
            }
        }
    }
    
    vector<pair<int, char>> ans;
    for (int i = 0; i < h; i++) {
        if (rh[i] == w) {
            ans.push_back({i, 'H'});
            rh[i] = ri[i] = rt[i] = -1;
        } else if (ri[i] == w) {
            ans.push_back({i, 'I'});
            rh[i] = ri[i] = rt[i] = -1;
        } else if (rt[i] == w) {
            ans.push_back({i, 'T'});
            rh[i] = ri[i] = rt[i] = -1;
        }
    }
    for (int j = 0; j < w; j++) {
        if (ch[j] == h) {
            ans.push_back({-j - 1, 'H'});
            ch[j] = ci[j] = ct[j] = -1;
        } else if (ci[j] == h) {
            ans.push_back({-j - 1, 'I'});
            ch[j] = ci[j] = ct[j] = -1;
        } else if (ct[j] == h) {
            ans.push_back({-j - 1, 'T'});
            ch[j] = ci[j] = ct[j] = -1;
        }
    }

    for (int b = 0; b < (int)ans.size(); b++) {
        pair<int, char> p = ans[b];
        if (p.first >= 0) { // row
            int i = p.first;
            char col = p.second;
            for (int j = 0; j < w; j++) {
                if (c[i][j] != '?') {
                    nz--;
                    if (c[i][j] == 'H') {
                        ch[j]--;
                        rh[i]--;
                    } else if (c[i][j] == 'I') {
                        ci[j]--;
                        ri[i]--;
                    } else if (c[i][j] == 'T') {
                        ct[j]--;
                        rt[i]--;
                    }
                    ch[j]++;
                    rh[i]++;
                    ci[j]++;
                    ri[i]++;
                    ct[j]++;
                    rt[i]++;
                }
                c[i][j] = '?';
                if (ch[j] == h) {
                    ans.push_back({-j - 1, 'H'});
                    ch[j] = ci[j] = ct[j] = -1;
                } else if (ci[j] == h) {
                    ans.push_back({-j - 1, 'I'});
                    ch[j] = ci[j] = ct[j] = -1;
                } else if (ct[j] == h) {
                    ans.push_back({-j - 1, 'T'});
                    ch[j] = ci[j] = ct[j] = -1;
                }
            }
        } else { // col
            int j = -p.first - 1;
            char col = p.second;
            for (int i = 0; i < h; i++) {
                if (c[i][j] != '?') {
                    nz--;
                    if (c[i][j] == 'H') {
                        ch[j]--;
                        rh[i]--;
                    } else if (c[i][j] == 'I') {
                        ci[j]--;
                        ri[i]--;
                    } else if (c[i][j] == 'T') {
                        ct[j]--;
                        rt[i]--;
                    }
                    ch[j]++;
                    rh[i]++;
                    ci[j]++;
                    ri[i]++;
                    ct[j]++;
                    rt[i]++;
                }
                c[i][j] = '?';
                if (rh[i] == w) {
                    ans.push_back({i, 'H'});
                    rh[i] = ri[i] = rt[i] = -1;
                } else if (ri[i] == w) {
                    ans.push_back({i, 'I'});
                    rh[i] = ri[i] = rt[i] = -1;
                } else if (rt[i] == w) {
                    ans.push_back({i, 'T'});
                    rh[i] = ri[i] = rt[i] = -1;
                }
            }
        }
    }

    if (nz) {
        cout<<"Impossible"<<endl;
    } else {
        reverse(ans.begin(), ans.end());
        cout<<ans.size()<<endl;
        for (int b = 0; b < (int)ans.size(); b++) {
            pair<int, char> p = ans[b];
            if (p.first >= 0) {
                cout<<"R"<<" "<<(p.first + 1)<<" "<<p.second<<endl;
            } else {
                cout<<"C"<<" "<<(-p.first)<<" "<<p.second<<endl;
            }
        }
    }
}
