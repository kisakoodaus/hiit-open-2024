#!/usr/bin/env python3

n, m = map(int, input().split())
neighbors = [[] for i in range(n)]
for i in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    neighbors[a].append(b)
    neighbors[b].append(a)


def dfs(v, visited, res):
    visited.add(v)
    for u in neighbors[v]:
        if u in visited: continue
        if (v, u) in res or (u, v) in res: continue
        res.add((v, u))
        dfs(u, visited, res)

res = set()
for c in range(3):
    visited = set()
    for i in range(n):
        if i not in visited:
            dfs(i, visited, res)

print(len(res))
print("\n".join(f"{a+1} {b+1}" for a, b in res))

