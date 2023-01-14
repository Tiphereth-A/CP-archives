#include <bits/stdc++.h>
#include <vector>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define Rep for_
template <typename... Ts>
void dec(Ts &...x) {
  ((--x), ...);
}
template <typename... Ts>
void inc(Ts &...x) {
  ((++x), ...);
}
using namespace std;
void solve(int t_ = 0) {
  if (t_ > 0) cout << '\n';
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> E(n + 1);
  vector<int> Fa(n + 1);
  vector<int> in(n + 1);
  vector<bool> sign(m + 1);
  Rep(i, 1, n) Fa[i] = i;
  auto Add = [&](int u, int v, int w) {
    E[u].push_back(make_pair(v, w)), E[v].push_back(make_pair(u, w));
  };
  function<int(int)> GF = [&](int x) -> int {
    return x == Fa[x] ? x : Fa[x] = GF(Fa[x]);
  };
  auto merge = [&](int u, int v) {
    u = GF(u), v = GF(v);
    if (u != v) return Fa[u] = v, 1;
    return 0;
  };
  bool flag = 1;
  Rep(i, 1, m) {
    int u, v;
    cin >> u >> v;
    if (flag) {
      inc(in[u], in[v]);
      sign[i] = 1;
      Add(u, v, i);
      if (!merge(u, v)) flag = 0;
    }
  }
  if (flag) cout << "-1";
  else {
    queue<int> Q;
    Rep(i, 1, n) {
      if (in[i] == 1) Q.push(i);
    }
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (auto [v, w] : E[u])
        if (in[v]) {
          sign[w] = 0;
          dec(in[v], in[u]);
          if (in[v] == 1) Q.push(v);
        }
    }
    Rep(i, 1, n) {}
    vector<int> ans;
    Rep(i, 1, m)
      if (sign[i] == 1) ans.push_back(i);
    cout << ans[0];
    Rep(i, 1, ans.size() - 1) cout << ' ' << ans[i];
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
