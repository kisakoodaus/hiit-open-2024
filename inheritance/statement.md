You and your sister have received inheritance. Unfortunately, you are not on speaking terms with your sister, and you need to divide the inheritance evenly between you two. You may give some of the items to charity if you otherwise cannot split them evenly.

# Input

The first line has a single integer $n$ describing the number of items you have inherited.

The second line has $n$ positive integers describing the value of each individual item.

The total value of the items is at most $2^n - 2$.

# Output

If a solution exists, output two lines with the first describing the values of the items that you receive and the second line describing the values of items that your sister receives. Neither of you should receive zero items. The unlisted items are given to charity. If no solution exists, output "Impossible".

# Constraints

- $2 \le n \le 40$
- $1 \le \sum_{i=1}^{n} x_i \le 2^{n}-2$

# Example

Input:
```
6
3 2 5 1 7 8
```

Output:
```
3 2
5
```

Explanation: If you take items with values 3 and 2, and your sister takes the item with value 5, you both get equally valuable inheritances in total.