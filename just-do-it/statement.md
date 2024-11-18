Your colleague at Hiitsburgh Inversion Innovation Technologies has come up with the following sorting algorithm:

```c
// Sort an array. Initialize with low = 0 and high = len(array)
algorithm HiitSort(array, low, high)
    if high - low > 1
        pivot <- median(array[low], array[(low + high) / 2], array[high - 1])

        a <- low
        b <- high - 1
        loop
            while array[a] < pivot      // (*)
                a <- a + 1
            while array[b] > pivot      // (*)
                b <- b - 1
            if a >= b
                break loop
            swap(array[a], array[b])
            a <- a + 1
            b <- b - 1

        call HiitSort(array, low, a)
        call HiitSort(array, a, high)
```

Your colleague claims that their algorithm uses only $O(n \log n)$ comparisons against the pivot in total. You are sceptical of this claim and want to prove them wrong. In particular, you want to find an array of $n$ distinct elements such that the algorithm makes at least $n^2 / 4$ comparison operations against the pivot.

For the purposes of this exercise, we are only interested in the comparisons against the pivot, that is the comparisons executed on lines 9 and 11 of the code above (marked with `(*)` in the code).

The array is 0-indexed and the division operator rounds down. Function `median` returns the value that is the median of the three arguments; it does not count towards comparisons.

# Input

The input contains a single integer $n$, the number of elements in the array.

# Constraints

- $2 \le n \le 1000$

# Output

The output contains $n$ distinct integers from range $[1, n]$, the array to be sorted.

# Example

Input:
```
3
```

Output:
```
1 2 3
```

Explanation: The array takes $7$ operations to sort, which is more than $3^2 / 4 = 2 \frac{1}{4}$.

Input:
```
5
```

Output:
```
1 2 4 3 5
```

Explanation: The array takes $17$ operations to sort, which is more than $5^2 / 4 = 4 \frac{1}{4}$.
