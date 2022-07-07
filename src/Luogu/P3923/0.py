import numpy as np
primes = (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
          61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
          149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
          239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337,
          347, 349)
prime_polys = {
    4: np .array([1, 1, 1], dtype=int),
    8: np .array([1, 0, 1, 1], dtype=int),
    9: np .array([1, 0, 1], dtype=int),
    16: np .array([1, 0, 0, 1, 1], dtype=int),
    25: np .array([1, 1, 1], dtype=int),
    27: np .array([1, 2, 1, 1], dtype=int),
    81: np .array([1, 0, 1, 1, 1], dtype=int),
    121: np .array([1, 1, 1], dtype=int),
    125: np .array([1, 0, 1, 1], dtype=int),
    128: np .array([1, 0, 0, 0, 0, 0, 1, 1], dtype=int),
    143: np .array([1, 1, 1], dtype=int),
    169: np .array([1, 1, 2], dtype=int),
    243: np .array([1, 0, 1, 3, 1, 1], dtype=int),
    256: np .array([1, 0, 0, 1, 0, 1, 0, 1, 1], dtype=int),
    343: np .array([1, 3, 1, 1], dtype=int)
}
polys = [np .array([0], dtype=int)]


def add(p, i, j):
    return np .polyval(np .polyadd(polys[i], polys[j]) % p, p)


def mul(p, k, i, j):
    conv = np .convolve(polys[i], polys[j])
    pp = prime_polys[p ** k]
    if conv .shape[0] >= pp .shape[0]:
        conv = np .polydiv(conv, pp)[1]
    return int(np .polyval(conv % p, p))


n = int(input())
prime = 0
cnt = 0
for i in primes:
    if n % i == 0:
        nn = n
        prime = i
        while nn % i == 0:
            nn = nn // i
            cnt = cnt + 1
        if nn != 1:
            print(-1)
            exit()
        break
print(0)
if cnt == 1:
    for i in range(0, n):
        for j in range(0, n):
            print((i + j) % n, end=(''if j == n - 1 else ' '))
        print()
    for i in range(0, n):
        for j in range(0, n):
            print((i * j) % n, end=(''if j == n - 1 else ' '))
        print()
else:
    for i in range(1, n):
        poly_i = []
        while i != 0:
            poly_i .append(i % prime)
            i = i // prime
        poly_i .reverse()
        polys .append(np .array(poly_i, dtype=int))
    res = np .zeros((n, n), dtype=int)
    for i in range(0, n):
        for j in range(i, n):
            res[i][j] = res[j][i] = add(prime, i, j)
    for i in range(0, n):
        for j in range(0, n):
            print(res[i][j], end=(''if j == n - 1 else ' '))
        print()
    for i in range(0, n):
        for j in range(i, n):
            res[i][j] = res[j][i] = mul(prime, cnt, i, j)
    for i in range(0, n):
        for j in range(0, n):
            print(res[i][j], end=(''if j == n - 1 else ' '))
        print()
