#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 4e5 + OFFSET, K = 21;
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
i64 h[N];
i64 ans;
i64 dfs(int now, int fa = 0) {
  i64 h_son_max = 0, h_son_submax = 0;
  _for_graph(head, e, i, now) {
    if (to == fa) continue;
    i64 _h_max_from_son = dfs(to, now);
    if (_h_max_from_son > h_son_max) {
      h_son_submax = h_son_max;
      h_son_max = _h_max_from_son;
    } else if (_h_max_from_son > h_son_submax) h_son_submax = _h_max_from_son;
  }
  ans += max(i64(0), h[now] - h_son_max + (!fa) * (h[now] - h_son_submax));
  return max(h[now], h_son_max);
}
void solve() {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> h[i];
  int root = 1;
  _for(i, 1, n)
    if (h[root] < h[i]) root = i;
  _for(i, 1, n - 1, x, y) {
    cin >> x >> y;
    addEdge(x, y);
    addEdge(y, x);
  }
  dfs(root);
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
