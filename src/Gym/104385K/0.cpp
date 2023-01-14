#include <bits/stdc++.h>
using ll = long long;
template <class Tp>
using vc = std::vector<Tp>;
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
  vc<int> a(n);
  for (auto &i : a) cin >> i;
  vc<int> diff(n);
  for_(i, 1, n - 1) diff[i] = a[i - 1] - a[i];
  sort(diff.begin() + 1, diff.end());
  partial_sum(diff.begin(), diff.end(), diff.begin());
  int q;
  cin >> q;
  for_(i, 1, q, op, x) {
    cin >> op >> x;
    if (!op) continue;
    cout << diff[n - x] << '\n';
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
