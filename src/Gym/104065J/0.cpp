#include <bits/stdc++.h>
using ll = long long;
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
  int n, a_[3];
  cin >> n >> a_[0] >> a_[1] >> a_[2];
  sort(a_, a_ + 3);
  int a = a_[0], b = a_[1], c = a_[2];
  auto print__ = [](int x) {
    cout << x << endl;
    int _1, _2;
    cin >> _1 >> _2;
    if (_1 == -1 && _2 == -1) exit(0);
  };
  auto print = [&](auto... x) { (print__(x), ...); };
  auto f = [&](ll x, ll y, ll z) -> ll {
    return abs((x * a + y * b + z * c) * 3 - 1ll * n * (a + b + c));
  };
  auto bi = [&](int x) -> tuple<int, int> {
    int l = 0, r = n - x;
    int y = 0, z = n - x;
    while (r - l >= 5) {
      int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
      if (auto z1_ = n - x - m1, z2_ = n - x - m2;
          f(x, m1, z1_) < f(x, m2, z2_))
        r = m2;
      else l = m1;
    }
    for_(i, l, r)
      if (f(x, i, n - x - i) < f(x, y, z)) tie(y, z) = make_tuple(i, n - x - i);
    return {y, z};
  };
  int x = 0, y = 0, z = n;
  for_(x_, 0, n)
    if (auto [y_, z_] = bi(x_); f(x_, y_, z_) < f(x, y, z))
      tie(x, y, z) = make_tuple(x_, y_, z_);
  for_(i, 1, x) print(a);
  for_(i, 1, y) print(b);
  for_(i, 1, z) print(c);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
