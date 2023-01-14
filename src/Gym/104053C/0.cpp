#include <bits/stdc++.h>
using namespace std;
class DsuBasic {
protected:
  std::vector<size_t> fa;

public:
  explicit DsuBasic(size_t size): fa(size) {
    std::iota(fa.begin(), fa.end(), 0);
  }
  size_t find(size_t x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
  bool merge(size_t x, size_t y) {
    size_t fx = find(x), fy = find(y);
    return fx == fy ? false : (fa[fx] = fy, true);
  }
};
void solve(int t_ = 0) {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> ng(n + 1);
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    ng[v].push_back(u);
  }
  vector<int> id(n + 1);
  int cnt = 0;
  {
    DsuBasic dsu(n + 1);
    for (int i = 1; i <= n; ++i)
      for (auto j : ng[i]) dsu.merge(ng[i].front(), j);
    for (int i = 1; i <= n; ++i)
      if (dsu.find(i) == i) id[i] = cnt++;
    for (int i = 1; i <= n; ++i) id[i] = id[dsu.find(i)];
  }
  vector<int> w_(n + 1);
  {
    vector<vector<int>> g(cnt);
    vector<int> indeg(n + 1);
    for (int v = 1; v <= n; ++v)
      for (auto u : ng[v]) {
        g[id[u]].emplace_back(id[v]);
        ++indeg[id[v]];
      }
    if (indeg[id[1]]) {
      cout << "No\n";
      return;
    }
    queue<int> q;
    q.push(id[1]);
    int cnt2 = 0;
    while (!q.empty()) {
      auto now = q.front();
      q.pop();
      w_[now] = cnt2++;
      for (auto to : g[now])
        if (!--indeg[to]) q.push(to);
    }
    if (cnt2 != cnt) {
      cout << "No\n";
      return;
    }
  }
  vector<int> w(n + 1);
  w[1] = 1;
  for (int v = 2; v <= n; ++v) w[v] = w_[id[v]] - w_[id[ng[v].front()]];
  cout << "Yes\n";
  for (int i = 1; i <= n; ++i) cout << w[i] << " \n"[i == n];
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
