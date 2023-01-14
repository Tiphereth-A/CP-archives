INF = 1145141919810
n, k = map(str, input().split())
k = int(k)
graph = [[], [], [], [], [], [], [], [], [], []]
for i in range(0, 10):
    graph[i] = [INF for j in range(0, 10)]
    graph[i][i] = 1
for i in range(0, k):
    x, y = map(int, input().split())
    graph[x][y] = 1
for k in range(0, 10):
    for i in range(0, 10):
        for j in range(0, 10):
            graph[i][j] = min(graph[i][j], graph[i][k] +
                              graph[k][j])if j else INF
num = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0]
for i in range(0, 10):
    for j in range(0, 10):
        num[i] += 1 if graph[i][j] < INF else 0
ans = 1
for ch in n:
    ans *= num[int(ch)]
print(ans)
