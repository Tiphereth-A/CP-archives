n = int(input())
s = set([])
s .add(n)
while True:
    n = str(int(str(n + 1)[::-1]))[::-1]
    n = int(n)if n else 0
    if n in s:
        print(len(s))
        break
    else:
        s .add(n)
