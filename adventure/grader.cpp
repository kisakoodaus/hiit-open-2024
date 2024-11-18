#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <set>

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

struct edge
{
    int a, b;

    bool operator==(const edge &rhs) const noexcept
    {
        return a == rhs.a && b == rhs.b;
    }
};

template <>
struct std::hash<edge>
{
    std::size_t operator()(const edge &e) const noexcept
    {
        return (2435234 * e.a) ^ (3251234 * e.b);
    }
};

int check_cycle_and_count_colors(const std::unordered_map<edge, std::bitset<128>> &graph, std::ifstream &input)
{
    std::vector<int> nodes;
    {
        int node;
        while (input >> node)
            nodes.push_back(node);
    }
    // A simple cycle must be at least a triangle
    if (nodes.size() < 3)
        fail();

    // All nodes must be unique
    std::set<int> nodes_set(nodes.begin(), nodes.end());
    if (nodes_set.size() != nodes.size())
        fail();

    // Close the cycle
    nodes.push_back(nodes.front());

    std::bitset<128> used_colors; // Extra bits to avoid off-by-one errors :D

    for (size_t i = 1; i < nodes.size(); i++)
    {
        int a = nodes[i - 1];
        int b = nodes[i];
        if (b < a)
            std::swap(a, b);
        auto cit = graph.find({a, b});
        if (cit == graph.end())
            fail(); // Tried to use non-existent edge
        used_colors |= cit->second;
    }

    return used_colors.count();
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

    std::unordered_map<edge, std::bitset<128>> graph;
    int n, m;
    SAFE_READ(input >> n >> m);
    for (int i = 0; i < m; i++)
    {
        int a, b, color_count;
        SAFE_READ(input >> a >> b >> color_count);
        std::bitset<128> mask;
        while (color_count-- > 0)
        {
            int c;
            SAFE_READ(input >> c);
            mask.set(c);
        }

        if (b < a)
            std::swap(a, b);
        graph[{a, b}] = mask;
    }

    int optimal_colors = check_cycle_and_count_colors(graph, correct);
    int user_colors = check_cycle_and_count_colors(graph, user);

    std::cerr << "User uses " << user_colors << ", optimal uses " << optimal_colors << std::endl;

    // Check that the solution is indeed a 2-approximation
    if (2 * optimal_colors < user_colors)
        fail();

    accept();
}
