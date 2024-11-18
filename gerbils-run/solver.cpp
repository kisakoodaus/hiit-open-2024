#include <iostream>
#include <cassert>

int main()
{
    long long n;
    std::cin >> n;
    long long tau = 6'283'185'307;
    // Use one-millionth-size units everywhere
    long long circle_length = n * tau / 1000;

    // Fill everything with unit-length segments, except for the last couple of units.
    long long pos = 0;
    for (; pos + 6000000 < circle_length; pos += 2000000)
    {
        std::cout << pos << "/1000000 " << pos + 1000000 << "/1000000\n";
    }

    // There's [4, 6) units of space left. We need to leave a gap of size [1, 2].
    long long gap = circle_length - pos;
    assert(gap >= 4000000 && gap < 6000000);
    if (gap <= 5000000)
    {
        // Just continue
        for (; pos + 1000000 < circle_length; pos += 2000000)
        {
            std::cout << pos << "/1000000 " << pos + 1000000 << "/1000000\n";
        }
    } else {
        // Add a longer gap already here
        pos += 1000000;
        for (; pos + 1000000 < circle_length; pos += 2000000)
        {
            std::cout << pos << "/1000000 " << pos + 1000000 << "/1000000\n";
        }
    }
}
