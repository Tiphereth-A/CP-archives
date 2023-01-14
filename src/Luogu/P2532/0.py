n = int(input())
ans = 1
for i in range(n + 1, 2 * n + 1):
    ans = ans * i
for i in range(1, n + 1):
    ans = ans // i
print(ans // (n + 1))
