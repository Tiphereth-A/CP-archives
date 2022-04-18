def get_inv(a):
    res = 1
    b = 19260815
    while b != 0:
        if (b % 2 == 1):
            res = res * a % 19260817
        a = a * a % 19260817
        b = b // 2
    return res % 19260817


a = int(input())
b = int(input())
if b == 0:
    print('Angry!')
else:
    print(a * get_inv(b) % 19260817)
