#include <bits/stdc++.h>
#define int long long
const int N = 2e5 + 5, M = 4e5 + 5;
int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    (x *= 10) += c - '0';
    c = getchar();
  }
  return x * f;
}
struct edge {
  int to, next, val;
} e[M * 4];
int head[N], cnt;
void add(int u, int v, int val) {
  e[++cnt] = {v, head[u], val};
  head[u] = cnt;
}
bool vis[N];
int dis[N];
struct node {
  int val, now;
  bool operator<(const node &a) const { return val > a.val; }
};
std::priority_queue<node> pq;
void dij(int from) {
  memset(dis, 0x3f, sizeof(dis));
  dis[from] = 0;
  pq.push({0, from});
  while (!pq.empty()) {
    node now = pq.top();
    pq.pop();
    int u = now.now;
    if (vis[u]) continue;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].to;
      if (dis[u] + e[i].val < dis[v]) {
        dis[v] = dis[u] + e[i].val;
        pq.push({dis[v], v});
      }
    }
  }
}
signed main() {
  int n = read(), m = read(), k = read(), x = read(), y = read();
  for (int a, b, c, i = 1; i <= m; ++i) {
    a = read();
    b = read();
    c = read();
    add(a, b, c);
    add(b, a, c);
  }
  for (int a, b, i = 1; i <= k; ++i) {
    a = read();
    b = read();
    add(a, b, 0);
  }
  dij(x);
  printf("%lld", dis[y]);
  return 0;
}
