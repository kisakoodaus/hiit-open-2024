#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef std::pair<long long, unsigned long long> sum_mask;

bool is_solution_in_range(const std::vector<sum_mask> &s1, const std::vector<sum_mask> &s2, long long minv, long long maxv)
{
    long long count = 0;
    // Keep track of range range in first vector and a single element in the second
    auto s1b = s1.begin();
    auto s1e = s1.begin();
    for (auto s2i = s2.rbegin(); s2i < s2.rend(); s2i++)
    {
        while (s1b != s1.end() && s1b->first + s2i->first < minv)
            s1b++;
        while (s1e != s1.end() && s1e->first + s2i->first < maxv)
            s1e++;
        count += std::distance(s1b, s1e);
    }

    return count > maxv - minv;
}

std::vector<sum_mask> sum_tables(const std::vector<long long> &input, int shift = 0)
{
    std::vector<sum_mask> sums;
    int n = input.size();
    for (unsigned long long m = 0; m < (1ull << n); m++)
    {
        unsigned long long mask = m;
        long long s = 0;
        int i = 0;
        while (mask)
        {
            if (mask & 1)
                s += input[i];
            i++;
            mask >>= 1;
        }
        sums.push_back({s, m << shift});
    }
    std::sort(sums.begin(), sums.end());
    return sums;
}

void print_masked(const std::vector<long long> &input, unsigned long long mask)
{
    bool is_first = true;
    int i = 0;
    while (mask)
    {
        if (mask & 1)
        {
            if (!is_first)
            {
                std::cout << " ";
            }
            std::cout << input[i];
            is_first = false;
        }
        i++;
        mask >>= 1;
    }
    std::cout << "\n";
}

int main()
{
    int n = 0;
    std::cin >> n;
    std::vector<long long> input;
    for (int i = 0; i < n; i++)
    {
        long long x;
        std::cin >> x;
        input.push_back(x);
    }

    std::vector<long long> h1, h2;
    for (int i = 0; i < n / 2; i++)
        h1.push_back(input[i]);
    for (int i = n / 2; i < n; i++)
        h2.push_back(input[i]);

    auto s1 = sum_tables(h1);
    auto s2 = sum_tables(h2, h1.size());

    long long start = 1;
    long long step = (1ll << n) - 2; // One past the end
    while (step > 0)
    {
        while (!is_solution_in_range(s1, s2, start, start + step))
            start += step;
        step /= 2;
    }

    // Find the values that sum to start
    std::vector<unsigned long long> res;
    auto s1i = s1.begin();
    for (auto s2i = s2.rbegin(); s2i < s2.rend(); s2i++)
    {
        while (s1i != s1.end() && s1i->first + s2i->first < start)
            s1i++;
        if (s1i != s1.end() && s1i->first + s2i->first == start)
        {
            res.push_back(s1i->second | s2i->second);
        }
        if (res.size() >= 2)
            break;
    }
    assert(res.size() >= 2);
    unsigned long long m1 = res[0];
    unsigned long long m2 = res[1];
    // Remove the set of same elements from the result
    unsigned long long inter = m1 & m2;
    m1 &= ~inter;
    m2 &= ~inter;

    assert(m1 != 0);
    assert(m2 != 0);

    print_masked(input, m1);
    print_masked(input, m2);
}
