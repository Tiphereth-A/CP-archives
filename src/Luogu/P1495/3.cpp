#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 15;
i64 a[N], b[N];
namespace CRT {
constexpr int64_t mul_mod(int64_t a, int64_t b, const int64_t &mod) {
  int64_t d = (int64_t)std::floor(1.0l * a * b / mod + 0.5l),
          ret = a * b - d * mod;
  return ret < 0 ? ret + mod : ret;
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
int64_t crt(std::vector<int64_t> const &b, std::vector<int64_t> const &m) {
  assert(b.size() == m.size());
  int64_t M = 1, ans = 0;
  for (auto &&i : m) M *= i;
  for (size_t i = 0; i < b.size(); ++i) {
    int64_t Mi = M / m[i], Ni = inverse(Mi, m[i]);
    (ans += mul_mod(mul_mod(b[i], Mi, M), Ni, M)) %= M;
  }
  return ans;
}
}  // namespace CRT
using CRT::crt;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vector<i64> b(n), m(n);
  for (int i = 0; i < n; ++i) cin >> m[i] >> b[i];
  cout << crt(b, m);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
