#include <bits/stdc++.h>
const int N = 1e6 + 5;
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
  int to, next;
} e[N * 2];
int head[N], cnt, ans;
bool vis[N] = {1, 1};
void add(int u, int v) {
  e[++cnt] = {v, head[u]};
  head[u] = cnt;
}
void dfs(int p) {
  for (int i = head[p]; i; i = e[i].next) {
    int v = e[i].to;
    if (!vis[v]) {
      vis[v] = 1;
      dfs(v);
      ++ans;
    }
  }
}
int main() {
  int n = read(), m = read();
  for (int p, q, i = 1; i <= m; ++i) {
    p = read();
    q = read();
    add(p, q);
  }
  dfs(1);
  printf("%d", ans);
  return 0;
}
