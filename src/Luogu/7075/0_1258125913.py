import math
for i in range(0, int(input())):
    Z = int(input())
    a = math .floor((Z - 2305507.25)/36524.25)
    A = Z if Z < 2299161 else Z + 10 + a - math .floor(a / 4)
    k = 0
    while True:
        B = A + 1524
        C = math .floor((B - 122.1)/365.25)
        D = math .floor(365.25 * C)
        E = math .floor((B - D)/30.6)
        day = B - D - math .floor(30.6 * E)
        if day >= 1:
            break
        A -= 1
        k += 1
    month = E - (1 if E < 14 else 13)
    year = C - (4716 if month > 2 else 4715)
    day += k
    if day == 0:
        day = 1
    print("{} {} {}".format(day, month, str(year)
                            if year >= 1 else str(-year + 1)+" BC"))
