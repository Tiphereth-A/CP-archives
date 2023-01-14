import itertools
from math import gcd
a, b = 1, 1
input()
for i in map(int, input().split()):
    a *= i
input()
for i in map(int, input().split()):
    b *= i
print(str(gcd(a, b))[-9:])
