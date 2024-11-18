You want to help your grandparents build a fence at their summer cottage. You went to a store to purchase materials for that, but you forgot to measure how long the fence is going to be. Fortunately, you still remember the general shape of the fence and that the sections of the fence are aligned either horizontally or vertically on a map. To figure out the total length, you call to your grandparents and ask them to take the measurements for you, but to avoid disturbing them too much, you want to minimize the number of sections whose lengths they need to measure.

# Input

The only line of the input has a string describing the shape of the fence. From the starting point, you first go some distance left ('L'), right ('R'), up ('U'), or down ('D'), then continue to the direction indicated by the second character, and so on. The path ends back at the starting point.  

# Output

Output the minimum number of measurements your grandparents need to take.

# Constraints

- The length of the string is at most $10^6$.

# Example

Input:
```
ULDRUR
```

Output:
```
2
```

The fence from the example is illustrated below.

![Illustration of the example](files/fence.png)
