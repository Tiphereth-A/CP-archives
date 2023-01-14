#include <bits/stdc++.h>
using ll = long long;
template <typename... Ts>
void dec(Ts &...x) {
  ((--x), ...);
}
template <typename... Ts>
void inc(Ts &...x) {
  ((++x), ...);
}
using namespace std;
constexpr int64_t qpow(int64_t a, int64_t b, int64_t mod) {
  int64_t res(1);
  a %= mod;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
constexpr int64_t inverse(int64_t n, int64_t mod) {
  int64_t b = mod, m0 = 0;
  for (int64_t q = 0, _ = 0, m1 = 1; n;) {
    _ = b - n * (q = b / n);
    b = n;
    n = _;
    _ = m0 - m1 * q;
    m0 = m1;
    m1 = _;
  }
  return (m0 + (m0 < 0 ? mod / b : 0)) % mod;
}
constexpr int64_t quad_residue(uint64_t a, uint64_t p) {
  auto euler_judge = [](uint64_t a, uint64_t p) -> bool {
    return qpow(a, p / 2, p) == 1;
  };
  if (!euler_judge(a, p)) return -1;
  int64_t r = 2;
  while (euler_judge(r, p)) ++r;
  auto n = std::countr_zero(p - 1);
  uint64_t m = (p - 1) >> n, g = qpow(r, m, p), e = 0, b = qpow(a, m / 2, p),
           am = qpow(a, m, p);
  for (decltype(n) k = 1; k < n; ++k)
    e |= (uint64_t)(qpow(am * inverse(qpow(g, e, p), p) % p,
                         1 << (n - 1 - k),
                         p) == p - 1)
         << k;
  return a * b % p * inverse(qpow(g, e / 2, p), p) % p;
}
void solve(int t_ = 0) {
  ll a, p;
  cin >> a >> p;
  if (a == 0) {
    cout << "0\n";
    return;
  }
  ll ans = quad_residue(a, p), ans2 = (p - ans) % p;
  if (ans == -1) cout << "Hola!\n";
  else if (ans == ans2) cout << ans << '\n';
  else {
    if (ans > ans2) swap(ans, ans2);
    cout << ans << ' ' << ans2 << '\n';
  }
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
