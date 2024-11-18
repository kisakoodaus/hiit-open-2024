#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator n upper_bound" << endl;
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
    if (argc != 3)
        usage();

    // Parse arguments into numbers
    int n = stoi(argv[1]);
    if (n == 3) {
        cout<<"3\n1 2 1"<<endl;
        return 0;
    }
    int ub = stoi(argv[2]);
    unsigned long long seed = 100000 * (unsigned long long)(ub + 1) + n;
    r_dev.seed(seed);
    r_dev64.seed(seed);

    cout<<n<<endl;
    for (int i = 0; i < n; i++) {
        cout<<rnd(0, ub);
        if (i != n - 1) cout<<" ";
    }
    cout<<endl;
}