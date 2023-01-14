#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET;
namespace Euler_path {
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = Edge(y, head[x]);
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
int epath[M];
int epath_cnt;
void dfs(int now) {
  for (int i = head[now], to = e[i].to; i; to = e[i = head[now]].to) {
    head[now] = e[i].next;
    dfs(to);
  }
  epath[epath_cnt--] = now;
}
bool euler_path(
  int n, int m, pair<int, int> *arcs, const int *in_deg, const int *out_deg) {
  if (!has_euler_path(n, in_deg, out_deg)) return false;
  int start = 1;
  for (int i = 1; i <= n; ++i)
    if (in_deg[i] + 1 == out_deg[i]) {
      start = i;
      break;
    }
  sort(arcs + 1,
       arcs + m + 1,
       [](const pair<int, int> &lhs, const pair<int, int> &rhs) -> bool {
         return lhs.first == rhs.first ? lhs.second > rhs.second :
                                         lhs.first < rhs.first;
       });
  for (int i = 1; i <= m; ++i) addEdge(arcs[i].first, arcs[i].second);
  epath_cnt = m + 1;
  dfs(start);
  return true;
}
}  // namespace Euler_path
using Euler_path::euler_path;
pair<int, int> arcs[M];
int in_deg[N], out_deg[N];
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  _for(i, 1, m) {
    cin >> arcs[i].first >> arcs[i].second;
    ++out_deg[arcs[i].first];
    ++in_deg[arcs[i].second];
  }
  if (!euler_path(n, m, arcs, in_deg, out_deg)) {
    cout << "No\n";
    return;
  }
  _for(i, 1, m + 1) cout << Euler_path::epath[i] << " \n"[i == m + 1];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
