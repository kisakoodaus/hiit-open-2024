#!/usr/bin/env python3

from pysmt.shortcuts import Symbol, And, Equals, Int, Or, Plus, Solver
from pysmt.typing import INT
import sys

n, m = map(int, input().split())
edges = []
for i in range(m):
    vals = map(int, input().split())
    a = next(vals)
    b = next(vals)
    next(vals)
    c = map(lambda x: x - 1, vals)

    # if b < a: a, b = b, a
    edges.append((a - 1, b - 1, c))

color_selectors = [Symbol(f"c{c+1}", INT) for c in range(64)]
edge_selectors = [Symbol(f"e{a+1}_{b+1}", INT) for a,b,c in edges]
# vertex_selectors = [Symbol(f"v{i}", INT) for i in range(n)]


formula = []

# Each selector is either 0 or 1
for s in edge_selectors + color_selectors:
    formula.append(And(Int(0) <= s, s <= Int(1)))

# Each edge can be active only if the corresponding color is active
for es, e in zip(edge_selectors, edges):
    a, b, c = e
    for cc in c:
        formula.append(es <= color_selectors[cc])

# Each vertex can have only 0 or 2 adjacent edges
vertex_neighbors = [[] for _ in range(n)]
for i, e in enumerate(edges):
    vertex_neighbors[e[0]].append(i)
    vertex_neighbors[e[1]].append(i)
for i in range(n):
    ns = [edge_selectors[e] for e in vertex_neighbors[i]]
    s = Plus(ns)
    formula.append(Or(Equals(s, Int(0)), Equals(s, Int(2))))

# At least one edge is selected
formula.append(Plus(edge_selectors) > Int(0))

# print(And(formula))

with Solver(name="z3") as solver:
    solver.add_assertion(And(formula))

    if not solver.solve():
        print("Something is horribly wrong!")
        exit()
    for colors in range(65):
        if solver.solve([Plus(color_selectors) <= Int(colors)]):
            print(f"Solvable with {colors} colors", file=sys.stderr)

            # for s in edge_selectors:
            #     print(f"{s} = {solver.get_value(s)}")

            # Extract the solution
            edges_used = set()
            for es, e in zip(edge_selectors, edges):
                if solver.get_py_value(es) > 0:
                    edges_used.add(e)

            first_edge = next(iter(edges_used))
            prev = first_edge[0]
            cur = first_edge[1]
            cycle = [cur]
            first = cur
            while True:
                neighbor_edges = [e for e in edges_used if e[0] == cur or e[1] == cur]
                assert len(neighbor_edges) == 2
                next_edge = next(e for e in neighbor_edges if e[0] != prev and e[1] != prev)
                next_node = next_edge[1] if next_edge[0] == cur else next_edge[0]
                if next_node == first:
                    break
                cycle.append(next_node)
                prev, cur = cur, next_node

            print(" ".join(str(node + 1) for node in cycle))

            break
        else:
            print(f"Not solvable with {colors} colors", file=sys.stderr)
