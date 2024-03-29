#include <bits/stdc++.h>
#include <unordered_map>
using ll = long long;
using ull = unsigned long long;
using u64 = ull;
template <class Tp>
using vc = std::vector<Tp>;
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
namespace atcoder {
namespace internal {
int ceil_pow2(int n) {
  int x = 0;
  while ((1U << x) < (unsigned int)(n)) x++;
  return x;
}
int bsf(unsigned int n) { return __builtin_ctz(n); }
constexpr long long safe_mod(long long x, long long m) {
  x %= m;
  if (x < 0) x += m;
  return x;
}
struct barrett {
  unsigned int _m;
  unsigned long long im;
  barrett(unsigned int m): _m(m), im((unsigned long long)(-1) / m + 1) {}
  unsigned int umod() const { return _m; }
  unsigned int mul(unsigned int a, unsigned int b) const {
    unsigned long long z = a;
    z *= b;
    unsigned long long x =
      (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
    unsigned int v = (unsigned int)(z - x * _m);
    if (_m <= v) v += _m;
    return v;
  }
};
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
  if (m == 1) return 0;
  unsigned int _m = (unsigned int)(m);
  unsigned long long r = 1;
  unsigned long long y = safe_mod(x, m);
  while (n) {
    if (n & 1) r = (r * y) % _m;
    y = (y * y) % _m;
    n >>= 1;
  }
  return r;
}
constexpr bool is_prime_constexpr(int n) {
  if (n <= 1) return false;
  if (n == 2 || n == 7 || n == 61) return true;
  if (n % 2 == 0) return false;
  long long d = n - 1;
  while (d % 2 == 0) d /= 2;
  constexpr long long bases[3] = {2, 7, 61};
  for (long long a : bases) {
    long long t = d;
    long long y = pow_mod_constexpr(a, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = y * y % n;
      t <<= 1;
    }
    if (y != n - 1 && t % 2 == 0) { return false; }
  }
  return true;
}
template <int n>
constexpr bool is_prime = is_prime_constexpr(n);
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
  a = safe_mod(a, b);
  if (a == 0) return {b, 0};
  long long s = b, t = a;
  long long m0 = 0, m1 = 1;
  while (t) {
    long long u = s / t;
    s -= t * u;
    m0 -= m1 * u;
    auto tmp = s;
    s = t;
    t = tmp;
    tmp = m0;
    m0 = m1;
    m1 = tmp;
  }
  if (m0 < 0) m0 += b / s;
  return {s, m0};
}
constexpr int primitive_root_constexpr(int m) {
  if (m == 2) return 1;
  if (m == 167772161) return 3;
  if (m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353) return 3;
  int divs[20] = {};
  divs[0] = 2;
  int cnt = 1;
  int x = (m - 1) / 2;
  while (x % 2 == 0) x /= 2;
  for (int i = 3; (long long)(i)*i <= x; i += 2) {
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) { x /= i; }
    }
  }
  if (x > 1) { divs[cnt++] = x; }
  for (int g = 2;; g++) {
    bool ok = true;
    for (int i = 0; i < cnt; i++) {
      if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
}
template <int m>
constexpr int primitive_root = primitive_root_constexpr(m);
template <class T>
using is_signed_int128 =
  typename std::conditional<std::is_same<T, __int128_t>::value ||
                              std::is_same<T, __int128>::value,
                            std::true_type,
                            std::false_type>::type;
template <class T>
using is_unsigned_int128 =
  typename std::conditional<std::is_same<T, __uint128_t>::value ||
                              std::is_same<T, unsigned __int128>::value,
                            std::true_type,
                            std::false_type>::type;
template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value ||
                                                is_signed_int128<T>::value ||
                                                is_unsigned_int128<T>::value,
                                              std::true_type,
                                              std::false_type>::type;
template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                                                 std::is_signed<T>::value) ||
                                                  is_signed_int128<T>::value,
                                                std::true_type,
                                                std::false_type>::type;
template <class T>
using is_unsigned_int =
  typename std::conditional<(is_integral<T>::value &&
                             std::is_unsigned<T>::value) ||
                              is_unsigned_int128<T>::value,
                            std::true_type,
                            std::false_type>::type;
template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;
template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;
struct static_modint_base {};
}  // namespace internal
template <int m, std::enable_if_t<(1 <= m)> * = nullptr>
struct static_modint: internal::static_modint_base {
  using mint = static_modint;

public:
  static constexpr int mod() { return m; }
  static mint raw(int v) {
    mint x;
    x._v = v;
    return x;
  }
  static_modint(): _v(0) {}
  template <class T, internal::is_signed_int_t<T> * = nullptr>
  static_modint(T v) {
    long long x = (long long)(v % (long long)(umod()));
    if (x < 0) x += umod();
    _v = (unsigned int)(x);
  }
  template <class T, internal::is_unsigned_int_t<T> * = nullptr>
  static_modint(T v) {
    _v = (unsigned int)(v % umod());
  }
  unsigned int val() const { return _v; }
  mint &operator++() {
    _v++;
    if (_v == umod()) _v = 0;
    return *this;
  }
  mint &operator--() {
    if (_v == 0) _v = umod();
    _v--;
    return *this;
  }
  mint operator++(int) {
    mint result = *this;
    ++*this;
    return result;
  }
  mint operator--(int) {
    mint result = *this;
    --*this;
    return result;
  }
  mint &operator+=(const mint &rhs) {
    _v += rhs._v;
    if (_v >= umod()) _v -= umod();
    return *this;
  }
  mint &operator-=(const mint &rhs) {
    _v -= rhs._v;
    if (_v >= umod()) _v += umod();
    return *this;
  }
  mint &operator*=(const mint &rhs) {
    unsigned long long z = _v;
    z *= rhs._v;
    _v = (unsigned int)(z % umod());
    return *this;
  }
  mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }
  mint operator+() const { return *this; }
  mint operator-() const { return mint() - *this; }
  mint pow(long long n) const {
    assert(0 <= n);
    mint x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  mint inv() const {
    if (prime) {
      assert(_v);
      return pow(umod() - 2);
    } else {
      auto eg = internal::inv_gcd(_v, m);
      assert(eg.first == 1);
      return eg.second;
    }
  }
  friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }
  friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }
  friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }
  friend mint operator/(const mint &lhs, const mint &rhs) {
    return mint(lhs) /= rhs;
  }
  friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs._v == rhs._v;
  }
  friend bool operator!=(const mint &lhs, const mint &rhs) {
    return lhs._v != rhs._v;
  }

private:
  unsigned int _v;
  static constexpr unsigned int umod() { return m; }
  static constexpr bool prime = internal::is_prime<m>;
};
namespace internal {
template <class T>
using is_static_modint = std::is_base_of<internal::static_modint_base, T>;
template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
void butterfly(std::vector<mint> &a) {
  static constexpr int g = internal::primitive_root<mint::mod()>;
  int n = int(a.size());
  int h = internal::ceil_pow2(n);
  static bool first = true;
  static mint sum_e[30];
  if (first) {
    first = false;
    mint es[30], ies[30];
    int cnt2 = bsf(mint::mod() - 1);
    mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
    for (int i = cnt2; i >= 2; i--) {
      es[i - 2] = e;
      ies[i - 2] = ie;
      e *= e;
      ie *= ie;
    }
    mint now = 1;
    for (int i = 0; i <= cnt2 - 2; i++) {
      sum_e[i] = es[i] * now;
      now *= ies[i];
    }
  }
  for (int ph = 1; ph <= h; ph++) {
    int w = 1 << (ph - 1), p = 1 << (h - ph);
    mint now = 1;
    for (int s = 0; s < w; s++) {
      int offset = s << (h - ph + 1);
      for (int i = 0; i < p; i++) {
        auto l = a[i + offset];
        auto r = a[i + offset + p] * now;
        a[i + offset] = l + r;
        a[i + offset + p] = l - r;
      }
      now *= sum_e[bsf(~(unsigned int)(s))];
    }
  }
}
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
void butterfly_inv(std::vector<mint> &a) {
  static constexpr int g = internal::primitive_root<mint::mod()>;
  int n = int(a.size());
  int h = internal::ceil_pow2(n);
  static bool first = true;
  static mint sum_ie[30];
  if (first) {
    first = false;
    mint es[30], ies[30];
    int cnt2 = bsf(mint::mod() - 1);
    mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
    for (int i = cnt2; i >= 2; i--) {
      es[i - 2] = e;
      ies[i - 2] = ie;
      e *= e;
      ie *= ie;
    }
    mint now = 1;
    for (int i = 0; i <= cnt2 - 2; i++) {
      sum_ie[i] = ies[i] * now;
      now *= es[i];
    }
  }
  for (int ph = h; ph >= 1; ph--) {
    int w = 1 << (ph - 1), p = 1 << (h - ph);
    mint inow = 1;
    for (int s = 0; s < w; s++) {
      int offset = s << (h - ph + 1);
      for (int i = 0; i < p; i++) {
        auto l = a[i + offset];
        auto r = a[i + offset + p];
        a[i + offset] = l + r;
        a[i + offset + p] =
          (unsigned long long)(mint::mod() + l.val() - r.val()) * inow.val();
      }
      inow *= sum_ie[bsf(~(unsigned int)(s))];
    }
  }
}
}  // namespace internal
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution(std::vector<mint> a, std::vector<mint> b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  if (std::min(n, m) <= 60) {
    if (n < m) {
      std::swap(n, m);
      std::swap(a, b);
    }
    std::vector<mint> ans(n + m - 1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) { ans[i + j] += a[i] * b[j]; }
    }
    return ans;
  }
  int z = 1 << internal::ceil_pow2(n + m - 1);
  a.resize(z);
  internal::butterfly(a);
  b.resize(z);
  internal::butterfly(b);
  for (int i = 0; i < z; i++) { a[i] *= b[i]; }
  internal::butterfly_inv(a);
  a.resize(n + m - 1);
  mint iz = mint(z).inv();
  for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
  return a;
}
template <unsigned int mod = 998244353,
          class T,
          std::enable_if_t<internal::is_integral<T>::value> * = nullptr>
std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  using mint = static_modint<mod>;
  std::vector<mint> a2(n), b2(m);
  for (int i = 0; i < n; i++) { a2[i] = mint(a[i]); }
  for (int i = 0; i < m; i++) { b2[i] = mint(b[i]); }
  auto c2 = convolution(move(a2), move(b2));
  std::vector<T> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) { c[i] = c2[i].val(); }
  return c;
}
std::vector<long long> convolution_ll(const std::vector<long long> &a,
                                      const std::vector<long long> &b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};
  static constexpr unsigned long long MOD1 = 754974721;
  static constexpr unsigned long long MOD2 = 167772161;
  static constexpr unsigned long long MOD3 = 469762049;
  static constexpr unsigned long long M2M3 = MOD2 * MOD3;
  static constexpr unsigned long long M1M3 = MOD1 * MOD3;
  static constexpr unsigned long long M1M2 = MOD1 * MOD2;
  static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;
  static constexpr unsigned long long i1 =
    internal::inv_gcd(MOD2 * MOD3, MOD1).second;
  static constexpr unsigned long long i2 =
    internal::inv_gcd(MOD1 * MOD3, MOD2).second;
  static constexpr unsigned long long i3 =
    internal::inv_gcd(MOD1 * MOD2, MOD3).second;
  auto c1 = convolution<MOD1>(a, b);
  auto c2 = convolution<MOD2>(a, b);
  auto c3 = convolution<MOD3>(a, b);
  std::vector<long long> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) {
    unsigned long long x = 0;
    x += (c1[i] * i1) % MOD1 * M2M3;
    x += (c2[i] * i2) % MOD2 * M1M3;
    x += (c3[i] * i3) % MOD3 * M1M2;
    long long diff =
      c1[i] - internal::safe_mod((long long)(x), (long long)(MOD1));
    if (diff < 0) diff += MOD1;
    static constexpr unsigned long long offset[5] = {
      0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
    x -= offset[diff % 5];
    c[i] = x;
  }
  return c;
}
}  // namespace atcoder
using namespace atcoder;
void solve(int t_ = 0) {
  int n, q;
  cin >> n >> q;
  vc<int> p(n + 1);
  for_(i, 1, n) cin >> p[i];
  vc<bool> vis(n + 1);
  unordered_map<ll, vector<ll>> polys;
  for_(i, 1, n, j) {
    if (vis[j = i]) continue;
    vc<ll> pp;
    do {
      pp.push_back(j);
      vis[j] = 1;
    } while (!vis[j = p[j]]);
    vc<ll> p2 = pp;
    for (auto i : pp) p2.push_back(i);
    reverse(p2.begin(), p2.end());
    auto _ = convolution_ll(pp, p2);
    if (polys[pp.size()].empty()) polys[pp.size()] = _;
    else
      for_(i, 0, _.size() - 1) polys[pp.size()][i] += _[i];
  }
  for_(i, 1, q, k) {
    cin >> k;
    u64 ans = 0;
    for (auto &[key, poly] : polys) ans += poly[k % key + key - 1];
    cout << ans << '\n';
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
