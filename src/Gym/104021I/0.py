ss = input().split()
x, y = int(ss[0]), int(ss[1])
z = 0
for ch in ss[2]:
    z *= x
    z += ord(ch)-(48 if '0' <= ch <= '9'else 65 -
                  10 if 'A' <= ch <= 'Z'else 97 - 36)
s = ''
while z:
    tmp = z % y
    s = s + chr(tmp + (48 if tmp < 10 else 65 - 10 if tmp < 36 else 97 - 36))
    z //= y
if not s:
    s = '0'
print(s[::-1])
