from math import ceil, sqrt, factorial
n = int(input())
if n <= 4:
    print(n)
    print(n)
    exit(0)
end = ceil((sqrt(8 * n + 9)-1)/2)
k = (end - 1)*(end + 2)//2 - n
if k != 1:
    for j in range(2, end + 1):
        if j != k:
            print(j, end=' ')
    print(end='\n')
    print(factorial(end)//(k if k <= end and k >= 2 else 1))
else:
    for j in range(3, end):
        print(j, end=' ')
    print(end + 1, end='\n')
    print(factorial(end - 1)*(end + 1)//2)
