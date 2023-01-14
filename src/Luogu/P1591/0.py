from math import factorial
t = int(input())
for i in range(0, t):
    n, a = map(int, input().split())
    print(str(factorial(n)).count(str(a)))
