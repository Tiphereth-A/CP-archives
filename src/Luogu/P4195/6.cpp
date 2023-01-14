#include <bits/stdc++.h>
using i64 = int64_t;
namespace EXBSGS {
constexpr int64_t qpow(int64_t a, int64_t b, int64_t mod) {
  int64_t res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
constexpr int64_t inverse(int64_t n, const int64_t &mod) {
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
int64_t BSGS(int64_t a, int64_t b, int64_t m) {
  std::unordered_map<int64_t, int64_t> hmp;
  int64_t sqrt_m = std::ceil(std::sqrt(m)), s = b % m * a % m;
  for (int64_t i = 1; i <= sqrt_m; ++i, (s *= a) %= m) hmp[s] = i;
  int64_t _ = qpow(a, sqrt_m, m);
  s = _;
  for (int64_t i = 1; i <= sqrt_m; ++i, (s *= _) %= m)
    if (hmp[s] && i * sqrt_m >= hmp[s]) return i * sqrt_m - hmp[s];
  return -1;
}
int64_t exBSGS(int64_t a, int64_t b, int64_t m) {
  if (m == 0) return -1;
  a %= m;
  if ((b %= m) == 1 || m == 1) return 0;
  uint64_t cnt = 0;
  int64_t t = 1;
  for (int64_t d = std::gcd(a, m); d != 1; d = std::gcd(a, m)) {
    if (b % d) return -1;
    ++cnt;
    b /= d;
    m /= d;
    (t *= a / d) %= m;
    if (b == t) return cnt;
  }
  auto &&ans = BSGS(a, b * inverse(t, m) % m, m);
  return ~ans ? ans + cnt : -1;
}
}  // namespace EXBSGS
using EXBSGS::exBSGS;
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 a, b, m;
  while ((cin >> a >> m >> b), (a || b || m))
    if (auto &&ans = exBSGS(a, b, m); ~ans) cout << ans << '\n';
    else cout << "No Solution\n";
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
