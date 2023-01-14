n = int(input())
b = n ** n
a = 1
for i in range(1, n + 1):
    a *= i
a = a ** 2
print(a / b)
