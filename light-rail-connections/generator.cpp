#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator seed n m" << endl;
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
    if (argc < 3)
        usage();

    // Parse arguments into numbers
    unsigned long long seed = stoull(argv[1]);
    r_dev.seed(seed);
    r_dev64.seed(seed);

    if (argv[2] == "example"s)
    {
        cout << "5 8\n1 2\n1 3\n1 4\n2 3\n2 4\n3 4\n3 5\n2 5" << endl;
    }
    else if (argv[2] == "cliques"s)
    {
        // two cliques connected with an edge
        if (argc != 4)
            usage();
        int n = atoi(argv[3]);

        vector<pair<int, int>> edges;
        for (int i = 1; i <= n / 2; i++)
        {
            for (int j = i + 1; j <= n / 2; j++)
            {
                edges.push_back({i, j});
            }
        }
        edges.push_back({n / 2, n / 2 + 1});
        for (int i = n / 2 + 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                edges.push_back({i, j});
            }
        }
        int m = edges.size();
        cout << n << " " << m << "\n";
        for (auto e : edges)
        {
            cout << e.first << " " << e.second << "\n";
        }
    }
    else if (argv[2] == "clique-cliques"s)
    {
        // four cliques that form a clique
        if (argc != 4)
            usage();
        int n = atoi(argv[3]);

        vector<pair<int, int>> edges;
        for (int i = 1; i <= n / 4; i++)
        {
            for (int j = i + 1; j <= n / 4; j++)
            {
                edges.push_back({i, j});
                edges.push_back({i + n / 4, j + n / 4});
                edges.push_back({i + n / 2, j + n / 2});
                edges.push_back({i + 3 * n / 4, j + 3 * n / 4});
            }
        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                edges.push_back({25 * i + 1, 25 * j + 1});
            }
        }
        int m = edges.size();
        cout << n << " " << m << "\n";
        for (auto e : edges)
        {
            cout << e.first << " " << e.second << "\n";
        }
    }
    else if (argv[2] == "sausage"s)
    {
        if (argc != 5)
            usage();
        int n = atoi(argv[3]);
        int c = atoi(argv[4]);
        int m = c * (n - 1);
        int N = n + m;
        int M = 2 * m;

        cerr<<m<<" "<<N<<" "<<M<<endl;

        std::vector<int> names(N);
        for (size_t i = 0; i < names.size(); i++)
            names[i] = i + 1;
        shuffle(names);

        cout << N << " " << M << endl;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cout << names[i] << " " << names[n + i * c + j] << "\n";
                cout << names[i + 1] << " " << names[n + i * c + j] << "\n";
            }
        }
    }
    else if (argv[2] == "random"s)
    {

        if (argc != 5)
            usage();
        int n = atoi(argv[3]);
        int m = atoi(argv[4]);

        set<pair<int, int>> s;
        cout << n << " " << m << endl;
        while ((int)s.size() != m)
        {
            int i, j;
            i = rnd(1, n);
            j = rnd(1, n);
            if (i == j)
                continue;
            if (i > j)
                swap(i, j);
            if (s.count({i, j}))
                continue;
            s.insert({i, j});
            if (coin())
                swap(i, j);
            cout << i << " " << j << endl;
        }
    }
    else
    {
        usage();
    }
}
