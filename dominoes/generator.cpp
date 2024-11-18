#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main(int argc, char **argv)
{
    if (argv[1][0] == 'M') {
        int n = stoi(argv[2]);
        cout<<n<<endl;
        for (int i = 1; i <= n; i++) {
            cout<<stoi(argv[2 * i + 1])<<" "<<stoi(argv[2 * i + 2])<<endl;
        }
    } else if (argv[1][0] == 'G') {
        int k = stoi(argv[2]);
        int n = stoi(argv[3]);
        srand(time(0) + k + n + k * n);
        int p[] = {1, 2, 3, 4, 5, 6};
        random_shuffle(p, p + 6);
        cout<<n<<endl;
        for (int i = 0; i < n; i++) {
            int x = p[rand() % k];
            int y = p[rand() % k];
            while (x == y) y = p[rand() % k];
            cout<<x<<" "<<y<<endl;
        }
    } else {
        cerr<<"Check generator.cpp..."<<endl;
        exit(1);
    }
}
