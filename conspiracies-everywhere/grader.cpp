#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

int main(int argc, char **argv)
{
    string x1 = argv[1]; // correct output
    string x2 = argv[2]; // user output
    string x3 = argv[3]; // input
    ifstream correct, user, input;
    correct.open(x1);
    user.open(x2);
    input.open(x3);

    // Write grader here
    // Remember to add this to the Makefile, otherwise the default grader will be used

    long long n, q;
    input>>n>>q;

    if ((1LL<<(n - 1)) > q) {
        string ans;
        getline(user, ans);
        if (ans != "The truth is out there") {
            fail();
        }
    } else {
        long long p[n][n];
        for (int i = 0; i < n; i++) {
            user>>p[0][i];
            if (p[0][i] < 1 || p[0][i] > q) {
                fail();
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                p[i][j] = p[i - 1][j] + p[i - 1][j + 1];
            }
        }
        if (p[n - 1][0] != q) {
            fail();
        }
    }

    accept();
}
