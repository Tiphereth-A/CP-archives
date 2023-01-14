t = int(input())
for i in range(t):
    input()
    s = input().replace('100', 'j').replace('200', 't')
    for i in range(11, 20):
        s = s .replace(str(i * 10), chr(96 + i))
    for i in range(21, 27):
        s = s .replace(str(i * 10), chr(96 + i))
    for i in range(1, 10):
        s = s .replace(str(i), chr(96 + i))
    print(s)
