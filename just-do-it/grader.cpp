#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <random>

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

mt19937 r_dev;
mt19937_64 r_dev64;
// Returns a value in range [a, b] inclusive
int rnd(int a, int b)
{
    return uniform_int_distribution<int>(a, b)(r_dev);
}

#define SAFE_READ(x) \
    do               \
    {                \
        if (!(x))    \
            fail();  \
    } while (false)

int median(int a, int b, int c)
{
    if (a < b)
    {
        if (b < c)
            return b;
        if (a < c)
            return c;
        return a;
    }
    else
    {
        if (a < c)
            return a;
        if (b < c)
            return c;
        return b;
    }
}

void hiit_sort(int *arr, int low, int high, int &count)
{
    if (high - low > 1)
    {
        int pivot = median(arr[low], arr[(low + high) / 2], arr[high - 1]);
        int a = low;
        int b = high - 1;
        while (true)
        {
            while (count++, arr[a] < pivot)
                a++;
            while (count++, arr[b] > pivot)
                b--;
            if (a >= b)
                break;
            swap(arr[a], arr[b]);
            a++;
            b--;
        }
        hiit_sort(arr, low, a, count);
        hiit_sort(arr, a, high, count);
    }
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

    int n;
    SAFE_READ(input >> n);

    std::vector<int> values(n);
    for (int &v : values)
        SAFE_READ(user >> v);

    int operations = 0;
    hiit_sort(values.data(), 0, n, operations);

    // Check that there were enough comparisons
    std::cerr << "Used " << operations << " comparisons\n";
    int bound = n * n / 4;
    if (n * n % 4 != 0) bound++;
    if (operations < bound)
        fail();

    // Check that the array is a permutation
    for (int i = 0; i < n; i++)
    {
        if (values[i] != i + 1)
            fail();
    }

    accept();
}
