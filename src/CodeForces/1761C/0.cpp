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
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vvc<int> g(n), ng(n);
  vc<int> deg(n);
  vc<string> vs(n);
  for (auto &i : vs) cin >> i;
  for_(i, 0, n - 1)
    for_(j, 0, n - 1) {
      if (vs[i][j] & 1) {
        g[i].push_back(j);
        ng[j].push_back(i);
        ++deg[j];
      }
    }
  vc<set<int>> s(n);
  vc<bool> vis(n);
  for_(cnt, 1, n) {
    int j;
    for (j = 0; j < n; ++j) {
      if (vis[j]) continue;
      if (!deg[j]) break;
    }
    vis[j] = 1;
    for (auto &&i : g[j]) --deg[i];
    s[j].insert(cnt);
    for (auto &&i : ng[j])
      set_union(s[j].begin(),
                s[j].end(),
                s[i].begin(),
                s[i].end(),
                inserter(s[j], s[j].end()));
  }
  for (auto &&a : s) {
    cout << a.size();
    for (auto &&i : a) cout << ' ' << i;
    cout << '\n';
  }
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
