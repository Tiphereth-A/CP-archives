#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
vector<vector<int>> g;
vector<int> sz;
i64 ans;
int n;
void dfs(int now, int fa) {
  if (g[now].size() == 1) {
    sz[now] = 1;
    return;
  }
  for (auto &&to : g[now]) {
    if (to == fa) continue;
    dfs(to, now);
    ans += 1ll * sz[now] * sz[to] * (n - 1 - sz[now] - sz[to]);
    sz[now] += sz[to];
  }
  ++sz[now];
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  std::cin >> n;
  sz.resize(n + 1);
  g.resize(n + 1);
  for_(i, 1, n - 1, u, v, w) {
    cin >> u >> v >> w;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1, 0);
  cout << ans;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
