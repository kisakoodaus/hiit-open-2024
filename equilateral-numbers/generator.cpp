#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator n" << endl;
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc != 2) usage();
    long long n = stoll(argv[1]);
    cout << n << '\n';
}
