#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>
#include <list>
#include <random>

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

size_t max_flow(const graph &g, size_t s, size_t t)
{
    const size_t n = g.neighbors.size();
    std::vector<std::unordered_map<size_t, size_t>> out_edges(n);
    for (size_t u = 0; u < n; u++)
    {
        for (size_t v : g.neighbors[u])
        {
            out_edges[u][v] = 1;
        }
    }

    std::vector<std::pair<size_t, size_t>> visited(n);
    std::queue<size_t> q;
    size_t gen = 1;
    q.push(s);
    visited[s] = {gen, s};
    size_t flow = 0;
    while (!q.empty())
    {
        size_t u = q.front();
        q.pop();
        // std::cerr << "At " << u << "\n";
        for (auto [v, w] : out_edges[u])
        {
            // std::cerr << " n " << v << " " << w << "\n";
            if (!w)
                continue;
            if (v == t)
            {
                // std::cerr << " found\n";
                flow++;
                size_t prev = v;
                size_t cur = u;
                do
                {
                    out_edges[cur][prev]--;
                    out_edges[prev][cur]++;
                    prev = cur;
                    assert(visited[cur].first == gen);
                    cur = visited[cur].second;
                } while (prev != s);
                gen++;
                while (!q.empty())
                    q.pop();
                q.push(s);
                visited[s] = {gen, s};
                break;
            }
            if (visited[v].first == gen)
                continue;
            visited[v] = {gen, u};
            q.push(v);
        }
    }

    return flow;
}

std::vector<size_t> components_max_flow(const graph &g)
{
    const size_t n = g.neighbors.size();
    connectivity con(n);
    for (size_t u = 0; u < n; u++)
    {
        for (size_t v = 0; v < u; v++)
        {
            if (con.find(u) == con.find(v))
                continue;
            // std::cerr << u << " -> " << v << " flow " << max_flow(g, u, v) << std::endl;
            if (max_flow(g, u, v) >= 3)
                con.join(u, v);
        }
    }
    return con.to_vector();
}

std::ostream &operator<<(std::ostream &s, const std::vector<size_t> &v)
{
    for (auto a : v)
        s << " " << a;
    return s;
}

std::vector<size_t> components(const graph &g)
{
    const size_t n = g.neighbors.size();
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
        // std::cerr << "Absorbing (" << start << ", " << end << ") " << x0 << " <-";
        while (pre[x0] < pre[p] && pre[p] <= start && end <= last_pre[p])
        {
            // std::cerr << " " << p << "(" << pre[p] << ", " << last_pre[p] << ")";
            // TODO: Check the condition
            l_bar[x0].splice(l_bar[x0].end(), l_bar[p]);
            con.join(x0, p);
            p = next[p];
        }
        return p;
    };

    std::function<void(size_t, size_t, size_t)> dfs = [&](size_t w, size_t v, size_t d)
    {
        // std::cerr << "dfs " << w << " " << v << std::endl;
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
                // std::cerr << "Tree-edge " << w << " " << u << std::endl;
                // u has not been visited before
                dfs(u, w, d + 1);
                last_pre[w] = count;

                size_t u_path = u;

                // 1.1
                size_t degree = 1;

                // std::cerr << "Degree check values " << pre[next[u]] << " " << lowpt[u] << std::endl;
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
                        // std::cerr << "Found back edge " << w << " " << *it << std::endl;
                        // Back edge
                        it++;
                        degree++;
                    }
                }
                // std::cerr << "Node " << u << " has degree " << degree << std::endl;
                if (lowpt[u] == pre[u])
                {
                    // (w, u) is a bridge
                    // std::cerr << "This is a bridge. Ignoring" << std::endl;
                    continue;
                }
                if (degree == 2)
                {
                    // std::cerr << "Ejecting " << u << std::endl;
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
                    // std::cerr << "Setting next of " << w << " to be " << u_path << std::endl;
                }
            }
            else if (pre[w] > pre[u])
            {
                // std::cerr << "Outgoing back-edge " << w << " " << u << std::endl;
                // (w, u) is an outgoing back-edge of w
                l_bar[w].push_back(u); // From extended explanation
                if (pre[u] < lowpt[w])
                {
                    // 1.5
                    absorb_path(w, next[w], -1, 0);
                    lowpt[w] = pre[u];
                    next[w] = u;
                    // std::cerr << "Setting next of " << w << " to be " << u << std::endl;
                }
            }
            else if (pre[w] < pre[u])
            {
                // std::cerr << "Incoming back-edge " << w << " " << u << std::endl;
                // 1.6
                next[w] = absorb_path(w, next[w], pre[u], last_pre[u]);
                // std::cerr << "Setting next of " << w << " to be " << next[w] << std::endl;
            }
            else
            {
                assert(false);
            }
        }

        // std::cerr << "end dfs " << w << " " << lowpt[w] << std::endl;
    };

    for (size_t w = 0; w < n; w++)
    {
        if (lowpt[w] != sentinel)
            continue; // This component has been handled already
        dfs(w, -1, 1);
    }

    return con.to_vector();
}

bool has_bridge(const graph &g)
{
    const size_t n = g.neighbors.size();
    std::vector<size_t> pre(n), lowpt(n);
    size_t count = 1;
    std::function<bool(size_t, size_t)> dfs = [&](size_t w, size_t v)
    {
        lowpt[w] = pre[w] = count++;
        for (size_t u : g.neighbors[w])
        {
            if (u == v)
                continue; // Skip parent
            if (pre[u])
            {
                // u visited
                lowpt[w] = std::min(lowpt[w], pre[u]);
                continue;
            }
            if (dfs(u, w))
                return true;
            lowpt[w] = std::min(lowpt[w], lowpt[u]);
            if (lowpt[u] > pre[w])
                return true; // (w, u) is a bridge
        }
        return false;
    };

    for (size_t w = 0; w < n; w++)
    {
        if (pre[w])
            continue; // This component has been handled already
        if (dfs(w, -1))
            return true;
    }

    return false;
}

int main(int argc, char **argv)
{

    // graph h(4);
    // h.add_edge(0, 1);
    // h.add_edge(0, 2);
    // h.add_edge(1, 2);
    // h.add_edge(1, 3);
    // h.add_edge(2, 3);
    // std::cout<<max_flow(h, 0, 3)<<std::endl;

    graph h(4);
    h.add_edge(0, 1);
    h.add_edge(0, 2);
    h.add_edge(0, 3);
    h.add_edge(1, 2);
    h.add_edge(1, 3);
    // components_max_flow(h);
    // std::cout << max_flow(h, 0, 3) << std::endl;
    std::cerr << components(h) << std::endl;
    // return 0;
    // const size_t n = 5;
    // Iterate over all graphs of n nodes
    // for (size_t s = 0; s < (1 << (n * n)); s++)
    // {
    //     graph g(n);
    //     for (size_t u = 0; u < n; u++)
    //         for (size_t v = u + 1; v < n; v++)
    //             if (s & (1 << (u * n + v)))
    //                 g.add_edge(u, v);
    //     // if (has_bridge(g))
    //     //     continue;
    //     // for (size_t u = 0; u < n; u++)
    //     // {
    //     //     std::cout << u << ":";
    //     //     for (size_t v : g.neighbors[u])
    //     //         std::cout << " " << v;
    //     //     std::cout << std::endl;
    //     // }
    //     auto c1 = components_max_flow(g);
    //     auto c2 = components(g);
    //     if (c1 != c2)
    //     {
    //         std::cout << "Error! " << s << std::endl;

    //         for (size_t c : c1)
    //             std::cout << " " << c;
    //         std::cout << std::endl;
    //         for (size_t c : c2)
    //             std::cout << " " << c;
    //         std::cout << std::endl;
    //     }
    // }

    // const size_t n = 20;
    // size_t counter = 0;
    // std::mt19937 r_dev;
    // std::uniform_int_distribution<size_t> e_dist(0, n - 1);
    // while (true)
    // {
    //     counter++;
    //     if (counter % 1'000 == 0)
    //         std::cerr << counter << std::endl;
    //     graph g(n);
    //     std::set<std::pair<size_t, size_t>> edges;
    //     for (size_t e = 0; e < 3 * n; e++)
    //     {
    //     retry:
    //         size_t x = e_dist(r_dev);
    //         size_t y = e_dist(r_dev);
    //         if (x == y)
    //             goto retry;
    //         if (edges.count({x, y}))
    //             goto retry;
    //         edges.insert({x, y});
    //         edges.insert({y, x});
    //         g.add_edge(x, y);
    //     }
    //     // if (has_bridge(g))
    //     //     continue;
    //     // for (size_t u = 0; u < n; u++)
    //     // {
    //     //     std::cout << u << ":";
    //     //     for (size_t v : g.neighbors[u])
    //     //         std::cout << " " << v;
    //     //     std::cout << std::endl;
    //     // }
    //     auto c1 = components_max_flow(g);
    //     auto c2 = components(g);
    //     if (c1 != c2)
    //     {
    //         std::cout << "Error!" << std::endl;
    //         if (has_bridge(g))
    //             std::cout << "Bridges detected" << std::endl;
    //         for (size_t u = 0; u < n; u++)
    //         {
    //             std::cout << u << ":";
    //             for (size_t v : g.neighbors[u])
    //                 std::cout << " " << v;
    //             std::cout << std::endl;
    //         }

    //         for (size_t c : c1)
    //             std::cout << " " << c;
    //         std::cout << std::endl;
    //         for (size_t c : c2)
    //             std::cout << " " << c;
    //         std::cout << std::endl;
    //         return 1;
    //     }
    // }

    const size_t n = 8;
    // Iterate over all graphs of n nodes
    for (size_t s = 0; s < (1 << ((n * n - n) / 2)); s++)
    {
        graph g(n);
        size_t i = 0;
        for (size_t u = 0; u < n; u++)
            for (size_t v = u + 1; v < n; v++)
                if (s & (1 << i++))
                    g.add_edge(u, v);
        assert(i == (n * n - n) / 2);
        if (has_bridge(g))
            continue;
        // for (size_t u = 0; u < n; u++)
        // {
        //     std::cout << u << ":";
        //     for (size_t v : g.neighbors[u])
        //         std::cout << " " << v;
        //     std::cout << std::endl;
        // }
        auto c1 = components_max_flow(g);
        auto c2 = components(g);
        if (c1 != c2)
        {
            std::cout << "Error! " << s << std::endl;
            for (size_t u = 0; u < n; u++)
            {
                std::cout << u << ":";
                for (size_t v : g.neighbors[u])
                    std::cout << " " << v;
                std::cout << std::endl;
            }

            for (size_t c : c1)
                std::cout << " " << c;
            std::cout << std::endl;
            for (size_t c : c2)
                std::cout << " " << c;
            std::cout << std::endl;
        }
    }

    // std::string x1 = argv[1]; // correct output
    // std::string x2 = argv[2]; // user output
    // std::string x3 = argv[3]; // input
    // std::ifstream correct, user, input;
    // correct.open(x1);
    // user.open(x2);
    // input.open(x3);

    // // Write grader here
    // // Remember to add this to the Makefile, otherwise the default grader will
    // be used

    // accept();
}