n, k = map(int, filter(lambda _: _, input().split()))
s = '1'+input()
f = [[0 for i in range(n + 1)]if j else [int(s[1:i + 1]if s[1:i + 1]else '0')
                                         for i in range(n + 1)]for j in range(k + 1)]
for kk in range(1, k + 1):
    for i in range(kk + 1, n + 1):
        for j in range(kk, i):
            f[kk][i] = max(f[kk][i], f[kk - 1][j]*int(s[j + 1:i + 1]))
print(f[k][n])
