# Give reasonably possible point scores for each task, one per line.
# Don't include 100 point scores, because we're mainly interested in how many
# sub-100 scores sum to a multiple of 100.
import sys
from collections import defaultdict
c = {0: 1}
for l in sys.stdin:
    points = [int(x) for x in l.split()]
    points = set([0] + points)
    nc = defaultdict(lambda: 0)
    for x in points:
        for y, yc in c.items():
            nc[x+y] += yc
    c = nc

print(sorted([(a, b) for a, b, in c.items() if b > 1], key=lambda x: (x[1], x[0]), reverse=True))
