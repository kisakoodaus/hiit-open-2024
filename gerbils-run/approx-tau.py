#!/usr/bin/env python3

from fractions import Fraction
from math import log10

# Pi with 100 decimals, according to Wikipedia
pi = Fraction(31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679, 10**100)
tau = 2*pi

def approx_lb(denom):
    return Fraction(int(tau*denom), denom)

def approx_ub(denom):
    return Fraction(int(tau*denom+1), denom)

def status(lb, ub, i):
    lbd = -log10(float((tau - lb) / tau))
    ubd = -log10(float((ub - tau) / tau))
    print(f"{str(lb):>25} ({lbd:3.1f}) - {str(ub):25} ({ubd:3.1f}) ({i})")


best_lb = Fraction(6283185307, 10**9)
best_ub = Fraction(6283185308, 10**9)
assert best_lb <= tau
assert best_ub >= tau
for i in range(1, 10**9):
    lb = approx_lb(i)
    ub = approx_ub(i)
    assert lb <= tau
    assert ub >= tau
    if lb > best_lb:
        best_lb = lb
        #print(f"New lb: {str(lb):>20} - {str(ub):20} ({i})")
        status(best_lb, best_ub, i)
    if ub < best_ub:
        best_ub = ub
        status(best_lb, best_ub, i)
        #print(f"New ub: {str(lb):>20} - {str(ub):20} ({i})")

