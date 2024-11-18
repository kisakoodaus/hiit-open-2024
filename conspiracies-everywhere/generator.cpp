#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator n q" << endl;
    exit(1);
}

int main(int argc, char **argv)
{
    // Check argument count
    if (argc != 3)
        usage();

    // Parse arguments into numbers
    long long n = stoll(argv[1]);
    long long q = stoll(argv[2]);

    // Output the test case to the standard output
    cout << n << " " << q << '\n';
}
