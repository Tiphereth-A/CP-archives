#include <bits/stdc++.h>
namespace Polynomial {
using data_t = int32_t;
using ldata_t = int64_t;
const size_t N = 1 << 17 | 500;
const data_t MOD = 998244353;
using udata_t = std::make_unsigned<data_t>::type;
using ludata_t = std::make_unsigned<ldata_t>::type;
const size_t DEG_LIMIT = N << 1;
namespace Helper {
constexpr ldata_t qpow(ldata_t a, ldata_t b, const ldata_t &mod) {
  ldata_t res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
constexpr ldata_t inverse(ldata_t n, const ldata_t &mod) {
  ldata_t b = mod, m0 = 0;
  for (ldata_t q = 0, _ = 0, m1 = 1; n;) {
    _ = b - n * (q = b / n);
    b = n;
    n = _;
    _ = m0 - m1 * q;
    m0 = m1;
    m1 = _;
  }
  return (m0 + (m0 < 0 ? mod / b : 0)) % mod;
}
constexpr data_t proot_impl_(data_t m) {
  if (m == 2) return 1;
  if (m == 3 || m == 5) return 2;
  if (m == 104857601 || m == 167772161 || m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353 || m == 1004535809) return 3;
  data_t divs[20] = {2};
  data_t cnt = 1, x = (m - 1) / 2;
  while (!(x & 1)) x >>= 1;
  for (data_t i = 3; (ldata_t)i * i <= x; i += 2)
    if (x % i == 0) {
      divs[++cnt] = i;
      while (x % i == 0) x /= i;
    }
  if (x > 1) divs[++cnt] = x;
  for (data_t g = 2;; ++g) {
    bool ok = true;
    for (data_t i = 0; i < cnt; ++i)
      if (qpow(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    if (ok) return g;
  }
}
template <data_t M>
constexpr data_t proot = proot_impl_(M);
constexpr data_t legendre_symbol(uint64_t a, uint64_t p) noexcept {
  if (a == 0) return 0;
  data_t s = 1, _ctz = 0;
  while (a > 1) {
    if (a == p || a == 0 || p < 2) return 0;
    _ctz = __builtin_ctzll(a);
    if (((p - 1) & 7) && ((p + 1) & 7) && (_ctz & 1)) s = -s;
    if ((a >>= _ctz) == 1) break;
    if ((((p - 1) & 7) * (a - 1)) & 7) s = -s;
    std::swap(p %= a, a);
  }
  return s;
}
struct GaussInt {
  data_t real, imag;
  const data_t i_sqr;
  const data_t mod;
  constexpr GaussInt &operator*=(const GaussInt &rhs) {
    const data_t _ = (real * rhs.real % mod + imag * rhs.imag % mod) % mod;
    real = (real * rhs.real % mod + i_sqr * imag % mod * rhs.imag % mod) % mod;
    imag = _;
    return *this;
  }
};
data_t quad_residue(data_t n, data_t p) {
  if (n == 0 || n == 1 || n == p - 1) return n;
  if (legendre_symbol(n, p) != 1) return -1;
  std::mt19937 e;
  std::uniform_int_distribution<udata_t> u(1, p - 1);
  data_t a = u(e);
  while (legendre_symbol((a * a % p + (p - n)) % p, p) == 1) a = u(e);
  return [](GaussInt a, udata_t b) {
    GaussInt res{1, 0, a.i_sqr, a.mod};
    for (; b; b >>= 1, a *= a)
      if (b & 1) res *= a;
    return res.real;
  }(GaussInt{a, 1, (a * a % p + (p - n)) % p, p}, (p + 1) / 2);
}
template <size_t DEG_LIMIT, data_t MOD>
class INV_ {
protected:
  data_t data[DEG_LIMIT];

public:
  constexpr INV_() {
    data[0] = 0;
    data[1] = 1;
    for (size_t i = 2; i < DEG_LIMIT; ++i)
      data[i] = (data_t)((ldata_t)data[MOD % i] * (MOD - MOD / i) % MOD);
  }
  constexpr const data_t &operator[](size_t idx) const { return data[idx]; }
};
template <size_t DEG_LIMIT, data_t MOD>
class NTT_ {
  static constexpr data_t G = proot<MOD>, IG = inverse(G, MOD);

protected:
  data_t root[DEG_LIMIT];
  size_t rsz_;
  ludata_t f[DEG_LIMIT], w[DEG_LIMIT];
  constexpr void root_init(size_t n) {
    if (rsz_ == n) return;
    rsz_ = n;
    for (size_t i = 0; i < n; ++i)
      root[i] = (root[i >> 1] >> 1) | (data_t)((i & 1) * (n >> 1));
  }

public:
  constexpr NTT_() = default;
  constexpr void operator()(data_t *g, size_t n, bool inv = false) {
    root_init(n);
    w[0] = 1;
    for (size_t i = 0; i < n; ++i)
      f[i] = (((ldata_t)MOD << 5) + g[root[i]]) % MOD;
    for (size_t l = 1; l < n; l <<= 1) {
      ludata_t tG = qpow(inv ? IG : G, (MOD - 1) / (l + l), MOD);
      for (size_t i = 1; i < l; ++i) w[i] = w[i - 1] * tG % MOD;
      for (size_t k = 0; k < n; k += l + l)
        for (size_t p = 0; p < l; ++p) {
          ldata_t _ = w[p] * f[k | l | p] % MOD;
          f[k | l | p] = f[k | p] + (MOD - _);
          f[k | p] += _;
        }
      if (l == (1 << 10))
        for (size_t i = 0; i < n; ++i) f[i] %= MOD;
    }
    if (inv) {
      ludata_t in = inverse(n, MOD);
      for (size_t i = 0; i < n; ++i) g[i] = (data_t)(f[i] % MOD * in % MOD);
    } else
      for (size_t i = 0; i < n; ++i) g[i] = (data_t)(f[i] % MOD);
  }
};
const INV_<DEG_LIMIT, MOD> inv;
NTT_<DEG_LIMIT, MOD> NTT;
}  // namespace Helper
using Helper::inverse;
using Helper::NTT;
using Helper::qpow;
class Poly {
protected:
  std::vector<data_t> data;
  template <class Fodd, class Feven>
  void expand_base__(
    Poly &ans, size_t n, data_t val1, Fodd &&fodd, Feven &&feven) const {
    if (n == 1) {
      ans.data.push_back(val1);
      return;
    }
    if (n & 1) {
      expand_base__(ans, n - 1, val1, fodd, feven);
      fodd(ans, n);
      return;
    }
    expand_base__(ans, n / 2, val1, fodd, feven);
    feven(ans, n);
  }
  void inv_(Poly &ans, size_t n) const {
    expand_base__(
      ans,
      n,
      (data_t)inverse(data[0], MOD),
      [this](Poly &ans, size_t n) -> void {
        --n;
        ldata_t _ = 0;
        for (size_t i = 0; i < n; ++i)
          _ = (_ + (ldata_t)ans[i] * data[n - i]) % MOD;
        ans.data.push_back((data_t)(_ * inverse(MOD - data[0], MOD) % MOD));
      },
      [this](Poly &ans, size_t n) -> void {
        Poly sA = *this;
        sA.resize(n);
        ans = ans * 2 - (ans * ans * sA).resize(n);
      });
  }
  void exp_(Poly &ans, size_t n) const {
    expand_base__(
      ans,
      n,
      1,
      [this](Poly &ans, size_t n) -> void {
        n -= 2;
        ldata_t _ = 0;
        for (size_t i = 0; i <= n; ++i)
          _ = (_ + (i + 1) * data[i + 1] % MOD * ans[n - i] % MOD) % MOD;
        ans.data.push_back((data_t)(_ * Helper::inv[n + 1] % MOD));
      },
      [this](Poly &ans, size_t n) -> void {
        Poly ans_log = ans;
        ans_log.resize(n);
        ans_log.do_log();
        for (size_t i = 0; i < ans_log.size(); ++i)
          ans_log[i] = (MOD + data[i] - ans_log[i]) % MOD;
        ++ans_log[0];
        (ans *= ans_log).resize(n);
      });
  }
  void sqrt_(Poly &ans, size_t n) const {
    if (n == 1) {
      auto &&qres = Helper::quad_residue(data[0], MOD);
      assert(qres != -1);
      ans.data.push_back(qres);
      return;
    }
    sqrt_(ans, (n + 1) / 2);
    Poly sA = *this;
    sA.resize(n);
    ans.resize(ans.size() * 2);
    ans = (sA + (ans * ans).resize(n)) * inverse(ans * 2);
    ans.resize(n);
  }

public:
  explicit Poly(decltype(DEG_LIMIT) sz = 0): data(std::min(DEG_LIMIT, sz)) {}
  explicit Poly(const std::initializer_list<data_t> &v): data(v) {}
  explicit Poly(const std::vector<data_t> &v): data(v) {}
  friend std::istream &operator>>(std::istream &is, Poly &poly) {
    for (auto &val : poly.data) is >> val;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Poly &poly) {
    for (size_t i = 1; i < poly.size(); ++i) os << poly[i - 1] << ' ';
    return os << poly.data.back();
  }
  data_t &operator[](size_t x) { return data[x]; }
  const data_t &operator[](size_t x) const { return data[x]; }
  size_t size() const { return data.size(); }
  Poly &resize(size_t size) {
    data.resize(size);
    return *this;
  }
  Poly &strip() {
    if (size() > DEG_LIMIT) resize(DEG_LIMIT);
    while (!data.back()) data.pop_back();
    if (data.empty()) data.push_back(0);
    return *this;
  }
  Poly &operator*=(const data_t &c) {
    for (data_t &val : data) val = (data_t)((ldata_t)val * c % MOD);
    return *this;
  }
  friend Poly operator*(Poly poly, const data_t &c) { return poly *= c; }
  friend Poly operator*(const data_t &c, Poly poly) { return poly *= c; }
#define OOCR_(op, ...)                                                       \
  Poly &operator op##=(const Poly &rhs) __VA_ARGS__ friend Poly operator op( \
    Poly lhs, const Poly &rhs) {                                             \
    return lhs op## = rhs;                                                   \
  }
#define OO_(op, ...)                                                  \
  Poly &operator op##=(Poly rhs) __VA_ARGS__ friend Poly operator op( \
    Poly lhs, const Poly &rhs) {                                      \
    return lhs op## = rhs;                                            \
  }
  OOCR_(+, {
    resize(std::max(size(), rhs.size()));
    for (size_t i = 0; i < rhs.size(); ++i) {
      data[i] += rhs[i];
      data[i] -= data[i] >= MOD ? MOD : 0;
    }
    return *this;
  })
  OOCR_(-, {
    resize(std::max(size(), rhs.size()));
    for (size_t i = 0; i < rhs.size(); ++i) {
      data[i] += MOD - rhs[i];
      data[i] -= data[i] >= MOD ? MOD : 0;
    }
    return *this;
  })
  OOCR_(*, {
    static data_t a__[N << 1], b__[N << 1];
    std::copy(data.begin(), data.end(), a__);
    std::copy(rhs.data.begin(), rhs.data.end(), b__);
    size_t _sz = size();
    data.clear();
    resize(_sz + rhs.size() - 1);
    size_t n =
      (size_t)(1) << (size_t)std::max(1., std::ceil(std::log2(size())));
    NTT(a__, n);
    NTT(b__, n);
    for (size_t i = 0; i < n; ++i)
      a__[i] = (data_t)((ldata_t)a__[i] * b__[i] % MOD);
    NTT(a__, n, true);
    std::copy(a__, a__ + size(), data.begin());
    memset(a__, 0, sizeof(a__[0]) * (n));
    memset(b__, 0, sizeof(b__[0]) * (n));
    return *this;
  })
  OO_(/, {
    size_t n_ = size(), m_ = rhs.size();
    std::reverse(data.begin(), data.end());
    std::reverse(rhs.data.begin(), rhs.data.end());
    rhs.resize(n_ - m_ + 1);
    *this *= rhs.do_inverse();
    resize(n_ - m_ + 1);
    std::reverse(data.begin(), data.end());
    return *this;
  })
  OOCR_(%, {
    auto &&__ = rhs * (*this / rhs);
    return (*this -= __).resize(rhs.size() - 1);
  })
#undef OO_
#undef OOCR_
  friend std::pair<Poly, Poly> divmod(const Poly &lhs, const Poly &rhs) {
    auto &&div_ = lhs / rhs;
    return {div_, (lhs - rhs * div_).resize(rhs.size() - 1)};
  }
  Poly &shift_left(size_t offset) {
    if (offset == 0) return *this;
    if (offset >= size()) {
      data.clear();
      return *this;
    }
    data.erase(std::move(data.begin() + offset, data.end(), data.begin()),
               data.end());
    return *this;
  }
  Poly &shift_right(size_t offset) {
    if (offset == 0) return *this;
    resize(size() + offset);
    std::fill(data.begin(),
              std::move_backward(data.begin(), data.end() - offset, data.end()),
              0);
    return *this;
  }
#define FUNC_(name, ...)                                      \
  Poly &do_##name() __VA_ARGS__ friend Poly name(Poly poly) { \
    return poly.do_##name();                                  \
  }
#define FUNCP2_(name, type1, var1, type2, var2, ...)                    \
  Poly &do_##name(type1 var1, type2 var2) __VA_ARGS__ friend Poly name( \
    Poly poly, type1 var1, type2 var2) {                                \
    return poly.do_##name(var1, var2);                                  \
  }
  FUNC_(inverse, {
    Poly ret;
    inv_(ret, size());
    return *this = ret;
  })
  FUNC_(derivative, {
    for (size_t i = 1; i < size(); ++i)
      data[i - 1] = (data_t)((ldata_t)data[i] * i % MOD);
    data.pop_back();
    return *this;
  })
  FUNC_(integral, {
    data.push_back(0);
    for (size_t i = size() - 1; i; --i)
      data[i] = (data_t)((ldata_t)data[i - 1] * Helper::inv[i] % MOD);
    data.front() = 0;
    return *this;
  })
  FUNC_(log, {
    size_t sz_ = size();
    *this = (derivative(*this) * inverse(*this)).do_integral();
    resize(sz_);
    return *this;
  })
  FUNC_(exp, {
    Poly ret;
    exp_(ret, size());
    return *this = ret;
  })
  FUNC_(sqrt, {
    Poly ret;
    sqrt_(ret, size());
    return *this = ret;
  })
  FUNCP2_(pow, ludata_t, y, ludata_t, y_mod_phiMOD, {
    size_t k_ = 0, sz_ = data.size();
    for (; k_ < sz_; ++k_)
      if (data[k_]) break;
    if (k_ * y >= sz_) {
      std::fill(data.begin(), data.end(), 0);
      return *this;
    }
    shift_left(k_);
    resize(sz_ - k_ * y);
    data_t c_ = data[0], inv_c_ = (data_t)inverse(c_, MOD),
           c_y_ = (data_t)qpow(c_, y_mod_phiMOD, MOD);
    *this *= inv_c_;
    *this = (log(*this) * (data_t)y).do_exp() * c_y_;
    shift_right(k_ * y);
    return *this;
  })
#undef FUNC_
#undef FUNCP2_
};
}  // namespace Polynomial
using Polynomial::Poly;
using namespace std;
using Polynomial::qpow, Polynomial::MOD, Polynomial::Helper::inv;
int64_t invf[Polynomial::N];
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  Poly px(n);
  cin >> px;
  cout << px.do_sqrt();
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
