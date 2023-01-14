#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vector<vector<int>> g(n + 1);
  vector<int> id(n + 1), pre(n + 1), suc(n + 1);
  for_(i, 1, n - 1, u, v) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for_(i, 1, n) cin >> id[i];
  function<void(int, int)> dfs = [&](int now, int fa) {
    if (g[now].size() == 1) return;
    for (auto &&to : g[now]) {
      if (to == fa) continue;
      dfs(to, now);
      if (id[to] == (id[now] + 1) % 3) pre[now] = max(pre[now], pre[to] + 1);
      if (id[to] == (id[now] + 2) % 3) suc[now] = max(suc[now], suc[to] + 1);
    }
  };
  dfs(1, 0);
  int ans = 0;
  for_(i, 1, n) ans = max(ans, pre[i] + suc[i] + 1);
  cout << ans << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
