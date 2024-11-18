#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <set>
#include <cassert>

using namespace std;

[[noreturn]] void usage()
{
    cerr << "Usage: ./generator [seed] cycle [cycle length] [cycle colors] [max edges]" << endl;
    cerr << "Usage: ./generator [seed] ccycle [cycle length] [cycle colors] [max edges]" << endl;
    cerr << "Usage: ./generator [seed] lcycle" << endl;
    cerr << "Usage: ./generator [seed] lcycle2" << endl;
    cerr << "Usage: ./generator [seed] cycle-cycle [cycle count] [cycle colors] [min colors]" << endl;
    cerr << "Usage: ./generator [seed] lattice [width] [height] [colors]" << endl;
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

struct graph
{
    size_t vertex_count;
    std::set<std::pair<std::pair<size_t, size_t>, std::vector<size_t>>> edges;

    graph() : graph(0) {}

    graph(size_t n) : vertex_count(n) {}

    size_t add_node()
    {
        return vertex_count++;
    }

    void add_edge(size_t u, size_t v, std::vector<size_t> c)
    {
        edges.insert({{u, v}, c});
    }
};

void print_graph_shuffled(const graph &g, bool shuf = true)
{
    std::vector<size_t> renaming(g.vertex_count);
    for (size_t i = 0; i < renaming.size(); i++)
        renaming[i] = i + 1;
    if (shuf)
        shuffle(renaming);

    std::vector<size_t> color_renaming(64);
    for (size_t i = 0; i < color_renaming.size(); i++)
        color_renaming[i] = i + 1;
    if (shuf)
        shuffle(color_renaming);

    std::vector<std::tuple<size_t, size_t, std::vector<size_t>>> lines;
    for (auto [e, c] : g.edges)
    {
        size_t a = e.first;
        size_t b = e.second;
        if (coin())
            std::swap(a, b);
        std::vector<size_t> cols = c;
        for (auto &d : cols)
            d = color_renaming[d];
        lines.push_back({renaming[a], renaming[b], cols});
    }
    if (shuf)
        shuffle(lines);

    std::cout << g.vertex_count << " " << g.edges.size() << "\n";
    for (auto [a, b, c] : lines)
    {
        std::cout << a << " " << b << " " << c.size();
        for (auto d : c)
            std::cout << " " << d;
        std::cout << "\n";
    }
}

// void build_path(graph &g, size_t a, size_t b, std::vector<size_t> colors)
// {
//     assert(!colors.empty());
//     for (size_t i = 0; i < colors.size(); i++)
//     {
//         size_t next = i < colors.size() - 1 ? g.add_node() : b;
//         g.add_edge(a, next, colors[i]);
//         a = next;
//     }
// }

std::vector<size_t> range(size_t a, size_t b, size_t mod = 64)
{
    std::vector<size_t> res(b - a);
    for (size_t i = 0; i < b - a; i++)
        res[i] = (a + i) % mod;
    return res;
}

std::vector<size_t> logrange(size_t idx, size_t shift, bool complement)
{
    const size_t lmask = 1 << idx;
    const size_t umask = 2 << idx;
    std::vector<size_t> res;
    for (size_t i = 0; i < 64; i++)
    {
        if (((i & (1 << (5 - idx))) != 0) ^ complement)
            res.push_back((i + shift) % 64);
    }

    return res;
}

int main(int argc, char **argv)
{
    // Check argument count
    if (argc < 3)
        usage();

    // Parse arguments into numbers
    unsigned long long seed = stoull(argv[1]);
    r_dev.seed(seed);
    r_dev64.seed(seed);

    if (argv[2] == "cycle"s)
    {
        if (argc != 6)
            usage();

        unsigned long long cycle_length = stoull(argv[3]);
        unsigned long long cycle_colors = stoull(argv[4]);
        unsigned long long max_edges = stoull(argv[5]);

        graph g(cycle_length);
        for (size_t i = 0; i < cycle_length; i++)
        {
            g.add_edge(i, (i + 1) % cycle_length, {i < cycle_colors ? i % cycle_colors : rnd(0, cycle_colors - 1)});
        }

        while (g.edges.size() + 2 * cycle_colors + 1 <= max_edges)
        {
            size_t a = rnd(0, g.vertex_count - 1);
            size_t b = rnd(0, g.vertex_count - 1);
            std::vector<size_t> colors(2 * cycle_colors + 1);
            for (size_t i = 0; i < 2 * cycle_colors + 1; i++)
                colors[i] = i;
            shuffle(colors);

            // TODO: Add multiple colors on the edge
            for (size_t i = 0; i < 2 * cycle_colors; i++)
            {
                size_t d = g.add_node();
                g.add_edge(a, d, {colors[i]});
                a = d;
            }
            g.add_edge(a, b, {colors[2 * cycle_colors]});
        }

        print_graph_shuffled(g);
    }
    else if (argv[2] == "ccycle"s)
    {
        if (argc != 6)
            usage();

        unsigned long long cycle_length = stoull(argv[3]);
        unsigned long long cycle_colors = stoull(argv[4]);
        unsigned long long max_edges = stoull(argv[5]);

        graph g(cycle_length);
        for (size_t i = 0; i < cycle_length; i++)
        {
            g.add_edge(i, (i + 1) % cycle_length, {i < cycle_colors ? i % cycle_colors : rnd(0, cycle_colors - 1)});
        }

        while (g.edges.size() < max_edges)
        {
            size_t a = rnd(0, g.vertex_count - 1);
            size_t b = rnd(0, g.vertex_count - 1);
            if (a == b)
                continue;
            std::vector<size_t> colors(2 * cycle_colors + 1);
            for (size_t i = 0; i < 2 * cycle_colors + 1; i++)
                colors[i] = i;
            shuffle(colors);

            std::vector<size_t> colors1(colors.begin(), colors.begin() + (colors.end() - colors.begin()) / 2);
            std::vector<size_t> colors2(colors.begin() + (colors.end() - colors.begin()) / 2, colors.end());
            size_t n = g.add_node();
            g.add_edge(a, n, colors1);
            g.add_edge(n, b, colors2);
        }

        print_graph_shuffled(g);
    }
    else if (argv[2] == "cycle-cycle"s)
    {
        if (argc != 6)
            usage();

        unsigned long long cycle_count = stoull(argv[3]);
        unsigned long long cycle_colors = stoull(argv[4]);
        unsigned long long min_colors = stoull(argv[5]);

        if (cycle_colors % 2 != 0)
            usage();
        unsigned long long half_cycle_colors = cycle_colors / 2;

        graph g;

        // Construct small cycles
        size_t correct_side_colors = std::min(min_colors, half_cycle_colors);
        size_t side_length = half_cycle_colors + (half_cycle_colors - correct_side_colors);
        std::vector<std::pair<size_t, size_t>> small_cycles;
        for (size_t c = 0; c < cycle_count; c++)
        {
            size_t start = g.add_node();
            size_t end = g.add_node();

            std::vector<size_t> correct_colors(side_length);
            std::vector<size_t> incorrect_colors(side_length);
            for (size_t i = 0; i < side_length; i++)
            {

                correct_colors[i] = (i < correct_side_colors && min_colors <= half_cycle_colors) ? i : rnd(0, min_colors - 1);
                incorrect_colors[i] = cycle_colors - 1 - i;
            }
            shuffle(correct_colors);
            shuffle(incorrect_colors);

            // Correct side
            size_t prev = start;
            for (size_t i = 0; i < side_length; i++)
            {
                size_t node = i < side_length - 1 ? g.add_node() : end;
                g.add_edge(prev, node, {correct_colors[i]});
                prev = node;
            }
            // Incorrect side
            prev = start;
            for (size_t i = 0; i < side_length; i++)
            {
                size_t node = i < side_length - 1 ? g.add_node() : end;
                g.add_edge(prev, node, {incorrect_colors[i]});
                prev = node;
            }

            small_cycles.push_back({start, end});
        }

        // Connect the cycles into a big one
        for (size_t i = 0; i < small_cycles.size(); i++)
            g.add_edge(small_cycles[i].second, small_cycles[(i + 1) % cycle_count].first, {1});

        print_graph_shuffled(g);
    }
    else if (argv[2] == "lcycle"s)
    {
        if (argc != 3)
            usage();

        graph g;

        size_t start = g.add_node();
        size_t prev = start;

        for (size_t k = 0; k < 5; k++)
        {
            for (size_t i = 0; i < 16; i++)
            {
                size_t n = g.add_node();
                for (size_t j = 0; j < 6; j++)
                {
                    size_t a = g.add_node();
                    g.add_edge(prev, a, logrange(j, i, false));
                    g.add_edge(a, n, logrange(j, i, false));
                }
                prev = n;
            }
        }
        g.add_edge(prev, start, {1});

        print_graph_shuffled(g, false);
    }
    else if (argv[2] == "lcycle2"s)
    {
        if (argc != 3)
            usage();

        graph g;

        size_t start = g.add_node();
        size_t prev = start;

        for (size_t k = 0; k < 15; k++)
        {
            for (size_t i = 0; i < 16; i++)
            {
                size_t n = g.add_node();
                size_t a = g.add_node();
                size_t b = g.add_node();
                g.add_edge(prev, a, logrange(0, i, false));
                g.add_edge(a, n, logrange(0, i, false));
                auto foo = logrange(rnd(1, 5), i, coin());
                g.add_edge(prev, b, foo);
                g.add_edge(b, n, foo);
                prev = n;
            }
        }
        g.add_edge(prev, start, {1});

        print_graph_shuffled(g, false);
    }

    else if (argv[2] == "lattice"s || argv[2] == "lattice-shuffle"s)
    {
        if (argc != 6)
            usage();

        const bool shuf = argv[2] == "lattice-shuffle"s;
        const size_t width = stoull(argv[3]);
        const size_t height = stoull(argv[4]);
        const size_t colors = stoull(argv[5]);

        if (colors % 2 != 0)
            usage();

        graph g;

        std::vector<std::vector<size_t>> layers;
        for (size_t i = 0; i < height; i++)
        {
            std::vector<size_t> layer;
            for (size_t j = 0; j < width; j++)
                layer.push_back(g.add_node());
            layers.push_back(layer);
        }

        for (size_t i = 0; i < height - 1; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                size_t a = layers[i][j];
                size_t c = layers[i + 1][j];
                size_t d = layers[i + 1][(j + 1) % width];

                g.add_edge(a, c, range(i, colors / 2 + i, colors));
                g.add_edge(a, d, range(colors / 2 + i, colors + i, colors));
            }
        }

        print_graph_shuffled(g, shuf);
    }
    else
    {
        usage();
    }
}
