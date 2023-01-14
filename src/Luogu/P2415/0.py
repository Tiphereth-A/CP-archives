sum = 0
n = -1
for i in map(int, input().split()):
    sum += i
    n += 1
print(2 ** n * sum)
