Hiitism is a popular art movement in Hiitsburgh. In Hiitism, the paintings only use three colors, Honeydew, Indigo, and Teal. The canvas is divided into a number of rows and columns, and each brushstroke has to color either one column or one row with single color. A shady figure wants to sell you a painting that he claims to be Hiitist. Can you figure out if that's true?

# Input

The first line of the input has two integers $n$ and $m$, describing the height and the width of the painting.

The following $n$ lines have strings of length $m$, describing each row of the canvas. The colors Honeydew, Indigo, and Teal are denoted by 'H', 'I', and 'T', and an unpainted part of a canvas by '.'.

# Output

Output a sequence of brushstrokes that would produce the given painting or state that it is impossible by outputting "Impossible". If such a sequence of brushstrokes exists, first write the number of brushstrokes and then three values for each brushstroke: whether we paint a row ('R') or a column ('C'), its index, and the color of the brushstroke.

# Constraints

- $1 \le n, m \le 1000$
- You may use at most $10^5$ brushstrokes. 

# Example

Input:
```
3 3
.H.
IHI
TTT
```

Output:
```
3
R 2 I
C 2 H
R 3 T
```

The painting from the example is illustrated below. Unpainted parts of the canvas are colored in a light shade of brown.

![Example of a Hiitist painting.](<files/painting.png>)
