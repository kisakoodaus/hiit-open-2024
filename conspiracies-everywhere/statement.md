You suspect that the pyramids were built by aliens. A pyramid is a structure consisting of $n$ layers of stones such that the $i\text{th}$ layer of stones from the top has $i$ stones in it. You observe that the quality of the building materials increases the higher the stones are, with the topmost stone having quality $q$. If aliens had built the pyramids, you believe that the qualities of the stones would be positive integers such that the quality of a stone is exactly the sum of the qualities of the two stones below it. Can you find the qualities of the stones in the bottom layer of a given pyramid to prove that aliens built them?

# Input

The only line of the input has two integers $n$ and $q$.

# Output

Print any valid way to choose the stone qualities in the bottom layer. If there are no solutions, print "The truth is out there".

# Constraints

- $1 \le n \le 60$
- $1 \le q \le 10^{18}$

# Example 1

Input:
```
3 8
```

Output:
```
2 1 4
```

Explanation: the qualities of the stones are
```
  8
 3 5
2 1 4
```

# Example 2

Input:
```
2 1
```

Output:
```
The truth is out there
```
