You are playing with dominoes. Each domino tile can be represented as a pair of two distinct numbers between $1$ and $6$. You want to build a long chain of domino tiles without rotating them such that all adjacent numbers are distinct. Can you put all domino tiles into this chain?

# Input

The first line of the input contains the integer $n$, the number of domino tiles.

The following $n$ lines contain two distinct integers between $1$ and $6$, describing each domino tile.

# Output

If a solution exists, output $2n$ numbers on a single line describing the sequence of numbers in the chain.

Otherwise, output "Impossible".

# Constraints

- $1 \le n \le 10^5$

# Example

Input:
```
3
1 2
1 2
2 3
```

Output:
```
2 3 1 2 1 2
```
