#!/usr/bin/env python3

n = int(input())

equilateral = [(i*i - i) // 2 for i in range(1414215)]

def twosum(l, t):
    a = 0
    b = len(l)-1
    while a < b:
        while l[a] + l[b] < t: a += 1
        while l[a] + l[b] > t: b -= 1
        if l[a] + l[b] == t: return True
    return False

if n in equilateral:
    print(1)
elif twosum(equilateral, n):
    print(2)
else:
    print(3)
