n = int(input())
s = ''
if len(list(filter(lambda x: x != '9', str(n)))) == 0:
    s = '1'*len(str(n))*9
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
