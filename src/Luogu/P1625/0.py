from math import gcd, factorial
n, m = map(int, input().split())
a = factorial(m + n - 1)
p = sum([factorial(i)*a // factorial(i + m)for i in range(0, n)])
g = gcd(p, a)
print(p // g)
print(a // g)
