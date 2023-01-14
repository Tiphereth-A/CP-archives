#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 26 + OFFSET, M = 2e3 + OFFSET;
namespace Euler_path_digraph {
struct Edge {
  int to, next;
  string w;
  Edge(int _to = 0, int _next = 0, const string &_w = "")
    : to(_to), next(_next), w(_w) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, const string &w = "") {
  e[++cnt_edge] = Edge(y, head[x], w);
  head[x] = cnt_edge;
}
bool has_euler_cycle(int n, const int *in_deg, const int *out_deg) {
  for (int i = 1; i <= n; ++i)
    if (in_deg[i] != out_deg[i]) return false;
  return true;
}
bool has_euler_path(int n, const int *in_deg, const int *out_deg) {
  bool _in = 0, _out = 0;
  for (int i = 1; i <= n; ++i) {
    if (in_deg[i] == out_deg[i]) continue;
    if (_in && in_deg[i] > out_deg[i]) return false;
    if (_out && out_deg[i] > in_deg[i]) return false;
    if (in_deg[i] == out_deg[i] + 1) _in = true;
    else if (out_deg[i] == in_deg[i] + 1) _out = true;
    else return false;
  }
  return !(_in ^ _out);
}
string epath[M];
int epath_cnt;
bool dfs(int now, int dep = 0) {
  if (dep >= epath_cnt) return true;
  static bool vis[M];
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to) {
    if (vis[i]) continue;
    vis[i] = 1;
    epath[dep + 1] = e[i].w;
    if (dfs(to, dep + 1)) return true;
    vis[i] = 0;
  }
  return false;
}
bool euler_path(int n,
                int m,
                int default_start,
                tuple<int, int, string> *arcs,
                const int *in_deg,
                const int *out_deg) {
  if (!has_euler_path(n, in_deg, out_deg)) return false;
  int start = default_start;
  for (int i = 1; i <= n; ++i)
    if (in_deg[i] + 1 == out_deg[i]) {
      start = i;
      break;
    }
  sort(arcs + 1, arcs + m + 1, [](const auto &lhs, const auto &rhs) -> bool {
    return get<2>(lhs) > get<2>(rhs);
  });
  for (int i = 1; i <= m; ++i)
    addEdge(get<0>(arcs[i]), get<1>(arcs[i]), get<2>(arcs[i]));
  epath_cnt = m;
  dfs(start);
  return true;
}
}  // namespace Euler_path_digraph
using Euler_path_digraph::euler_path;
tuple<int, int, string> arcs[M];
int in_deg[N], out_deg[N];
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
auto solve() -> void {
  int m;
  cin >> m;
  string s;
  _for(i, 1, 26) fa[i] = i;
  int _min_alpha = 27, _max_alpha = 0;
  _for(i, 1, m) {
    cin >> s;
    int u = s.front() - 'a' + 1, v = s.back() - 'a' + 1;
    arcs[i] = {u, v, s};
    ++in_deg[v];
    ++out_deg[u];
    _max_alpha = max({_max_alpha, u, v});
    _min_alpha = min({_min_alpha, u, v});
    merge(u, v);
  }
  _for(i, _min_alpha + 1, _max_alpha, _ = find(_min_alpha))
    if (in_deg[i] + out_deg[i] && find(i) != _) {
      cout << "***\n";
      return;
    }
  if (!euler_path(_max_alpha, m, _min_alpha, arcs, in_deg, out_deg)) {
    cout << "***\n";
    return;
  }
  _for(i, 1, m) cout << Euler_path_digraph::epath[i] << ".\n"[i == m];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
