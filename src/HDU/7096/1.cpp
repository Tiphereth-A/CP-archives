#include <bits/stdc++.h>
using ll = long long;
using namespace std;
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vector<vector<int>> g(n + 1);
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<ll> b(n + 1), p(n + 1);
  for (int i = 1; i <= n; ++i) cin >> b[i] >> p[i];
  ll ans = 0;
  vector<ll> f(n + 1);
  function<void(int, int)> dfs = [&](int now, int fa) {
    for (int to : g[now])
      if (to != fa) dfs(to, now);
    ll tmp = b[now] * p[now];
    for (int to : g[now]) {
      if (to == fa) continue;
      int cnt = min({tmp, f[to], b[now]});
      ans += f[to] - cnt;
      tmp -= cnt;
    }
    f[now] = min(tmp, b[now]);
    ans += b[now] - f[now];
  };
  dfs(1, 0);
  cout << ans + f[1] << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
