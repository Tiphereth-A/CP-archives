import math
n = int(input())
for i in range(1, n + 1):
    s = input().split(" ")
    a = int(s[0], 16)
    b = int(s[1], 16)
    if a < b:
        tmp = a
        a = b
        b = tmp
    str_a = bin(a)[2:]
    str_b = bin(b)[2:]
    str_a = str_a[:len(str_b)]
    if str_a < str_b:
        tmp = str_a
        str_a = str_b
        str_b = tmp
    ans = ""
    for j in range(0, len(str_b)):
        if str_a[j] != str_b[j]:
            ans = str_a[:j]
            break
    if ans == "":
        ans = str_b
    print("Case #", i, ": ", hex(int(ans, 2))[2:], sep='')
    if i != n:
        print()
