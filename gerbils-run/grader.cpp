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

struct safe_uint128
{
    unsigned __int128 val;
    safe_uint128(unsigned __int128 v) : val(v) {}

    bool operator<(const safe_uint128 &rhs) const
    {
        return val < rhs.val;
    }

    bool operator<=(const safe_uint128 &rhs) const
    {
        return val <= rhs.val;
    }

    bool operator>(const safe_uint128 &rhs) const
    {
        return val > rhs.val;
    }

    bool operator>=(const safe_uint128 &rhs) const
    {
        return val >= rhs.val;
    }

    safe_uint128 operator+(const safe_uint128 &rhs) const
    {
        unsigned __int128 res;
        if (__builtin_add_overflow(val, rhs.val, &res))
            exit(1);
        return res;
    }

    safe_uint128 operator*(const safe_uint128 &rhs) const
    {
        unsigned __int128 res;
        if (__builtin_mul_overflow(val, rhs.val, &res))
            exit(1);
        return res;
    }

    safe_uint128 operator/(const safe_uint128 &rhs) const
    {
        if (rhs.val == 0)
            exit(1);
        return val / rhs.val;
    }
};

std::ostream &operator<<(std::ostream &out, const safe_uint128 i)
{
    unsigned __int128 div = 1;
    for (int j = 0; j < 38; j++)
        div *= 10;
    while (i.val / div == 0)
        div /= 10;
    for (; div > 0; div /= 10)
    {
        out << int((i.val / div) % 10);
    }
    return out;
}

safe_uint128 gcd(safe_uint128 a, safe_uint128 b)
{
    if (b.val == 0)
        return a;
    return gcd(b.val, a.val % b.val);
}

struct quotient
{
    safe_uint128 numerator, denominator;

    quotient() : numerator(0), denominator(1)
    {
    }

    quotient(safe_uint128 val) : numerator(val), denominator(1)
    {
    }

    quotient(safe_uint128 n, safe_uint128 d) : numerator(n), denominator(d)
    {
        safe_uint128 div = gcd(n, d);
        numerator = numerator / div;
        denominator = denominator / div;
    }

    bool operator<(const quotient &rhs) const
    {
        return numerator * rhs.denominator < rhs.numerator * denominator;
    }

    bool operator<=(const quotient &rhs) const
    {
        return numerator * rhs.denominator <= rhs.numerator * denominator;
    }

    bool operator>(const quotient &rhs) const
    {
        return numerator * rhs.denominator > rhs.numerator * denominator;
    }

    bool operator>=(const quotient &rhs) const
    {
        return numerator * rhs.denominator >= rhs.numerator * denominator;
    }

    quotient operator+(const quotient &rhs) const
    {
        return {
            numerator * rhs.denominator + rhs.numerator * denominator,
            denominator * rhs.denominator};
    }

    quotient operator*(const quotient &rhs) const
    {
        return {
            numerator * rhs.numerator,
            denominator * rhs.denominator};
    }
};

std::ifstream &operator>>(std::ifstream &in, quotient &q)
{
    std::string s;
    in >> s;
    if (!in)
        return in;
    size_t split = s.find('/');
    if (split == std::string::npos)
        fail();
    unsigned long long n = stoull(s.substr(0, split));
    unsigned long long d = stoull(s.substr(split + 1));
    if (d == 0)
        fail();
    if (d > 1000000)
        fail();
    q = {n, d};
    return in;
}

std::ostream &operator<<(std::ostream &out, const quotient &q)
{
    return out << q.numerator << "/" << q.denominator;
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

    unsigned n;
    input >> n;

    // Lower and upper approximation of 2π with sufficiently many bits (33).
    // This should be enough to get accurate results, and low enough not to
    // overflow numbers:
    // Addition, multiplication and comparison each double the number of bits
    // in the worst case. As a special case, adding an integer does not affect
    // the number of bits.
    //
    // The numerator of user's input can contain at most 33 bits:
    // (1000 * 2π * 10^6).
    // The denominator fits in 20. So (33, 20) bits in the worst case.
    //
    // The largest operations in this grader are the aliasing operators: adding
    // users input and a multiple of pi, and then comparing these numbers.
    // The length of the circle requires (43, 30) bits and the user's input
    // (33, 20) bits. Their sum requires (63, 50) bits. Comparing them then
    // requires 113 bits, which fits in 128 bits.
    // quotient tau_lb(6'283'185'307, 1'000'000'000);
    // quotient tau_ub(6'283'185'308, 1'000'000'000);
    quotient tau_lb(4687425571, 746026950); // 18.5 decimals
    quotient tau_ub(2549491779, 405764219); // 18.8 decimals

    std::vector<std::pair<quotient, quotient>> segments;
    while (true)
    {
        quotient a, b;
        if (!(user >> a >> b))
            break;
        if (b <= a)
        {
            std::cerr << "Invalid: " << a << " " << b << "\n";
            fail(); // Segments must be well-formed
        }
        if (b > quotient(n) * tau_ub)
        {
            std::cerr << "Aliases over 0: " << b << "\n";
            fail(); // All segments must lie on the unaliased circle.
        }
        segments.push_back({a, b});
    }
    if (segments.size() > 100'000)
        fail();

    std::sort(segments.begin(), segments.end());

    // First ensure that no segment is longer than 1 unit. Otherwise you
    // starting from one endpoint and moving one unit would land you in the
    // same segment.
    for (auto s : segments)
    {
        if (s.first + quotient(1) < s.second)
        {
            std::cerr << "Too long segment: " << s.first << " " << s.second << "\n";
            fail();
        }
    }

    // Then make sure that the segments, along with their aliases around 0/2π,
    // shifted by 1 unit to right are disjoint from the original. This can be
    // done by taking the union of segments and their shifts, and making sure
    // that all of them are disjoint. If they are not, then either two segments
    // intersect, which is a contradiction, or a segment and a shift of a
    // segment intersect, in which case jumping 1 unit from the intersecting
    // part of the segment to the left would lead to another segment, which is
    // again a contradiction. Finally, as the test is symmetric between the
    // segments and their shifts, and the set contains the aliases of each
    // segment, jumps to right and jumps over the split are also captured.
    {
        std::vector<std::pair<quotient, quotient>> aliased;
        for (auto s : segments)
        {
            aliased.push_back(s);
            aliased.push_back({s.first + quotient(1), s.second + quotient(1)});

            // Be careful to add tau_ub to the lower end and tau_lb to the
            // higher end to ensure that the aliased versions never exceed what
            // they should.
            aliased.push_back({s.first + quotient(n) * tau_ub, s.second + quotient(n) * tau_lb});
            aliased.push_back({s.first + quotient(n) * tau_ub + quotient(1), s.second + quotient(n) * tau_lb + quotient(1)});
        }

        std::sort(aliased.begin(), aliased.end());

        for (size_t i = 1; i < aliased.size(); i++)
        {
            auto prev = aliased[i - 1];
            auto cur = aliased[i];
            if (prev.second > cur.first)
            {
                std::cerr << "Overlapping segments: (" << prev.first << " - " << prev.second << ") (" << cur.first << ", " << cur.second << ")\n";
                fail();
            }
        }
    }

    // Finally, make sure that you can get from any point not inside the
    // segments to outside. This can be ensured by taking the union of all
    // segments shifted to both left and right by 1 unit with the original
    // segments, along with their aliases, and making sure that this set covers
    // the whole circle. Now any point inside the segments is included as the
    // claim holds vacuously for them. Every point outside the original
    // segments needs to be covered by either the left or the right shift. If
    // not, then jumping from that point to either direction would still leave
    // you outside of the segments.
    {
        std::vector<std::pair<quotient, quotient>> aliased;
        for (auto s : segments)
        {
            // In practice, instead of adding [-1, 0, 1], we shift everything
            // by one and add [0, 1, 2].
            aliased.push_back(s);
            aliased.push_back({s.first + quotient(1), s.second + quotient(1)});
            aliased.push_back({s.first + quotient(2), s.second + quotient(2)});

            // Unlike in the previous case, we now want to make sure that the
            // segments are never smaller than they should be to ensure that
            // the solution covers the whole circle.
            aliased.push_back({s.first + quotient(n) * tau_lb, s.second + quotient(n) * tau_ub});
            aliased.push_back({s.first + quotient(n) * tau_lb + quotient(1), s.second + quotient(n) * tau_ub + quotient(1)});
            aliased.push_back({s.first + quotient(n) * tau_lb + quotient(2), s.second + quotient(n) * tau_ub + quotient(2)});
        }

        // Order the segments by their starting points.
        std::sort(aliased.begin(), aliased.end());

        quotient lb(1);
        for (size_t i = 0; i < aliased.size(); i++)
        {
            auto cur = aliased[i];
            if (cur.first > quotient(1) + quotient(n) * tau_ub)
                break; // We have checked the whole circle.
            if (cur.first > lb)
            {
                std::cerr << "Gap: " << lb << " " << cur.first << "\n";
                fail(); // There is a gap!
            }
            lb = std::max(lb, cur.second);
        }
    }

    accept();
}
