#include <bits/stdc++.h>
using ll = long long;
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
template <class Tp>
uint64_t rooted_tree_hash(std::vector<std::vector<Tp>> const &g,
                          size_t now = 0,
                          size_t fa = 0) {
  auto f = [](uint64_t x) {
    uint64_t lo = x & ((1 << 31) - 1), hi = x >> 31;
    return (lo * lo * lo + hi * hi * hi) * 1237123 + 19260817;
  };
  uint64_t ans = 1;
  for (auto to : g[now])
    if (to != fa) ans += f(rooted_tree_hash(g, to, now));
  return ans;
}
template <class Tp>
void tree_centroid(std::vector<std::vector<Tp>> const &g,
                   std::vector<size_t> &size_,
                   std::vector<size_t> &ans,
                   size_t now = 0,
                   size_t fa = 0) {
  size_[now] = 1;
  size_t max_sz = 0;
  for (auto to : g[now])
    if (to != fa) {
      tree_centroid(g, size_, ans, to, now);
      size_[now] += size_[to];
      max_sz = max(max_sz, size_[to]);
    }
  if ((max_sz = max(max_sz, g.size() - size_[now])) <= g.size() / 2)
    ans.push_back(now);
}
template <class Tp>
uint64_t unrooted_tree_hash(std::vector<std::vector<Tp>> const &g) {
  std::vector<size_t> sz(g.size()), c;
  tree_centroid(g, sz, c);
  uint64_t ans = 0;
  for (auto root : c) ans += rooted_tree_hash(g, root, root);
  return ans;
}
void solve(int t_ = 0) {
  int m;
  cin >> m;
  map<uint64_t, int> dict;
  auto add_edge = [](auto &g, auto u, auto v) {
    g[u].push_back(v);
    g[v].push_back(u);
  };
  vc<uint64_t> hs(m + 1);
  for_(i, 1, m, n, root) {
    cin >> n;
    vvc<int> g(n);
    root = 0;
    for_(j, 0, n - 1, x) {
      cin >> x;
      if (x) add_edge(g, j, x - 1);
    }
    if (!dict[hs[i] = unrooted_tree_hash(g)]) dict[hs[i]] = i;
  }
  for_(i, 1, m) cout << dict[hs[i]] << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
