You are visiting Hiitland, a country with $n$ states and $m$ two-way connections between them. When you arrive to one of the states from another state, you need to present certain legal documents at the border control. More precisely, there are $64$ legal documents that are used in Hiitland, and passing each border check requires some specific subset of them.

Your travel plan consists of three steps. First, you arrive to some state by an airplane and stay there at a hotel. Then, you visit some other states, at least three states in total. Finally, you return back to the state where your hotel is and fly back home. Traveling to the same state multiple times is boring, so you would never do that, apart from returning the state you started from and flying home. Further, obtaining the legal documents is a hassle, so you plan your trip such that the number of legal documents you have to gather is not significantly larger than it has to be. That is, if a travel plan can be made with some number of legal documents, you want to gather at most twice that many documents.

# Input

The first line has two integers, $n$ and $m$.

The following $m$ lines start with three numbers, $v$, $u$ and $c$, describing that the you need $c$ documents to travel between states $v$ and $u$. The line continues by $c$ integers describing the needed documents.

# Output

Output the states you visit on your trip in the order you visit them. After the last state, you return to the state you started from and fly back home.

# Constraints

- $3 \le n \le m \le 1000$
- Each document is numbered by an integer between $1$ and $64$
- There's at most one connection between two states.

# Example

Input:
```
5 6
1 2 1 1
2 3 1 2
3 4 1 3
4 5 1 2
5 2 1 3
5 1 1 2
```

Output:
```
2 5 1
```

Explanation: You fly to state 2, then travel to state 5, which requires document 3. Then you continue your trip to state 1, requiring document 2. Finally, you return back to state 2, which requires document 1. There exists a travel plan for which only two legal documents are needed, so obtaining three documents is not too many.
