#include <iostream>
#include <vector>

int main()
{
    // Naïve solution. Should not pass.
    long long n;
    std::cin >> n;
    long long tau = 6'283'185'307;
    long long cur = 0;
    std::vector<std::pair<long long, long long>> segments;
    while ((cur + 1) * 1'000'000'000 < n * tau)
    {
        segments.push_back({cur, cur + 1});
        cur += 2;
    }

    for (size_t i = 0; i < segments.size(); i++)
    {
        std::cout << segments[i].first << "/1 " << segments[i].second << "/1\n";
    }
}
