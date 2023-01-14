#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int MOD = 1e9 + 7;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1), dg(n + 1);
  vector<int> deg(n + 1);
  auto comp = [&](int u, int v) -> bool {
    return deg[u] > deg[v] || (deg[u] == deg[v] && u > v);
  };
  {
    vector<pair<int, int>> e;
    e.reserve(m);
    for (int i = 1, u, v; i <= m; ++i) {
      cin >> u >> v;
      e.emplace_back(u, v);
      ++deg[u];
      ++deg[v];
    }
    for (auto [u, v] : e) {
      if (!comp(u, v)) swap(u, v);
      dg[u].push_back(v);
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }
  i64 ans = 0;
  if (n >= 4) {
    i64 c4 = 0;
    vector<int> pre(n + 1), cnt(n + 1);
    for (int i = 1; i <= n; ++i)
      for (auto &&to1 : dg[i])
        for (auto &&to2 : g[to1]) {
          if (i == to2 || !comp(i, to2)) continue;
          if (pre[to2] != i) cnt[to2] = 0;
          c4 += cnt[to2]++;
          pre[to2] = i;
        }
    (ans += c4 % MOD) %= MOD;
  }
  if (n >= 3) {
    i64 c3 = 0;
    vector<int> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
      for (auto &&to : dg[i]) pre[to] = i;
      for (auto &&to1 : dg[i])
        for (auto &&to2 : dg[to1]) c3 += pre[to2] == i;
    }
    (ans += c3 % MOD * 3) %= MOD;
  }
  (ans += (i64)m * (m - 1)) %= MOD;
  for (int i = 1; i <= n; ++i) ans += (i64)deg[i] * (deg[i] - 1) / 2 % MOD;
  ans %= MOD;
  (ans += (i64)m * (n - 2)) %= MOD;
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
