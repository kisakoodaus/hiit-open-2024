#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator max_len" << endl;
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

int main(int argc, char **argv)
{
    // Check argument count
    if (argc != 2)
        usage();

    // Parse arguments into numbers
    long long m = stoull(argv[1]);
    r_dev.seed(m);
    r_dev64.seed(m);

    if (m == 6) {
        cout<<"ULDRUR"<<endl;
        return 0;
    }

    // Create the test case

    string pgen[] = {"URULU", "URULDRDLU", "URDLDRDLDRULU"};
    vector<pair<char, string>> parts;
    for (string s : pgen) {
        for (int i = 0; i < 4; i++) {
            for (int flip = 0; flip < 2; flip++) {
                string t = s;
                for (int j = 0; j < (int)t.length(); j++) {
                    for (int k = 0; k < 4; k++) {
                        if (s[j] == "ULDR"[k]) {
                            t[j] = "ULDR"[(k + i) % 4];
                            break;
                        }
                    }
                }
                if (flip) {
                    for (int j = 0; j < (int)t.length(); j++) {
                        if (t[j] == 'R') t[j] = 'L';
                        else if (t[j] == 'L') t[j] = 'R';
                    }
                }
                parts.push_back({t[0], t});
            }
        }
    }

    string test = "ULDR";

    while ((int)test.length() + 13 <= m) {
        int i = rnd(0, (int)test.length() - 1);
        vector<string> pot;
        for (auto rule : parts) {
            if (rule.first == test[i]) {
                pot.push_back(rule.second);
            }
        }
        test = test.substr(0, i) + pot[rnd(0, (int)pot.size() - 1)] + test.substr(i + 1);
    }

    int offset = rnd(0, 3);
    for (int j = 0; j < (int)test.length(); j++) {
        for (int k = 0; k < 4; k++) {
            if (test[j] == "ULDR"[k]) {
                test[j] = "ULDR"[(k + offset) % 4];
                break;
            }
        }
    }

    // Output the test case to the standard output
    cout << test << '\n';
}
