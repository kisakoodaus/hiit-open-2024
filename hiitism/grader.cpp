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

    string possible;
    correct>>possible;
    string output;
    user>>output;
    if (possible == "Impossible" && possible != output) {
        fail();
    }
    if (output == "Impossible" && possible != output) {
        fail();
    }
    if (output == "Impossible") {
        accept();
    }
    int width, height;
    input>>height>>width;
    char c[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) c[i][j] = '.';
    }
    int m;
    try {
        m = stoi(output);
    } catch (const std::invalid_argument& e) {
        fail();
    } catch (const std::out_of_range& e) {
        fail();
    }
    if (m < 0 || m > 100000) fail();

    while (m --> 0) {
        try {
            char t, col;
            int i = 0;
            user>>t>>i>>col;
            if (col != 'H' && col != 'I' && col != 'T') fail();
            if (t != 'R' && t != 'C') fail();
            i--;
            if (t == 'R') {
                if (i < 0 || i >= height) fail();
                for (int j = 0; j < width; j++) c[i][j] = col;
            } else {
                if (i < 0 || i >= width) fail();
                for (int j = 0; j < height; j++) c[j][i] = col;
            }
        } catch (const std::invalid_argument& e) {
            fail();
        } catch (const std::out_of_range& e) {
            fail();
        }
    }
    for (int i = 0; i < height; i++) {
        string line;
        input>>line;
        for (int j = 0; j < width; j++) {
            if (line[j] != c[i][j]) fail();
        }
    }
    accept();
}
