#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <cassert>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator raw [x]..." << endl;
    cerr << "       ./generator random <seed> equilateral <count> <base>" << endl;
    cerr << "       ./generator random <seed> even <count> <base>" << endl;
    // cerr << "       ./generator random <seed> <type> <count> <base>" << endl;
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
    assert(a <= b);
    return uniform_int_distribution<int>(a, b)(r_dev);
}
long long rnd64(long long a, long long b)
{
    return uniform_int_distribution<long long>(a, b)(r_dev64);
}
// Returns either 0 or 1
int coin() { return rnd(0, 1); }
// Shuffles any type with begin and end
template <typename T>
void shuffle(T &arr)
{
    shuffle(arr.begin(), arr.end(), r_dev);
}

void print_instance(const std::vector<long long> &instance)
{

    cout << instance.size() << '\n';
    cout << instance[0];
    for (size_t i = 1; i < instance.size(); i++)
        cout << " " << instance[i];
    cout << '\n';
}

long long equilateral_number(long long n)
{
    return n * (n - 1) / 2;
}

int main(int argc, char **argv)
{
    // Check argument count
    if (argc < 2)
        usage();

    if (string(argv[1]) == "raw")
    {
        // Parse arguments into instance
        std::vector<long long> instance;
        for (int i = 2; i < argc; i++)
        {
            long long x = stoll(argv[i]);
            instance.push_back(x);
        }
        print_instance(instance);
    }
    else if (string(argv[1]) == "random")
    {
        if (argc != 6)
            usage();
        unsigned long long seed = stoull(argv[2]);
        r_dev.seed(seed);
        r_dev64.seed(seed);
        string type = argv[3];
        int n = stoi(argv[4]);
        long long base = stoll(argv[5]);

        if (type == "equilateral")
        {
            long long budget_left = (1ll << n) - 2;
            budget_left -= n * base;
            assert(budget_left >= equilateral_number(n));

            std::vector<long long> instance;
            for (long long i = n; i > 0; i--)
            {
                long long x = rnd64(i - 1, i - 1 + budget_left - equilateral_number(i));
                budget_left -= x;
                instance.push_back(base + x);
            }
            print_instance(instance);
        }
        else if (type == "even")
        {
            long long budget_left = (1ll << n) - 2;
            budget_left -= n * base;
            assert(budget_left >= equilateral_number(n));

            std::vector<long long> instance;
            for (long long i = n; i > 0; i--)
            {
                long long x = rnd64(0, base);
                if (std::count(instance.begin(), instance.end(), base + x))
                {
                    continue;
                }
                budget_left -= x;
                instance.push_back(base + x);
            }
            assert(budget_left >= 0);
            print_instance(instance);
        }
        else
        {
            usage();
        }
    }
    else if (string(argv[1]) == "break-brute") {
        int n = 40;
        long long d = 5000000000;
        vector<long long> a(n);
        // https://oeis.org/A005318
        a[1] = 1;
        for (int i = 2; i < n; i++) {
            a[i] = 2*a[i-1]-a[i-1-floor(.5+sqrt(2*(i-1)))];
        }
        vector<long long> instance;
        for (int i = 0; i < n; i++) {
            instance.push_back(d+a[i]);
        }
        print_instance(instance);
    }
    else
    {
        usage();
    }
}

