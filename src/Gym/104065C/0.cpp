#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
using vvc = std::vector<std::vector<Tp>>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vvc<int> g(n + 1);
  for_(i, 1, n - 1, u, v) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vc<int> dep(n + 1), ndep(n + 1);
  function<void(int, int)> dfs = [&](int now, int fa) {
    dep[now] = dep[fa] + 1;
    ndep[now] = 1;
    for (auto &&to : g[now]) {
      if (to == fa) continue;
      dfs(to, now);
      ndep[now] = max(ndep[now], ndep[to] + 1);
    }
  };
  dfs(1, 0);
  i64 ans = 0;
  for (auto &&i : g[1]) ans += ndep[i];
  cout << ans;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
