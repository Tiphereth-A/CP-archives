#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
using i128 = __int128_t;
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
ostream &operator<<(ostream &os, i128 n) {
  if (n < 0) {
    os << '-';
    n = -n;
  }
  if (n > 9) os << (i128)(n / 10);
  os << (uint_fast32_t)(n % 10);
  return os;
}
using P = pair<i64, i64>;
i128 abs(i128 x) { return x < 0 ? -x : x; }
void solve(int t_ = 0) {
  int n;
  cin >> n;
  vector<P> poly(n);
  for (auto &[l, r] : poly) cin >> l >> r;
  auto area = [](P const &p0, P p1, P p2) -> i128 {
    p1.first -= p0.first;
    p1.second -= p0.second;
    p2.first -= p0.first;
    p2.second -= p0.second;
    return p1.first * p2.second - p1.second * p2.first;
  };
  auto nxt = [n](int x) { return x + 1 == n ? 0 : x + 1; };
  auto pre = [n](int x) { return (x ?: n) - 1; };
  i128 tot = 0;
  for_(i, 1, n - 2) tot += area(poly[0], poly[i], poly[i + 1]);
  i128 tot3 = tot * 3;
  i128 now = 0, ans = tot * 4;
  for (int prei = n - 1, i = 0, j = 0, k = 0, nxtk = 1; i < n; prei = i, ++i) {
    if (tot < now * 4) goto end1;
    nxtk = nxt(k = nxt(j));
    while (k != prei && nxtk != prei) {
      now += area(poly[i], poly[j = k], poly[nxtk]);
      ans = min(ans, abs(tot - now * 4));
      if (tot < now * 4) break;
      nxtk = nxt(k = nxtk);
    }
  end1:
    if (j != nxt(i)) {
      now -= area(poly[i], poly[j], poly[nxt(j)]);
      now -= area(poly[i], poly[nxt(i)], poly[j]);
      now += area(poly[nxt(i)], poly[j], poly[nxt(j)]);
    } else {
      j = nxt(j);
      now = area(poly[nxt(i)], poly[j], poly[nxt(j)]);
    }
    ans = min(ans, abs(tot - now * 4));
  }
  cout << ans << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
