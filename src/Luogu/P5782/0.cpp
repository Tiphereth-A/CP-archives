#include <bits/stdc++.h>
using namespace std;
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
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
namespace SAT_2 {
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
int dfn[N], low[N], cnt_dfn;
stack<int> stk;
bool in_stk[N];
int scc_id[N], cnt_scc;
void tarjan(int now) {
  dfn[now] = low[now] = ++cnt_dfn;
  stk.push(now);
  in_stk[now] = 1;
  _for_graph(head, e, i, now)
    if (!dfn[to]) {
      tarjan(to);
      chkmin(low[now], low[to]);
    } else if (in_stk[to]) chkmin(low[now], dfn[to]);
  if (dfn[now] == low[now]) {
    ++cnt_scc;
    while (stk.top() != now) {
      scc_id[stk.top()] = cnt_scc;
      in_stk[stk.top()] = 0;
      stk.pop();
    }
    scc_id[stk.top()] = cnt_scc;
    in_stk[stk.top()] = 0;
    stk.pop();
  }
}
int n;
bool init(int _n, int m, const pair<int, int> *restricts) {
  n = _n;
  for (int i = 1; i <= m; ++i) {
    auto &[x, y] = restricts[i];
    addEdge(x, y + (y % 2 ? 1 : -1));
    addEdge(y, x + (x % 2 ? 1 : -1));
  }
  for (int i = 1; i <= n * 2; ++i)
    if (!dfn[i]) tarjan(i);
  for (int i = 1; i <= n * 2; ++i)
    if (i % 2 && scc_id[i] == scc_id[i + 1]) return false;
  return true;
}
bool possible_value(int x) { return scc_id[x] < scc_id[x + (x % 2 ? 1 : -1)]; }
}  // namespace SAT_2
pair<int, int> a[M];
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  _for(i, 1, m) cin >> a[i].first >> a[i].second;
  if (!SAT_2::init(n, m, a)) {
    cout << "NIE";
    return;
  }
  _for(i, 1, n * 2)
    if (SAT_2::possible_value(i)) cout << i << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
