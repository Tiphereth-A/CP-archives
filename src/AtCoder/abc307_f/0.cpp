#include <bits/stdc++.h>
using ll = long long;
using pii = std::pair<int, int>;
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
using vvc = std::vector<std::vector<Tp>>;
template <class Tp>
using pqg = std::priority_queue<Tp, std::vector<Tp>, std::greater<Tp>>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
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
  int n, m;
  cin >> n >> m;
  vvc<pii> g(n + 1);
  for_(i, 1, m, u, v, w) {
    cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  vc<int> ans(n + 1, -1);
  pqg<pii> q;
  int k;
  cin >> k;
  for_(i, 1, k, x) {
    cin >> x;
    ans[x] = 0;
    q.emplace(0, x);
  }
  while (!q.empty() && q.top().first == 0) {
    auto [_, from] = q.top();
    q.pop();
    for (auto [to, w] : g[from])
      if (!~ans[to]) q.emplace(w, to);
  }
  int d;
  cin >> d;
  for_(i, 1, d, x) {
    cin >> x;
    vc<pii> q2;
    while (!q.empty() && q.top().first <= x) {
      auto [_, from] = q.top();
      q.pop();
      if (~ans[from]) continue;
      ans[from] = i;
      for (auto [to, w] : g[from]) {
        if (~ans[to]) continue;
        if (_ + w > x) q2.emplace_back(w, to);
        else q.emplace(_ + w, to);
      }
    }
    for (auto &&i : q2) q.push(i);
  }
  for_(i, 1, n) cout << ans[i] << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
