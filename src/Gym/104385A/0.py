t = int(input())
for i in range(t):
    a, b, c = map(int, input().split())
    print(1 if a <= b * c else 0)
