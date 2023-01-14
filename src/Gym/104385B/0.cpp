#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
using i128 = __int128_t;
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
ostream &operator<<(ostream &os, i128 n) {
  if (n < 0) {
    os << '-';
    n = -n;
  }
  if (n > 9) os << (i128)(n / 10);
  os << (uint_fast16_t)(n % 10);
  return os;
}
void solve(int t_ = 0) {
  i64 k;
  cin >> k;
  vc<__int128_t> a(k);
  for_(i, 0, k - 1, x) {
    cin >> x;
    a[i] = x;
  }
  i64 n, m;
  cin >> n >> m;
  for (auto &i : a) i %= m;
  i64 x;
  cin >> x;
  cout << n - ((x + reduce(a.begin(), a.end(), (__int128_t)(0)) * (n / k) +
                reduce(a.begin(), a.begin() + n % k, (__int128_t)(0))) /
                 m -
               x / m);
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
