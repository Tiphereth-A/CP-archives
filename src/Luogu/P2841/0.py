n = int(input())
s = ''
_ = str(n).count('9')
if _ == len(str(n)):
    s = '1'*_ *9
elif n % 2 == 0 or n % 5 == 0:
    p, s = 2, '10'
    while int(s) % n:
        p += 2
        s = bin(p)[2:]
else:
    p, s = 1, '1'
    while int(s) % n:
        p += 1
        s = bin(p)[2:]
print(int(s)//n, s)
