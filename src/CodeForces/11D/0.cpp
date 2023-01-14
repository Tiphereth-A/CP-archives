#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  vector<vector<bool>> g(n, vector<bool>(n));
  vector<vector<i64>> dp(1 << n, vector<i64>(n));
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    --u;
    --v;
    g[u][v] = g[v][u] = true;
    dp[1 << u | 1 << v][u] = dp[1 << u | 1 << v][v] = 1;
  }
  i64 ans = 0;
  for (int s = 1; s < (1 << n); ++s) {
    auto __ = __builtin_ctz(s);
    for (int i = __ + 1; i < n; ++i) {
      if (!(s & (1 << i))) continue;
      for (int j = __ + 1; j < n; ++j)
        if ((s & (1 << j)) && g[j][i]) dp[s][i] += dp[s ^ (1 << i)][j];
      if (g[__][i] && (s ^ (1 << __) ^ (1 << i))) ans += dp[s][i];
    }
  }
  cout << ans / 2 << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
