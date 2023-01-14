#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> dg(n + 1);
  {
    vector<int> deg(n + 1);
    vector<pair<int, int>> edges;
    edges.reserve(m);
    for (int i = 1, u, v; i <= m; ++i) {
      cin >> u >> v;
      ++deg[u];
      ++deg[v];
      edges.emplace_back(u, v);
    }
    auto __lt__ = [&](int u, int v) -> bool {
      return deg[u] < deg[v] || (deg[u] == deg[v] && u < v);
    };
    for (auto [u, v] : edges) {
      if (!__lt__(u, v)) swap(u, v);
      dg[u].push_back(v);
    }
  }
  i64 c3 = 0;
  vector<int> pre(n + 1);
  for (int u = 1; u <= n; ++u) {
    for (auto v : dg[u]) pre[v] = u;
    for (auto v : dg[u])
      for (auto w : dg[v]) c3 += pre[w] == u;
  }
  cout << c3 << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
