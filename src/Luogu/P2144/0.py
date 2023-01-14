n = int(input())
if n == 1:
    print(1)
elif n == 2:
    print(5)
else:
    x1, x2, x = 1, 5, 16
    for i in range(2, n):
        x = 3 * x2 - x1 + 2
        x1, x2 = x2, x
    print(x)
