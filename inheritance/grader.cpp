#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

// Give numerical grade to the user
[[noreturn]] void grade(int result)
{
    cout << "1\n"
         << result << '\n';
    exit(0);
}
// Indicate that program failed to produce the right answer
[[noreturn]] void fail()
{
    cout << "0\n";
    exit(0);
}
// Indicate that the submission was accepted
[[noreturn]] void accept()
{
    cout << "1\n";
    exit(0);
}
#define SAFE_READ(x) \
    do               \
    {                \
        if (!(x))    \
            fail();  \
    } while (false)

std::vector<long long> read_line(ifstream &in)
{
    std::string line;
    SAFE_READ(getline(in, line));
    std::istringstream ss(line);
    std::vector<long long> nums;
    long long x;
    while (ss >> x)
        nums.push_back(x);
    // TODO: Check if this eof check is correct and works with e.g. trailing white space
    if (!ss.eof())
        fail();
    return nums;
}

int main(int argc, char **argv)
{
    string x1 = argv[1]; // correct output
    string x2 = argv[2]; // user output
    string x3 = argv[3]; // input
    ifstream correct, user, input;
    correct.open(x1);
    user.open(x2);
    input.open(x3);

    // Collect the set of input numbers
    std::multiset<long long> allowed;
    int n = 0;
    input >> n;
    for (int i = 0; i < n; i++)
    {
        long long x;
        input >> x;
        allowed.insert(x);
    }

    // Read user output
    std::vector<long long> first = read_line(user);
    std::vector<long long> second = read_line(user);
    // Ensure that the user output has ended
    std::string dummy;
    if (user >> dummy)
        fail();

    // Check that the numbers actually come from the allowed set
    std::multiset<long long> used;
    for (long long a : first)
        used.insert(a);
    for (long long a : second)
        used.insert(a);
    for (long long elem : used)
    {
        if (used.count(elem) > allowed.count(elem))
            fail();
    }

    // Check that both get the same sum, and that it's non-zero
    long long s1 = std::accumulate(first.begin(), first.end(), 0ll);
    long long s2 = std::accumulate(second.begin(), second.end(), 0ll);
    if (s1 <= 0)
        fail();
    if (s2 <= 0)
        fail();
    if (s1 != s2)
        fail();

    // Seems good
    accept();
}
