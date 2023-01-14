#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
#define _set_nul_n(a, n) memset(a, 0, sizeof(*(a)) * (n))
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET;
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = Edge(y, head[x]);
  head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int n, m;
i64 k;
int a[N];
bool vis[N];
int dep[N];
int ord[N], cnt_ord;
void typo(int now, int max_a) {
  vis[now] = 1;
  _for_graph(head, e, i, now) {
    if (a[to] > max_a) continue;
    if (!vis[to]) typo(to, max_a);
  }
  ord[++cnt_ord] = now;
}
bool judge(int max_a) {
  _set_nul_n(vis, n + 1);
  _set_nul_n(ord, n + 1);
  cnt_ord = 0;
  _for(i, 1, n)
    if (a[i] <= max_a && !vis[i]) typo(i, max_a);
  _set_nul_n(vis, n + 1);
  _set_nul_n(dep, n + 1);
  _rfor(i, cnt_ord, 1) {
    _for_graph(head, e, j, ord[i]) {
      if (a[to] > max_a) continue;
      if (vis[to]) return true;
      dep[to] = max(dep[to], dep[ord[i]] + 1);
    }
    vis[ord[i]] = true;
  }
  int ans = 0;
  _for(i, 1, n) ans = max(ans, dep[i]);
  return ans + 1 >= k;
}
auto solve() -> void {
  cin >> n >> m >> k;
  int l = INT_MAX, r = 0, mid = 0, ans = 0;
  _for(i, 1, n) {
    cin >> a[i];
    r = max(r, a[i]);
    l = min(l, a[i]);
  }
  if (!k) {
    cout << l;
    return;
  }
  _for(i, 1, m, x, y) {
    cin >> x >> y;
    addEdge(x, y);
  }
  while (l <= r) {
    mid = l + (r - l) / 2;
    if (judge(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << (ans ? ans : -1);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
