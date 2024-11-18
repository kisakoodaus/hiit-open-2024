#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator seed number" << endl;
    exit(1);
}

mt19937 r_dev;
mt19937_64 r_dev64;
// Returns a value in range [0, 1[
double rnd()
{
    return uniform_real_distribution<double>(0, 1)(r_dev);
}
// Returns a value in range [a, b] inclusive
int rnd(int a, int b)
{
    return uniform_int_distribution<int>(a, b)(r_dev);
}
long long rnd64(long long a, long long b)
{
    return uniform_int_distribution<long long>(a, b)(r_dev64);
}
// Returns either 0 or 1
int coin()
{
    return rnd(0, 1);
}
// Shuffles any type with begin and end
template <typename T>
void shuffle(T &arr)
{
    shuffle(arr.begin(), arr.end(), r_dev);
}

vector<int> kk[1<<18];
vector<int> s[1<<18];
int cc;
 
bool same (int a, int b) {
	while (kk[a].back() != a) a = kk[a].back();
	while (kk[b].back() != b) b = kk[b].back();
	return a == b;
}
 
void join (int a, int b) {
	while (kk[a].back() != a) a = kk[a].back();
	while (kk[b].back() != b) b = kk[b].back();
	if (s[a].back() > s[b].back()) {
		s[a].push_back(s[a].back() + s[b].back());
		s[b].push_back(s[b].back());
		kk[b].push_back(a);
		kk[a].push_back(a);
	} else {
		s[b].push_back(s[a].back() + s[b].back());
		s[a].push_back(s[a].back());
		kk[a].push_back(b);
		kk[b].push_back(b);
	}
    cc--;
}

int main(int argc, char **argv)
{
    if (argv[1][0] == 'M') {
        bool lf = true;
        for (int i = 2; i < argc; i++) {
            int x = stoi(argv[i]);
            if (x) {
                if (!lf) cout<<" ";
                lf = false;
                cout<<x;
            } else {
                cout<<endl;
                lf = true;
            }
        }
        cout<<endl;
    } else if (argv[1][0] == 'G') {
        unsigned long long seed = stoull(argv[2]);
        r_dev.seed(seed);
        r_dev64.seed(seed);
        int n = stoi(argv[3]);
        int m = stoi(argv[4]);
        int k = stoi(argv[5]);
        int w = stoi(argv[6]);
        int l = stoi(argv[7]);
        int u = stoi(argv[8]);
        int mm = m;

        cout<<n<<" "<<m<<" "<<k<<endl;

        cc = n;
        for (int i = 1; i <= n; i++) {
            kk[i].push_back(i);
            s[i].push_back(1);
        }
        set<pair<int, int>> eds;
        vector<pair<int, int>> ps;
        while (cc != 1) {
            int a = rnd(1, n);
            int b = rnd(1, n);
            if (!same(a, b)) {
                join(a, b);
                m--;
                cout<<a<<" "<<b<<" "<<rnd(1, w)<<endl;
                ps.push_back({a, b});
                if (b < a) swap(a, b);
                eds.insert({a, b});
            }
        }
        while (m) {
            int a = rnd(1, n);
            int b = rnd(1, n);
            if (a == b) continue;
            if (eds.count({min(a, b), max(a, b)})) continue;
            cout<<a<<" "<<b<<" "<<rnd(1, w)<<endl;
            ps.push_back({a, b});
            if (b < a) swap(a, b);
            eds.insert({a, b});
            m--;
        }
        m = mm;
        while (k) {
            set<int> es;
            int b = rnd(l, u);
            cout<<b<<endl;
            while ((int)es.size() != b) {
                int i = rnd(0, m - 1);
                es.insert(i);
            }
            for (int i : es) {
                cout<<ps[i].first<<" "<<ps[i].second<<endl;
            }
            k--;
        }
    } else {
        cerr<<"Check generator.cpp..."<<endl;
        exit(1);
    }
}
