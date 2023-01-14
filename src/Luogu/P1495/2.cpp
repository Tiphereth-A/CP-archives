#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 15;
i64 a[N], b[N];
constexpr std::tuple<int64_t, int64_t, int64_t> exgcd(int64_t a, int64_t b) {
  int64_t b_ = b, m0 = 0;
  for (int64_t q = 0, _ = 0, a_ = a, m1 = 1; a_;) {
    _ = b_ - a_ * (q = b_ / a_);
    b_ = a_;
    a_ = _;
    _ = m0 - m1 * q;
    m0 = m1;
    m1 = _;
  }
  m0 = (m0 + (m0 < 0 ? b / b_ : 0)) % b;
  return {b_, m0, (b_ - m0 * a) / b};
}
constexpr int64_t mul_mod(int64_t a, int64_t b, const int64_t &mod) {
  int64_t d = (int64_t)std::floor(1.0l * a * b / mod + 0.5l),
          ret = a * b - d * mod;
  return ret < 0 ? ret + mod : ret;
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  i64 mul = 1;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i] >> b[i];
    mul *= a[i];
  }
  i64 ans = 0;
  for (int i = 1; i <= n; ++i) {
    i64 _ = mul / a[i];
    auto [g, x, y] = exgcd(_, a[i]);
    ((x %= a[i]) += a[i]) %= a[i];
    (ans += mul_mod(mul_mod(b[i], _, mul), x, mul)) %= mul;
  }
  cout << ans;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
