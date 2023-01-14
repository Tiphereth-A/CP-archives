n = int(input())
if n == 1:
    print(1)
else:
    d = [0, 0, 1]
    for i in range(3, n + 1):
        d .append((i - 1)*(d[i - 1]+d[i - 2]))
    print(d[n])
