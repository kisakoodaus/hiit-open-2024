#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>
#include <list>
#include <set>

// Give numerical grade to the user
[[noreturn]] void grade(int result)
{
    std::cout << "1\n"
              << result << '\n';
    exit(0);
}
// Indicate that program failed to produce the right answer
[[noreturn]] void fail()
{
    std::cout << "0\n";
    exit(0);
}
// Indicate that the submission was accepted
[[noreturn]] void accept()
{
    std::cout << "1\n";
    exit(0);
}
#define SAFE_READ(x) \
    do               \
    {                \
        if (!(x))    \
            fail();  \
    } while (false)

struct graph
{
    std::vector<std::vector<size_t>> neighbors;

    graph(size_t n) : neighbors(n) {}

    void add_edge(size_t u, size_t v)
    {
        neighbors[u].push_back(v);
        neighbors[v].push_back(u);
    }

    size_t size() const
    {
        return neighbors.size();
    }
};

struct connectivity
{
    std::vector<std::pair<size_t, size_t>> jumps;

    connectivity(size_t n) : jumps(n)
    {
        for (size_t i = 0; i < n; i++)
            jumps[i] = {i, 0};
    }

    size_t find(size_t v)
    {
        if (jumps[v].first == v)
            return v;
        return jumps[v].first = find(jumps[v].first);
    }

    size_t join(size_t u, size_t v)
    {
        u = find(u);
        v = find(v);

        if (jumps[u].second < jumps[v].second)
        {
            jumps[u].first = v;
            return v;
        }
        else if (jumps[v].second < jumps[u].second)
        {
            jumps[v].first = u;
            return u;
        }
        else
        {
            jumps[u].first = v;
            jumps[v].second++;
            return v;
        }
    }

    std::vector<size_t> to_vector() const
    {
        std::vector<size_t> components(jumps.size());
        for (size_t i = 0; i < jumps.size(); i++)
        {
            components[i] = jumps[i].first;
        }
        std::function<size_t(size_t)> fc = [&](size_t i)
        {
            if (components[i] == i)
                return i;
            return components[i] = fc(components[i]);
        };
        for (size_t i = 0; i < jumps.size(); i++)
        {
            size_t root = fc(i);
            if (root > i)
            {
                components[root] = i;
                components[i] = i;
                root = i;
            }
        }

        return components;
    }
};

// Compute connected components
std::vector<size_t> components(const graph &g)
{
    const size_t n = g.size();
    connectivity con(n);

    for (size_t v = 0; v < n; v++)
    {
        for (size_t u : g.neighbors[v])
        {
            con.join(v, u);
        }
    }

    return con.to_vector();
}

// Compute 3-edge-connected components
std::vector<size_t> components3(const graph &g)
{
    const size_t n = g.size();
    constexpr size_t sentinel = size_t(-1);

    size_t count = 1;
    std::vector<size_t> next(n, sentinel);
    connectivity con(n);
    std::vector<std::list<size_t>> l_bar(n);
    std::vector<size_t> pre(n, sentinel);
    std::vector<size_t> last_pre(n, sentinel);
    std::vector<size_t> lowpt(n, sentinel);

    std::function<size_t(size_t, size_t, size_t, size_t)> absorb_path = [&](size_t x0, size_t p, size_t start, size_t end)
    {
        while (pre[x0] < pre[p] && pre[p] <= start && end <= last_pre[p])
        {
            l_bar[x0].splice(l_bar[x0].end(), l_bar[p]);
            con.join(x0, p);
            p = next[p];
        }
        return p;
    };

    std::function<void(size_t, size_t, size_t)> dfs = [&](size_t w, size_t v, size_t d)
    {
        lowpt[w] = last_pre[w] = pre[w] = ++count;
        next[w] = w;
        bool parent_seen = false;

        for (size_t u : g.neighbors[w])
        {
            if (u == v && !parent_seen)
            {
                parent_seen = true;
                continue; // Don't use the parent edge
            }
            if (pre[u] == sentinel)
            {
                // u has not been visited before
                dfs(u, w, d + 1);
                last_pre[w] = count;

                size_t u_path = u;

                // 1.1
                size_t degree = 1;

                if (pre[next[u]] != lowpt[u])
                    degree++; // u has a successor in P path
                for (auto it = l_bar[u].begin(); it != l_bar[u].end() && degree <= 3;)
                {
                    if (pre[u] <= pre[*it])
                    {
                        // Self loop, or an outdated self loop
                        it = l_bar[u].erase(it);
                    }
                    else
                    {
                        // Back edge
                        it++;
                        degree++;
                    }
                }
                if (lowpt[u] == pre[u])
                {
                    // (w, u) is a bridge
                    continue;
                }
                if (degree == 2)
                {
                    // TODO: Remove (w, u) from the graph
                    l_bar[w].splice(l_bar[w].end(), l_bar[u]);
                    u_path = next[u];
                }

                if (lowpt[w] <= lowpt[u])
                {
                    // 1.3
                    absorb_path(w, u_path, -1, 0);
                }
                else
                {
                    lowpt[w] = lowpt[u];
                    // 1.4
                    absorb_path(w, next[w], -1, 0);
                    next[w] = u_path;
                }
            }
            else if (pre[w] > pre[u])
            {
                // (w, u) is an outgoing back-edge of w
                l_bar[w].push_back(u); // From extended explanation
                if (pre[u] < lowpt[w])
                {
                    // 1.5
                    absorb_path(w, next[w], -1, 0);
                    lowpt[w] = pre[u];
                    next[w] = u;
                }
            }
            else if (pre[w] < pre[u])
            {
                // 1.6
                next[w] = absorb_path(w, next[w], pre[u], last_pre[u]);
            }
            else
            {
                assert(false);
            }
        }
    };

    for (size_t w = 0; w < n; w++)
    {
        if (lowpt[w] != sentinel)
            continue; // This component has been handled already
        dfs(w, -1, 1);
    }

    return con.to_vector();
}

int main(int argc, char **argv)
{
    std::string x1 = argv[1]; // correct output
    std::string x2 = argv[2]; // user output
    std::string x3 = argv[3]; // input
    std::ifstream correct, user, input;
    correct.open(x1);
    user.open(x2);
    input.open(x3);

    std::set<std::pair<long long, long long>> edges;

    long long n, m;
    SAFE_READ(input >> n >> m);
    graph input_g(n);
    for (long long i = 0; i < m; i++)
    {
        long long x, y;
        SAFE_READ(input >> x >> y);
        if (x == y)
            fail();
        if (x < 1 || x > n)
            fail();
        if (y < 1 || y > n)
            fail();
        x--;
        y--;
        input_g.add_edge(x, y);
        edges.insert({x, y});
    }

    std::set<std::pair<long long, long long>> user_edges;
    graph user_g(n);
    SAFE_READ(user >> m);
    if (m > 3 * n)
        fail();
    for (long long i = 0; i < m; i++)
    {
        long long x, y;
        SAFE_READ(user >> x >> y);
        if (x == y)
            fail();
        if (x < 1 || x > n)
            fail();
        if (y < 1 || y > n)
            fail();
        x--;
        y--;
        if (!edges.count({x, y}) && !edges.count({y, x}))
            fail();
        if (user_edges.count({x, y}) || user_edges.count({y, x}))
            fail();
        user_edges.insert({x, y});
        user_g.add_edge(x, y);
    }

    // Start by checking the components are the same
    if (components(input_g) != components(user_g))
        fail();

    // Then check that the 3-edge-connected components are the same
    if (components3(input_g) != components3(user_g))
        fail();

    accept();
}