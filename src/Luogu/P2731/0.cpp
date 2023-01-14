#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 500 + OFFSET, M = 2048 + OFFSET;
namespace Euler_path_graph {
vector<int> graph[N];
bool has_euler_cycle(int n, const int *deg) {
  for (int i = 1; i <= n; ++i)
    if (deg[i] & 1) return false;
  return true;
}
bool has_euler_path(int n, const int *deg) {
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    if (!(deg[i] & 1)) continue;
    if (++cnt > 2) return false;
  }
  return cnt == 0 || cnt == 2;
}
int epath[M];
int epath_cnt;
map<pair<int, int>, int> cnt;
void dfs(int now) {
  for (int i = 0, to = graph[now][i]; i < graph[now].size();
       to = graph[now][++i]) {
    if (!cnt[{now, to}]) continue;
    --cnt[{now, to}];
    --cnt[{to, now}];
    dfs(to);
  }
  epath[epath_cnt--] = now;
}
bool euler_path(int n, int m, pair<int, int> *edges, const int *deg) {
  if (!has_euler_path(n, deg)) return false;
  int start = 1;
  for (int i = 1; i <= n; ++i)
    if (deg[i] & 1) {
      start = i;
      break;
    }
  for (int i = 1; i <= n; ++i) graph[i].reserve(deg[i]);
  for (int i = 1; i <= m; ++i) {
    graph[edges[i].first].push_back(edges[i].second);
    graph[edges[i].second].push_back(edges[i].first);
    ++cnt[edges[i]];
    ++cnt[{edges[i].second, edges[i].first}];
  }
  for (int i = 1; i <= n; ++i) sort(graph[i].begin(), graph[i].end());
  epath_cnt = m + 1;
  dfs(start);
  return true;
}
}  // namespace Euler_path_graph
using Euler_path_graph::euler_path;
pair<int, int> edges[M];
int deg[N];
auto solve() -> void {
  int n = 0, m;
  cin >> m;
  _for(i, 1, m, x, y) {
    cin >> x >> y;
    edges[i] = minmax(x, y);
    n = max(n, edges[i].second);
    ++deg[x];
    ++deg[y];
  }
  euler_path(n, m, edges, deg);
  _for(i, 1, m + 1) cout << Euler_path_graph::epath[i] << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
