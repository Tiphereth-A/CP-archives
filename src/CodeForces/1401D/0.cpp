#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, M = 2e6 + 5, MOD = 1e9 + 7;
struct Edge {
  i64 w;
  int from, to, next;
  bool operator<(const Edge &other) const { return w > other.w; }
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, i64 w = 0) {
  e[++cnt_edge] = {w, x, y, head[x]};
  head[x] = cnt_edge;
}
i64 p[N], cnt_nodes[N];
i64 init(int now, int fa) {
  for (int i = head[now], to; i; i = e[i].next) {
    to = e[i].to;
    if (to == fa) continue;
    cnt_nodes[now] += init(to, now);
  }
  return ++cnt_nodes[now];
}
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    memset(head, 0, sizeof(head[0]) * (n + 1));
    memset(cnt_nodes, 0, sizeof(cnt_nodes[0]) * (n + 1));
    cnt_edge = 0;
    for (int i = 1, x, y; i < n; ++i) {
      cin >> x >> y;
      addEdge(x, y);
      addEdge(y, x);
    }
    init(1, 1);
    int m;
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> p[i];
    for (int i = m + 1; i <= n; ++i) p[i] = 1;
    for (int i = 1; i <= cnt_edge; i += 2) {
      i64 _ = min(cnt_nodes[e[i].from], cnt_nodes[e[i].to]);
      e[i].w = _ * (n - _);
    }
    sort(e + 1, e + cnt_edge + 1);
    sort(p + 1, p + m + 1, greater<int>());
    i64 ans = 0;
    if (m > n - 1) {
      for (int i = 2; i <= m - n + 2; ++i) {
        (p[1] *= p[i]) %= MOD;
        p[i] = 0;
      }
      sort(p + 2, p + m + 1, greater<int>());
    }
    for (int i = 1; i < n; ++i) (ans += e[i].w % MOD * p[i] % MOD) %= MOD;
    cout << ans << endl;
  }
  return 0;
}
