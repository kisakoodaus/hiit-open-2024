The city of Hiitsburgh consists of $n$ islands. In the past, people of Hiitsburgh have travelled between the islands by boats, but now the city wants to modernize and connect its islands by bridges. However, the budget for the project is limited, and so the bridges should be built in such a way that it minimizes the total cost while enabling travel between any pair of islands. The city council has received a report describing the cost of building a bridge between some pairs of islands and is now discussing which bridges should be built. Some council members are lobbying for certain bridges to be included to the plan, but there are concerns that this would increase the total cost of the project. Can you help the city council to figure out if the given sets of bridges can be included so that the islands can still be connected with minimum cost?

# Input

The first line of the input has three integers $n$, $m$, and $k$, the number of islands, the number of possible bridges, and the number of plans the council members have.

The following $m$ lines have three integers $v$, $w$, and $c$, stating that the cost of building a bridge between islands $v$ and $w$ is $c$. Each pair of islands appears at most once.

Finally, there are descriptions of the plans of the council members. The first line of the plan has a single integer $b$, describing the number of bridges in the plan. The following $b$ lines have two integers $v$ and $w$, meaning that we must build a bridge between islands $v$ and $w$. The islands $v$ and $w$ are in the same order as when the possible bridges were described. 

# Output

For each plan, output either "YES" or "NO" depending on whether there exists a minimum-cost solution that connects all islands and contains the desired bridges.

# Constraints

- $1 \le n, m, k \le 2 \cdot 10^5$
- You may assume that building all bridges connects all islands.
- The costs of the bridges are at most $10^9$.
- The sum of all $b$ is at most $2 \cdot 10^5$.

# Example

Input:
```
3 3 2
1 2 1
1 3 1
2 3 2
1
1 2
2
1 3
2 3
```

Output:
```
YES
NO
```

Explanation: For the first plan, we can build a bridge between islands $1$ and $2$ and islands $1$ and $3$, resulting in a total cost of $2$. For the second plan, the cost is at least $3$. 