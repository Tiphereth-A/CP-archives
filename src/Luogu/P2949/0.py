from collections import defaultdict
from heapq import heappush, heappop
a = defaultdict(list)
for _ in range(int(input())):
    d, p = map(int, input().split())
    a[d].append(p)
ans = 0
q = []
l = sorted(a .keys(), reverse=True)
for i, j in zip(l, l[1:]+[0]):
    for k in a .pop(i):
        heappush(q, ~k)
    for _ in range(i - j):
        if q:
            ans += ~heappop(q)
        else:
            break
print(ans)
