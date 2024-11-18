#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#include <utility>

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::map<std::pair<int, int>, unsigned long long> edges;
    std::vector<std::vector<int>> neighbors(n);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        a--;
        b--;
        unsigned long long mask = 0;
        while (c-- > 0)
        {
            int d;
            std::cin >> d;
            d--;
            mask |= 1ull << d;
        }
        edges[{a, b}] = mask;
        edges[{b, a}] = mask;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }

    std::vector<int> visited(n * n, -1);
    typedef std::tuple<int, int, int, int, unsigned long long> elem;
    std::priority_queue<elem, std::vector<elem>, std::greater<elem>> q;
    for (int i = 0; i < n; i++)
        q.push({0, i, i, i, 0});
    while (!q.empty())
    {
        auto [colors, start, prev, cur, mask] = q.top();
        q.pop();

        if (visited[start * n + cur] != -1)
        {
            // Collect the two paths starting from the current node. Those are the result.
            std::vector<int> p1, p2;
            int p = cur;
            while (p != visited[start * n + p])
            {
                p1.push_back(p);
                p = visited[start * n + p];
            }
            p = prev;
            while (p != visited[start * n + p])
            {
                p2.push_back(p);
                p = visited[start * n + p];
            }
            // Remove the equal tails from both paths
            while (p1.back() == p2.back())
            {
                start = p1.back();
                p1.pop_back();
                p2.pop_back();
            };

            // Remove the last start node and append the second path to the first
            // p2.pop_back();
            std::reverse(p2.begin(), p2.end());
            p1.push_back(start);
            for (int e : p2)
                p1.push_back(e);

            auto it = p1.begin();
            std::cout << *it++ + 1;
            for (; it < p1.end(); it++)
                std::cout << " " << *it + 1;
            std::cout << "\n";
            return 0;
        }
        visited[start * n + cur] = prev;

        for (int neighbor : neighbors[cur])
        {
            if (neighbor == prev)
                continue;
            unsigned long long m2 = mask | edges[{cur, neighbor}];
            q.push({__builtin_popcountll(m2), start, cur, neighbor, m2});
        }
    }

    // This should never be reached
    return 1;
}
