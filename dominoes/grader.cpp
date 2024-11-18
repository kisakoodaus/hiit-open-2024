#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define pii pair<int, int>

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

    string s;
    correct>>s;
    if (s == "Impossible") {
        string t;
        user>>t;
        if (t != "Impossible") fail();
        accept();
    }

    int n;
    input>>n;
    pii p1[n];
    pii p2[n];
    for (int i = 0; i < n; i++) {
        int x, y;
        input>>x>>y;
        p1[i] = {x, y};
    }

    int pr = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        user>>x>>y;
        if (pr == x) fail();
        pr = y;
        p2[i] = {x, y};
    }
    sort(p1, p1 + n);
    sort(p2, p2 + n);
    for (int i = 0; i < n; i++) {
        if (p1[i].first != p2[i].first || p1[i].second != p2[i].second) fail();
    }

    accept();
}
