f = [0, 1]
n = int(input())
for i in range(n + 2):
    f .append(f[-2]+f[-1])
if n == 0:
    print("0")
else:
    print(f[n + 1])
