from datetime import *
from math import ceil
s, r = map(int, input().split())
print((datetime .now().replace(2000, 1, 1, 7, 50) -
       timedelta(minutes=ceil(s / r))).strftime('%H:%M'))
