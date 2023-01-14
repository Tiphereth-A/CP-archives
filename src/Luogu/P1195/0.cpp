#include <bits/stdc++.h>
using namespace std;
const int M = 5e5 + 5, N = 2e5 + 5;
struct Edge {
  int w, from, to;
  bool operator<(const Edge &other) const { return w < other.w; }
} e[M];
int cnt_edge;
void addEdge(int x, int y, int w = 1) { e[++cnt_edge] = {w, x, y}; }
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
long long kruskal(int n, int k = 1) {
  sort(e + 1, e + cnt_edge + 1);
  for (int i = 0; i <= n; ++i) fa[i] = i;
  int cnt = 0;
  long long ans = 0;
  for (int i = 1, fx, fy; i <= cnt_edge; ++i) {
    fx = find(e[i].from);
    fy = find(e[i].to);
    if (fx == fy) continue;
    fa[fx] = fy;
    ++cnt;
    ans += e[i].w;
    if (cnt == n - k) break;
  }
  if (cnt != n - k) throw "No Answer";
  return ans;
}
int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1, u, v, w; i <= m; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    addEdge(u, v, w);
  }
  try {
    printf("%lld", kruskal(n, k));
  } catch (const char *str) { puts(str); }
  return 0;
}
