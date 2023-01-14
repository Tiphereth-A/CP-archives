#include <bits/stdc++.h>
using ll = long long;
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
using vvc = std::vector<std::vector<Tp>>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define fors_(i, l, r, s, v...) \
  for (ll i = (l), i##e = (r), ##v; i <= i##e; i += s)
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
  int n;
  cin >> n;
  vvc<int> mp(n, vc<int>(n));
  for (auto &i : mp)
    for (auto &j : i) cin >> j;
  fors_(i, 1, n - 1, 2) reverse(mp[i].begin(), mp[i].end());
  vc<int> seq;
  seq.reserve(n * n);
  for (auto &&i : mp)
    for (auto j : i) seq.push_back(j);
  int cnt = 0;
  for_(i, 1, n * n - 1) cnt += seq[i] > seq[i - 1];
  if (cnt > (n * n - 1) - cnt) reverse(seq.begin(), seq.end());
  for_(i, 0, n * n - 1) cout << seq[i] << " \n"[i == n * n - 1];
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
