class Node:
    def __init__(self, a, b):
        self .a = a
        self .b = b

    def __lt__(self, rhs):
        return max(rhs .b, self .a * self .b) < max(self .b, rhs .a * rhs .b)


if __name__ == '__main__':
    n = int(input())
    king = Node(*map(int, input().split()))
    ministers = []
    for i in range(n):
        ministers .append(Node(*map(int, input().split())))
    ministers .sort()
    ans, prod = 0, king .a
    for i in ministers:
        now = prod // i .b
        if now > ans:
            ans = now
        prod *= i .a
    print(ans)
