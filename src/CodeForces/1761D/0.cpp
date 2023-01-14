#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
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
const int MOD = 1e9 + 7;
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
std::vector<int64_t> fact, inv_fact, p3;
void init(int64_t n, int64_t mod = MOD) {
  std::vector<int64_t> ffact(n);
  fact.resize(n * 2);
  inv_fact.resize(n);
  p3.resize(n * 2);
  ffact[0] = fact[0] = inv_fact[0] = fact[1] = inv_fact[1] = p3[0] = 1;
  for (size_t i = 2; i < n * 2; ++i) fact[i] = fact[i - 1] * i % mod;
  for (size_t i = 1; i < n; ++i) ffact[i] = ffact[i - 1] * fact[i] % mod;
  int64_t _ = inverse(ffact[n - 1], mod);
  for (ptrdiff_t i = n - 1; i > 1; --i) {
    inv_fact[i] = _ * ffact[i - 1] % mod;
    _ = _ * fact[i] % mod;
  }
  for (size_t i = 1; i < n * 2; ++i) p3[i] = p3[i - 1] * 3 % mod;
}
constexpr int64_t m_choose_n(int m, int n, int64_t mod = MOD) {
  return m < n || n < 0 ? 0 :
                          fact[m] * inv_fact[n] % mod * inv_fact[m - n] % mod;
}
void solve(int t_ = 0) {
  i64 n, k;
  cin >> n >> k;
  init(n * 2);
  i64 ans = 0;
  auto f = [](int m, int n) {
    return m == 0 && n == 0 ? 1 : m_choose_n(m - 1, n - 1);
  };
  for_(q, 0, n)
    (ans += p3[n - q] * f(k, (q + 1) / 2) % MOD * f(n - k + 1, q / 2 + 1) %
            MOD) %= MOD;
  cout << ans;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
