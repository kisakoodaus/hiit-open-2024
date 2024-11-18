#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

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

vector<pair<int,int>> bv[1000];
int bc[1000][1000];
int bz[1000];

void dfs(int w, int x, int a, int b) {
    if (bz[x]) return;
    bz[x] = 1;
    bc[w][x]++;
    for (auto u : bv[x]) {
        if (u.second == a || u.second == b) continue;
        dfs(w, u.first, a, b);
    }
}

void brute3(graph g) {
    int n = g.size();
    for (int i = 0; i < n; i++) bv[i].clear();
    int m = 0;
    for (int i = 0; i < n; i++) {
        for (auto x : g.neighbors[i]) {
            if (i < x) {
                bv[i].push_back({x,m});
                bv[x].push_back({i,m});
                m++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bc[i][j] = 0;
        }
    }
    int c = 0;
    for (int a = 0; a < m; a++) {
        for (int b = a+1; b < m; b++) {
            c++;
            for (int x = 0; x < n; x++) {
                for (int s = 0; s < n; s++) bz[s] = 0;
                dfs(x, x, a, b);
            }
        }
    }
    if (c == 0) {
        for (int i = 0; i < n; i++) bc[i][i] = 1;
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bc[i][j] = bc[i][j] == c;
        }
    }
}

int main(int argc, char **argv)
{

    int tc = 0;
    while (true) {
        tc++;
        cout << "new test " << tc << "\n";
        int n = rand()%25+1;
        int p = rand()%100;
        graph g(n);
        vector<pair<int,int>> v;
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (rand()%100 <= p) {
                    g.add_edge(i, j);
                    v.push_back({i,j});
                }
            }
        }

        auto c = components3(g);
        brute3(g);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (bc[i][j] != (c[i] == c[j])) {
                    cout << n << " " << v.size() << "\n";
                    for (auto e : v) {
                        cout << e.first << " " << e.second << "\n";
                    }
                    cout << "fail\n";
                    cout << i << " " << j << " " << bc[i][j] << " " << (c[i] == c[j]) << "\n";
                    return 0;
                }
            }
        }
    }
}
