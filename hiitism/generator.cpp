#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator width height brushstrokes random_pixels random_empty seed" << endl;
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
    if (argc != 7)
        usage();

    // Parse arguments into numbers
    int width = stoi(argv[1]);
    int height = stoi(argv[2]);
    if (width == 3) {
        cout<<"3 3\n.H.\nIHI\nTTT"<<endl;
        return 0;
    }
    if (width == 2) {
        cout<<"2 2\n.H\nIH"<<endl;
        return 0;
    }

    int bs = stoi(argv[3]);
    int rp = stoi(argv[4]);
    int re = stoi(argv[5]);
    int seed = stoi(argv[6]);
    r_dev.seed(seed);
    r_dev64.seed(seed);
    char out[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            out[i][j] = '.';
        }
    }
    while (bs --> 0) {
        int r = coin();
        char c = rnd(0, 3) ? (coin() ? 'H' : 'I') : 'T';
        if (r) {
            int j = rnd(0, width - 1);
            for (int i = 0; i < height; i++) {
                out[i][j] = c;
            }
        } else {
            int i = rnd(0, height - 1);
            for (int j = 0; j < width; j++) {
                out[i][j] = c;
            }
        }
    }

    while (rp --> 0) {
        int i = rnd(0, height - 1);
        int j = rnd(0, width - 1);
        char c = rnd(0, 3) ? (coin() ? 'H' : 'I') : 'T';
        out[i][j] = c;
    }

    while (re --> 0) {
        int i = rnd(0, height - 1);
        int j = rnd(0, width - 1);
        out[i][j] = '.';
    }

    cout<<height<<" "<<width<<endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout<<out[i][j];
        }
        cout<<endl;
    }
}
