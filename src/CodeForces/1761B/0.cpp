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
  if (n & 1) {
    cout << n << '\n';
    return;
  }
  bool f = 1;
  a.push_back(a.front());
  for_(i, 1, n - 1)
    if (a[i - 1] != a[i + 1]) {
      f = 0;
      break;
    }
  cout << (f ? (n - 2) / 2 + 2 : n) << '\n';
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
