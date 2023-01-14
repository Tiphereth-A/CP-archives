namespace tifa_libs::bit {
template <typename T>
constexpr int cntl0(T x) {
  constexpr int nd = sizeof(T) * 8;
  if (x == 0) return nd;
  static_assert(nd <= 128);
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u) return __builtin_clz(x) - (nd_u - nd);
  else if constexpr (nd <= nd_ul) return __builtin_clzl(x) - (nd_ul - nd);
  else if constexpr (nd <= nd_ull) return __builtin_clzll(x) - (nd_ull - nd);
  else {
    unsigned long long hi = x >> nd_ull;
    if (hi != 0) return __builtin_clzll(hi) - ((2 * nd_ull) - nd);
    unsigned long long lo = x & (unsigned long long)(-1);
    return (nd - nd_ull) + __builtin_clzll(lo);
  }
}
}  // namespace tifa_libs::bit
namespace tifa_libs::bit {
template <typename T>
constexpr int bwidth(T x) {
  return (int)sizeof(T) * 8 - cntl0(x);
}
}  // namespace tifa_libs::bit
#include <bits/stdc++.h>
namespace tifa_libs {
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
}  // namespace tifa_libs
namespace tifa_libs::math {
constexpr u64 mul_mod_u(u64 a, u64 b, u64 mod) {
  if (bit::bwidth(a) + bit::bwidth(b) <= 64) return a * b % mod;
  else return (u64)((u128)a * b % mod);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
vec<u64> inv_mod_gen(size_t sz, u64 mod) {
  vec<u64> ans(sz, 1);
  for (size_t i = 2; i < sz; ++i)
    ans[i] = mul_mod_u(mod - mod / i, ans[mod % i], mod);
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
vec<u64> ifact_mod_gen(size_t sz, u64 mod, vec<u64> const &inv) {
  vec<u64> ans = inv;
  for (size_t i = 2; i < sz; ++i) ans[i] = mul_mod_u(ans[i], ans[i - 1], mod);
  return ans;
}
vec<u64> ifact_mod_gen(size_t sz, u64 mod) {
  return ifact_mod_gen(sz, mod, inv_mod_gen(sz, mod));
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class Pldt>
class poly {
  Pldt p;

public:
  using value_type = typename Pldt::value_type;
  using data_type = vec<value_type>;
  explicit constexpr poly(size_t sz = 1): p(sz) {}
  explicit constexpr poly(std::initializer_list<value_type> v): p(v) {}
  template <class T>
  explicit constexpr poly(vec<T> const &v): p(v) {}
  constexpr friend std::istream &operator>>(std::istream &is, poly &poly) {
    for (auto &val : poly.p.d) is >> val;
    return is;
  }
  constexpr friend std::ostream &operator<<(std::ostream &os,
                                            const poly &poly) {
    if (!poly.size()) return os;
    for (size_t i = 1; i < poly.size(); ++i) os << poly[i - 1] << ' ';
    return os << poly.p.d.back();
  }
  constexpr size_t size() const { return p.d.size(); }
  constexpr data_type &data() { return p.d; }
  constexpr data_type const &data() const { return p.d; }
  constexpr value_type &operator[](size_t x) { return p.d[x]; }
  constexpr value_type operator[](size_t x) const { return p.d[x]; }
  constexpr value_type operator()(value_type x) const {
    value_type ans = 0;
    for (size_t i = size() - 1; ~i; --i) ans = ans * x + p.d[i];
    return ans;
  }
  template <class F>
  void apply_range(size_t l, size_t r, F f) {
    assert(l < r && r <= size());
    for (size_t i = l; i < r; ++i) f(i, p.d[i]);
  }
  template <class F>
  void apply(F f) {
    apply_range(0, size(), f);
  }
  constexpr void resize(size_t size) { p.d.resize(size); }
  constexpr poly pre(size_t size) const {
    poly _ = *this;
    _.resize(size);
    return _;
  }
  constexpr void strip() {
    auto it = std::find_if(
      p.d.rbegin(), p.d.rend(), [](auto const &x) { return x != 0; });
    p.d.resize(p.d.rend() - it);
    if (p.d.empty()) p.d.push_back(value_type(0));
  }
  constexpr void reverse(size_t n = 0) {
    std::reverse(p.d.begin(), p.d.begin() + (n ? n : size()));
  }
  void conv(poly const &r, size_t ans_size) { p.conv(r.p, ans_size); }
  void conv(poly const &r) { p.conv(r.p); }
  constexpr poly operator-() const {
    poly ret = *this;
    ret.apply([]([[maybe_unused]] size_t i, auto &v) { v = -v; });
    return ret;
  }
  friend poly operator+(poly p, value_type c) {
    p[0] += c;
    return p;
  }
  friend poly operator+(value_type c, poly const &p) { return p + c; }
  friend poly operator-(poly p, value_type c) {
    p[0] -= c;
    return p;
  }
  friend poly operator-(value_type c, poly const &p) { return p - c; }
  constexpr poly &operator*=(value_type c) {
    apply([&c]([[maybe_unused]] size_t i, auto &v) { v *= c; });
    return *this;
  }
  constexpr friend poly operator*(poly p, value_type c) { return p *= c; }
  constexpr friend poly operator*(value_type c, poly p) { return p *= c; }
  constexpr poly &operator+=(poly const &r) {
    if (!r.size()) return *this;
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r](size_t i, auto &v) { v += r[i]; });
    return *this;
  }
  friend poly operator+(poly l, poly const &r) { return l += r; }
  constexpr poly &operator-=(poly const &r) {
    if (!r.size()) return *this;
    resize(std::max(size(), r.size()));
    apply_range(0, r.size(), [&r](size_t i, auto &v) { v -= r[i]; });
    return *this;
  }
  friend poly operator-(poly l, poly const &r) { return l -= r; }
  poly &operator*=(poly const &r) {
    if (!r.size()) {
      resize(1);
      p.d[0] = 0;
      return *this;
    }
    conv(r);
    return *this;
  }
  friend poly operator*(poly l, poly const &r) { return l *= r; }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
poly<T> poly_ctsh(poly<T> const &f,
                  typename T::value_type c,
                  vec<u64> const &ifact,
                  usz m = 0) {
  usz n = f.size(), k = f.size() - 1;
  if (!m) m = n;
  using mint = typename T::value_type;
  u64 t = c.val();
  if (t <= k) {
    poly<T> ret(m);
    usz ptr = 0;
    for (usz i = t; i <= k && ptr < m; ++i) ret[ptr++] = f[i];
    if (k + 1 < t + m) {
      auto suf = poly_ctsh(f, k + 1, ifact, m - ptr);
      for (usz i = k + 1; i < t + m; ++i) ret[ptr++] = suf[i - (k + 1)];
    }
    return ret;
  }
  if (t + m > mint::mod()) {
    auto pref = poly_ctsh(f, t, ifact, mint::mod() - t),
         suf = poly_ctsh(f, 0, ifact, m - pref.size());
    std::copy(
      suf.data().begin(), suf.data().end(), std::back_inserter(pref.data()));
    return pref;
  }
  poly<T> d(k + 1);
  for (usz i = 0; i <= k; ++i) {
    d[i] = ifact[i];
    (d[i] *= ifact[k - i]) *= f[i];
    if ((k - i) & 1) d[i] = -d[i];
  }
  poly<T> h(m + k);
  for (usz i = 0; i < m + k; ++i) h[i] = mint(t - k + i).inv();
  auto dh = d * h;
  poly<T> ret(m);
  mint cur = t;
  for (usz i = 1; i <= k; ++i) cur *= t - i;
  for (usz i = 0; i < m; ++i) {
    ret[i] = cur * dh[k + i];
    (cur *= t + i + 1) *= h[i];
  }
  return ret;
}
template <class T>
poly<T> poly_ctsh(poly<T> const &f, typename T::value_type c, usz m = 0) {
  usz n = f.size();
  return poly_ctsh(f, c, ifact_mod_gen(n, T::value_type::mod()), m);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class polydata, class mint = typename polydata::value_type>
mint fact_mint(u64 n) {
  if (n <= 1) return 1;
  using poly_t = poly<polydata>;
  u64 v = 1;
  while (v * v < n) v *= 2;
  mint iv = mint(v).inv();
  poly_t g{1, v + 1};
  for (u64 d = 1; d != v; d *= 2) {
    poly_t g1 = poly_ctsh(g, mint(d) * iv),
           g2 = poly_ctsh(g, mint(d * v + v) * iv),
           g3 = poly_ctsh(g, mint(d * v + d + v) * iv);
    for (u64 i = 0; i <= d; ++i) g[i] *= g1[i], g2[i] *= g3[i];
    std::copy(
      g2.data().begin(), g2.data().end() - 1, std::back_inserter(g.data()));
  }
  mint res = 1;
  u64 i = 0;
  while (i + v <= n) res *= g[i / v], i += v;
  while (i < n) res *= ++i;
  return res;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <int>
class mint_d31 {
  u32 v_{};
  static u32 norm(i32 x) { return (u32)(x + (-(x < 0) & (i32)MOD)); }
  static u32 redc(u64 x) {
    u32 t = (u32)((x + (u64)((u32)(x)*R) * MOD_ODD) >> 32);
    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));
  }
  static u32 tsf(u32 x) {
    return redc((u64)(x % MOD_ODD) * R2) << OFFSET | (x & MASK);
  }
  static inline u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;
  static inline i32 SMOD;

public:
  static void set_mod(u32 m) {
    assert(!(m == 1 || m >> 31));
    for (MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0;
         ++OFFSET, MOD_ODD >>= 1);
    MASK = (1 << OFFSET) - 1, SMOD = (i32)(MOD);
    {
      u32 t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);
      iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv;
      R = iv * (MOD_ODD * iv - t);
    }
    R2 = (u32)(-(u64)(MOD_ODD) % MOD_ODD);
  }
  static u32 mod() { return MOD; }
  static i32 smod() { return SMOD; }
  mint_d31() {}
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  mint_d31(T v): v_(tsf(norm((i32)(v % (T)SMOD)))) {}
  u32 val() const {
    u32 h = redc(v_ >> OFFSET);
    return ((h - v_) * R & MASK) * MOD_ODD + h;
  }
  i32 sval() const { return (i32)val(); }
  bool is_zero() const { return v_ == 0; }
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit operator T() const {
    return (T)(val());
  }
  mint_d31 operator-() const {
    mint_d31 res;
    u32 h = v_ >> OFFSET;
    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-v_ & MASK);
    return res;
  }
  mint_d31 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_d31(x1);
  }
  mint_d31 &operator+=(const mint_d31 &rhs) {
    u32 h = (v_ >> OFFSET) + (rhs.v_ >> OFFSET) - MOD_ODD;
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ + rhs.v_) & MASK);
    return *this;
  }
  mint_d31 &operator-=(const mint_d31 &rhs) {
    u32 h = (v_ >> OFFSET) - (rhs.v_ >> OFFSET);
    v_ = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ - rhs.v_) & MASK);
    return *this;
  }
  mint_d31 &operator*=(const mint_d31 &rhs) {
    v_ = (redc((u64)(v_ >> OFFSET) * (rhs.v_ >> OFFSET)) << OFFSET) |
         ((v_ * rhs.v_) & MASK);
    return *this;
  }
  mint_d31 &operator/=(const mint_d31 &rhs) { return operator*=(rhs.inv()); }
  mint_d31 pow(u64 e) const {
    for (mint_d31 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  void swap(mint_d31 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend mint_d31 operator+(const mint_d31 &lhs, const mint_d31 &rhs) {
    return mint_d31(lhs) += rhs;
  }
  friend mint_d31 operator-(const mint_d31 &lhs, const mint_d31 &rhs) {
    return mint_d31(lhs) -= rhs;
  }
  friend mint_d31 operator*(const mint_d31 &lhs, const mint_d31 &rhs) {
    return mint_d31(lhs) *= rhs;
  }
  friend mint_d31 operator/(const mint_d31 &lhs, const mint_d31 &rhs) {
    return mint_d31(lhs) /= rhs;
  }
  friend bool operator==(const mint_d31 &lhs, const mint_d31 &rhs) {
    return lhs.v_ == rhs.v_;
  }
  friend bool operator!=(const mint_d31 &lhs, const mint_d31 &rhs) {
    return lhs.v_ != rhs.v_;
  }
  friend constexpr bool operator<(const mint_d31 &lhs, const mint_d31 &rhs) {
    return lhs.val() < rhs.val();
  }
  friend std::istream &operator>>(std::istream &is, mint_d31 &rhs) {
    i32 x;
    is >> x;
    rhs = mint_d31(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_d31 &rhs) {
    return os << rhs.val();
  }
  friend constexpr u32 abs(mint_d31 const &x) { return x.val(); }
};
}  // namespace tifa_libs::math
namespace tifa_libs::bit {
template <typename T>
constexpr T bceil(T x) {
  if (x == 0 || x == 1) return 1;
  constexpr int nd = sizeof(T) * 8;
  int sh = nd - cntl0((T)(x - 1u));
  using U = decltype(x << 1);
  if constexpr (!std::is_same_v<U, T>)
    sh |= (sh & nd) << (sizeof(U) / sizeof(T) / 2);
  return (T)1u << sh;
}
}  // namespace tifa_libs::bit
namespace tifa_libs::bit {
template <typename T>
constexpr int log2(T x) {
  return bwidth(x) - 1;
}
}  // namespace tifa_libs::bit
namespace tifa_libs::math {
template <class FP>
struct FFT {
  static_assert(std::is_floating_point_v<FP>);
  using C = std::complex<FP>;
  constexpr FFT(): rev(), w() {}
  size_t size() const { return rev.size(); }
  void bzr(size_t len) {
    size_t n = bit::bceil(len);
    int k = bit::log2(n);
    if (n == size()) return;
    rev.resize(n, 0);
    for (size_t i = 0; i < n; ++i)
      rev[i] = (rev[i / 2] / 2) | ((i & 1) << (k - 1));
    w.resize(n);
    w[0].real(1);
    for (size_t i = 1; i < n; ++i)
      w[i] = {std::cos(TAU * (FP)i / (FP)n), std::sin(TAU * (FP)i / (FP)n)};
  }
  void dif(vec<C> &f) const {
    size_t n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (size_t i = 0; i < n; ++i)
      if (i < rev[i]) std::swap(f[rev[i]], f[i]);
    for (size_t i = 2, d = n / 2; i <= n; i *= 2, d /= 2)
      for (size_t j = 0; j < n; j += i) {
        auto l = f.begin() + j, r = f.begin() + j + i / 2;
        auto p = w.begin();
        for (size_t k = 0; k < i / 2; ++k, ++l, ++r, p += d) {
          C tmp = *r * *p;
          *r = *l - tmp;
          *l = *l + tmp;
        }
      }
  }
  void dit(vec<C> &f) const {
    size_t n = size();
    dif(f);
    for (size_t i = 0; i < n; ++i) f[i] /= (FP)n;
  }

private:
  const FP TAU = std::acos((FP)-1.) * 2;
  vec<size_t> rev;
  vec<C> w;
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint, class FP = double>
vec<mint> conv_mtt(vec<mint> const &l, vec<mint> const &r, size_t ans_size) {
  using C = typename FFT<FP>::C;
  static FFT<FP> fft;
  if (l.size() == 1) {
    vec<mint> ans = r;
    ans.resize(ans_size);
    for (auto &i : ans) i *= l[0];
    return ans;
  }
  if (r.size() == 1) {
    vec<mint> ans = l;
    ans.resize(ans_size);
    for (auto &i : ans) i *= r[0];
    return ans;
  }
  fft.bzr(std::min(l.size() + r.size() - 1, ans_size));
  size_t n = fft.size();
  const int OFS =
    ((int)sizeof(decltype(mint::mod())) * 8 - bit::cntl0(mint::mod() - 1) + 1) /
    2;
  const u32 MSK = ((1u << OFS) - 1);
  vec<mint> ans(ans_size);
  vec<C> a(n), b(n);
  for (size_t i = 0; i < l.size(); ++i)
    a[i] = {(FP)(l[i].val() & MSK), (FP)(l[i].val() >> OFS)};
  for (size_t i = 0; i < r.size(); ++i)
    b[i] = {(FP)(r[i].val() & MSK), (FP)(r[i].val() >> OFS)};
  fft.dif(a);
  fft.dif(b);
  {
    vec<C> p(n), q(n);
    for (size_t i = 0, j; i < n; ++i) {
      j = (n - i) & (n - 1);
      C da = (a[i] + std::conj(a[j])) * C(.5, 0),
        db = (a[i] - std::conj(a[j])) * C(0, -.5),
        dc = (b[i] + std::conj(b[j])) * C(.5, 0),
        dd = (b[i] - std::conj(b[j])) * C(.5, 0);
      p[j] = da * dc + da * dd;
      q[j] = db * dc + db * dd;
    }
    a = p;
    b = q;
  }
  fft.dif(a);
  fft.dif(b);
  for (size_t i = 0; i < ans_size; ++i) {
    i64 da = (i64)(a[i].real() / (FP)n + .5) % mint::mod(),
        db = (i64)(a[i].imag() / (FP)n + .5) % mint::mod(),
        dc = (i64)(b[i].real() / (FP)n + .5) % mint::mod(),
        dd = (i64)(b[i].imag() / (FP)n + .5) % mint::mod();
    ans[i] =
      da + ((db + dc) << OFS) % mint::mod() + (dd << (OFS * 2)) % mint::mod();
  }
  return ans;
}
template <class mint, class FP = double>
vec<mint> conv_mtt(vec<mint> const &l, vec<mint> const &r) {
  return conv_mtt<mint, FP>(l, r, l.size() + r.size() - 1);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class U, class T = U>
vec<T> conv_naive(vec<U> const &l, vec<U> const &r, size_t ans_size) {
  static_assert(sizeof(U) <= sizeof(T));
  size_t n = l.size(), m = r.size();
  vec<T> ans(ans_size);
  if (n < m)
    for (size_t j = 0; j < m; ++j)
      for (size_t i = 0; i < n; ++i) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  else
    for (size_t i = 0; i < n; ++i)
      for (size_t j = 0; j < m; ++j) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  return ans;
}
template <class U, class T = U>
vec<T> conv_naive(vec<U> const &l, vec<U> const &r) {
  return conv_naive<U, T>(l, r, l.size() + r.size() - 1);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint>
struct polydata_d {
  using value_type = mint;
  vec<mint> d;
  explicit constexpr polydata_d(size_t sz = 1): d(sz) {}
  explicit constexpr polydata_d(std::initializer_list<mint> v): d(v) {}
  explicit constexpr polydata_d(vec<mint> const &v): d(v) {}
  void conv(polydata_d const &r, size_t ans_size) {
    d =
      ans_size < 32 ? conv_naive(d, r.d, ans_size) : conv_mtt(d, r.d, ans_size);
  }
  void conv(polydata_d const &r) { conv(r, d.size() + r.d.size() - 1); }
};
}  // namespace tifa_libs::math
using mint = tifa_libs::math::mint_d31<-1>;
using polyd = tifa_libs::math::polydata_d<mint>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::u32 n, p;
    std::cin >> n >> p;
    mint::set_mod(p);
    std::cout << tifa_libs::math::fact_mint<polyd>(n) << '\n';
  }
  return 0;
}
