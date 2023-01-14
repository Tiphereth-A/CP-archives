#include <bits/stdc++.h>
using ll = long long;
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
namespace tifa_libs::poly {
namespace detail__ {
constexpr size_t N = 1 << 17;
static_assert((N & (N - 1)) == 0 && N > 512,
              "N should be power of 2 and greater than 512");
constexpr size_t OFFSET = 500;
constexpr size_t DEG_LIMIT = (N | OFFSET) << 1;
constexpr int64_t qpow(int64_t a, int64_t b, const int64_t &mod) {
  int64_t res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
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
constexpr int32_t proot(int32_t m) {
  if (m == 2) return 1;
  if (m == 3 || m == 5) return 2;
  if (m == 104857601 || m == 167772161 || m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353 || m == 1004535809) return 3;
  int32_t divs[20] = {2};
  int32_t cnt = 1, x = (m - 1) / 2;
  while (!(x & 1)) x >>= 1;
  for (int32_t i = 3; (int64_t)i * i <= x; i += 2)
    if (x % i == 0) {
      divs[++cnt] = i;
      while (x % i == 0) x /= i;
    }
  if (x > 1) divs[++cnt] = x;
  for (int32_t g = 2;; ++g) {
    bool ok = true;
    for (int32_t i = 0; i < cnt; ++i)
      if (qpow(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    if (ok) return g;
  }
}
constexpr int legendre_symbol(uint64_t a, uint64_t p) {
  if (a == 0) return 0;
  int s = 1, _ctz = 0;
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
  int32_t real, imag;
  const int32_t i_sqr, mod;
  constexpr GaussInt &operator*=(GaussInt rhs) {
    const int64_t _r = real, _i = imag;
    real = (int32_t)((_r * rhs.real % mod + i_sqr * _i % mod * rhs.imag % mod) %
                     mod);
    imag = (int32_t)((_i * rhs.real % mod + _r * rhs.imag % mod) % mod);
    return *this;
  }
};
int32_t quad_residue(int32_t n, int32_t p) {
  static std::mt19937 eng__(time(nullptr));
  if (n == 0 || n == 1 || n == p - 1) return n;
  if (legendre_symbol(n, p) != 1) return -1;
  std::uniform_int_distribution<int64_t> u(2, p - 1);
  int64_t a = u(eng__);
  while (legendre_symbol((a * a % p + p - n) % p, p) == 1) a = u(eng__);
  int32_t ret = [](GaussInt a, uint32_t b) {
    GaussInt res{1, 0, a.i_sqr, a.mod};
    for (; b; b >>= 1, a *= a)
      if (b & 1) res *= a;
    return res.real;
  }(GaussInt{(int32_t)a, 1, (int32_t)(a * a % p + p - n) % p, p}, (p + 1) / 2);
  return std::min(ret, p - ret);
}
template <size_t DEG_LIMIT, int32_t MOD>
struct INV_ {
  constexpr INV_() {
    data[1] = 1;
    for (size_t i = 2; i < DEG_LIMIT; ++i)
      data[i] = (int64_t)data[MOD % i] * (MOD - MOD / i) % MOD;
  }
  constexpr int32_t operator[](size_t idx) const { return data[idx]; }

private:
  static int32_t data[DEG_LIMIT];
};
template <size_t DEG_LIMIT>
struct FFT_INFO_ {
  static int32_t root[DEG_LIMIT];
  static size_t rsz_;
  static constexpr void root_init(size_t n) {
    if (rsz_ == n) return;
    rsz_ = n;
    for (size_t i = 0; i < n; ++i)
      root[i] = (root[i >> 1] >> 1) | (int32_t)((i & 1) * (n >> 1));
  }
};
template <size_t DEG_LIMIT, int32_t MOD>
struct NTT_ {
  constexpr NTT_() = default;
  constexpr void operator()(int32_t *g, size_t n, bool inv = false) {
    FFT_INFO_<DEG_LIMIT>::root_init(n);
    w[0] = 1;
    for (size_t i = 0; i < n; ++i)
      f[i] = (((int64_t)MOD << 5) + g[FFT_INFO_<DEG_LIMIT>::root[i]]) % MOD;
    for (size_t l = 1; l < n; l <<= 1) {
      uint64_t tG = qpow(inv ? IG : G, (MOD - 1) / (l + l), MOD);
      for (size_t i = 1; i < l; ++i) w[i] = w[i - 1] * tG % MOD;
      for (size_t k = 0; k < n; k += l + l)
        for (size_t p = 0; p < l; ++p) {
          int64_t _ = w[p] * f[k | l | p] % MOD;
          f[k | l | p] = f[k | p] + (MOD - _);
          f[k | p] += _;
        }
      if (l == (1 << 10))
        for (size_t i = 0; i < n; ++i) f[i] %= MOD;
    }
    if (inv) {
      uint64_t in = inverse(n, MOD);
      for (size_t i = 0; i < n; ++i) g[i] = (int32_t)(f[i] % MOD * in % MOD);
    } else
      for (size_t i = 0; i < n; ++i) g[i] = (int32_t)(f[i] % MOD);
  }

private:
  static constexpr int32_t G = proot(MOD), IG = inverse(G, MOD);
  static uint64_t f[DEG_LIMIT], w[DEG_LIMIT];
};
template <size_t DEG_LIMIT>
struct FFT_ {
  using comp = std::complex<long double>;
  constexpr FFT_() = default;
  constexpr void operator()(comp *g, size_t n, bool inv = false) {
    FFT_INFO_<DEG_LIMIT>::root_init(n);
    for (size_t i = 0; i < n; ++i)
      if ((int32_t)i < FFT_INFO_<DEG_LIMIT>::root[i])
        std::swap(g[i], g[FFT_INFO_<DEG_LIMIT>::root[i]]);
    for (size_t i = 1; i < n; ++i)
      w[i] = {std::cos(TAU * i / n), (inv ? -1 : 1) * std::sin(TAU * i / n)};
    w[0] = 1;
    for (size_t i = 2; i <= n; i <<= 1) {
      for (size_t j = 1; j < i / 2; ++j)
        w[j] = {std::cos(TAU / i * j), (inv ? -1 : 1) * std::sin(TAU / i * j)};
      for (size_t j = 0; j < n; j += i) {
        comp *f = g + j, *h = g + j + i / 2;
        for (size_t k = 0; k < i / 2; ++k) {
          comp p = f[k], q = h[k] * w[k];
          f[k] = p + q;
          h[k] = p - q;
        }
      }
    }
  }

private:
  static constexpr long double TAU = M_PIl * 2;
  static comp w[DEG_LIMIT];
};
template <int32_t MOD>
struct SmodPoly_base_ {
  using self = SmodPoly_base_<MOD>;
  static_assert((MOD & 3) == 1, "MOD must be prime with 4k+1");
  static_assert((MOD - 1) % N == 0, "N must be a factor of MOD-1");
  static constexpr INV_<DEG_LIMIT, MOD> inv{};
  static NTT_<DEG_LIMIT, MOD> ntt;
  std::vector<int32_t> data;
  explicit SmodPoly_base_(size_t sz = 0): data(std::min(DEG_LIMIT, sz)) {}
  explicit SmodPoly_base_(const std::initializer_list<int32_t> &v): data(v) {}
  explicit SmodPoly_base_(const std::vector<int32_t> &v): data(v) {}
  static constexpr int32_t mod() { return MOD; }
#define OOCR_(op, ...)                                                       \
  self &operator op##=(const self &rhs) __VA_ARGS__ friend self operator op( \
    self lhs, const self &rhs) {                                             \
    return lhs op## = rhs;                                                   \
  }
  OOCR_(*, {
    static int32_t a__[DEG_LIMIT], b__[DEG_LIMIT];
    std::copy(data.begin(), data.end(), a__);
    std::copy(rhs.data.begin(), rhs.data.end(), b__);
    data.resize(data.size() + rhs.data.size() - 1);
    size_t n =
      (size_t)(1) << (size_t)std::max(1., std::ceil(std::log2(data.size())));
    ntt(a__, n);
    ntt(b__, n);
    for (size_t i = 0; i < n; ++i)
      a__[i] = (int32_t)((int64_t)a__[i] * b__[i] % MOD);
    ntt(a__, n, true);
    std::copy(a__, a__ + data.size(), data.begin());
    memset(a__, 0, sizeof(a__[0]) * (n));
    memset(b__, 0, sizeof(b__[0]) * (n));
    return *this;
  })
#undef OOCR_
};
template <ptrdiff_t ID>
struct DmodPoly_base_ {
  using comp = FFT_<DEG_LIMIT>::comp;
  using self = DmodPoly_base_<ID>;
  static int32_t mod_;
  static int32_t mod() { return mod_; }
  static void set_mod(int32_t m) {
    assert(1 <= m);
    mod_ = m;
  }
  static FFT_<DEG_LIMIT> fft;
  std::vector<int32_t> data;
  explicit DmodPoly_base_(size_t sz = 0): data(std::min(DEG_LIMIT, sz)) {}
  explicit DmodPoly_base_(const std::initializer_list<int32_t> &v): data(v) {}
  explicit DmodPoly_base_(const std::vector<int32_t> &v): data(v) {}
#define OOCR_(op, ...)                                                       \
  self &operator op##=(const self &rhs) __VA_ARGS__ friend self operator op( \
    self lhs, const self &rhs) {                                             \
    return lhs op## = rhs;                                                   \
  }
  OOCR_(*, {
    static comp a__[DEG_LIMIT], b__[DEG_LIMIT];
    for (size_t i = 0; i < data.size(); ++i)
      a__[i].real(data[i] & 0x7fff), a__[i].imag(data[i] >> 15);
    for (size_t i = 0; i < rhs.data.size(); ++i)
      b__[i].real(rhs.data[i] & 0x7fff), b__[i].imag(rhs.data[i] >> 15);
    data.resize(data.size() + rhs.data.size() - 1);
    size_t n =
      (size_t)(1) << (size_t)std::max(1., std::ceil(std::log2(data.size())));
    fft(a__, n);
    fft(b__, n);
    static comp p__[DEG_LIMIT], q__[DEG_LIMIT];
    for (size_t i = 0; i < n; ++i)
      p__[i] = b__[i] * (a__[i] + conj(a__[(n - i) % n])) * comp{.5, 0};
    for (size_t i = 0; i < n; ++i)
      q__[i] = b__[i] * (a__[i] - conj(a__[(n - i) % n])) * comp{0, -.5};
    fft(p__, n, true);
    fft(q__, n, true);
    for (size_t i = 0; i < data.size(); ++i)
      data[i] =
        (int32_t)(((int64_t)(p__[i].real() / n + .5) % mod() +
                   (((int64_t)((p__[i].imag() + q__[i].real()) / n + .5) %
                     mod())
                    << 15) +
                   (((int64_t)(q__[i].imag() / n + .5) % mod()) << 30)) %
                  mod());
    return *this;
  })
#undef OOCR_
};
template <class Poly_base>
class Poly {
private:
  Poly_base p;
  template <class Fodd, class Feven>
  void expand_base__(
    Poly &ans, size_t n, int32_t val1, Fodd &&fodd, Feven &&feven) const {
    if (n == 1) {
      ans.p.data.push_back(val1);
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
      (int32_t)inverse(p.data[0], p.mod()),
      [this](Poly &ans, size_t n) -> void {
        --n;
        int64_t _ = 0;
        for (size_t i = 0; i < n; ++i)
          _ = (_ + (int64_t)ans[i] * p.data[n - i]) % p.mod();
        ans.p.data.push_back(
          (int32_t)(_ * inverse(p.mod() - p.data[0], p.mod()) % p.mod()));
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
        int64_t _ = 0;
        for (size_t i = 0; i <= n; ++i)
          _ = (_ + (i + 1) * p.data[i + 1] % p.mod() * ans[n - i] % p.mod()) %
              p.mod();
        ans.p.data.push_back((int32_t)(_ * p.inv[n + 1] % p.mod()));
      },
      [this](Poly &ans, size_t n) -> void {
        Poly ans_log = ans;
        ans_log.resize(n);
        ans_log.do_log();
        for (size_t i = 0; i < ans_log.size(); ++i)
          ans_log[i] = (p.mod() + p.data[i] - ans_log[i]) % p.mod();
        ++ans_log[0];
        (ans *= ans_log).resize(n);
      });
  }
  void sqrt_(Poly &ans, size_t n) const {
    if (n == 1) {
      int32_t qres = quad_residue(p.data[0], p.mod());
      assert(~qres);
      ans.p.data.push_back(qres);
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
  using base = Poly_base;
  explicit Poly(size_t sz = 0): p(sz) { assert(sz < DEG_LIMIT); }
  explicit Poly(const std::initializer_list<int32_t> &v): p(v) {}
  explicit Poly(const std::vector<int32_t> &v): p(v) {}
  friend std::istream &operator>>(std::istream &is, Poly &poly) {
    for (auto &val : poly.p.data) is >> val;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Poly &poly) {
    for (size_t i = 1; i < poly.size(); ++i) os << poly[i - 1] << ' ';
    return os << poly.p.data.back();
  }
  int32_t &operator[](size_t x) { return p.data[x]; }
  int32_t operator[](size_t x) const { return p.data[x]; }
  size_t size() const { return p.data.size(); }
  Poly &resize(size_t size) {
    p.data.resize(size);
    return *this;
  }
  Poly &strip() {
    if (size() > DEG_LIMIT) resize(DEG_LIMIT);
    while (!p.data.back()) p.data.pop_back();
    if (p.data.empty()) p.data.push_back(0);
    return *this;
  }
  Poly &operator*=(int32_t c) {
    for (int32_t &val : p.data) val = (int32_t)((int64_t)val * c % p.mod());
    return *this;
  }
  friend Poly operator*(Poly poly, int32_t c) { return poly *= c; }
  friend Poly operator*(int32_t c, Poly poly) { return poly *= c; }
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
      p.data[i] += rhs[i];
      p.data[i] -= p.data[i] >= p.mod() ? p.mod() : 0;
    }
    return *this;
  })
  OOCR_(-, {
    resize(std::max(size(), rhs.size()));
    for (size_t i = 0; i < rhs.size(); ++i) {
      p.data[i] += p.mod() - rhs[i];
      p.data[i] -= p.data[i] >= p.mod() ? p.mod() : 0;
    }
    return *this;
  })
  OOCR_(*, {
    p *= rhs.p;
    return *this;
  })
  OO_(/, {
    size_t n_ = size(), m_ = rhs.size();
    std::reverse(p.data.begin(), p.data.end());
    std::reverse(rhs.p.data.begin(), rhs.p.data.end());
    rhs.resize(n_ - m_ + 1);
    *this *= rhs.do_inverse();
    resize(n_ - m_ + 1);
    std::reverse(p.data.begin(), p.data.end());
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
      p.data.clear();
      return *this;
    }
    p.data.erase(
      std::move(p.data.begin() + offset, p.data.end(), p.data.begin()),
      p.data.end());
    return *this;
  }
  Poly &shift_right(size_t offset) {
    if (offset == 0) return *this;
    resize(size() + offset);
    std::fill(
      p.data.begin(),
      std::move_backward(p.data.begin(), p.data.end() - offset, p.data.end()),
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
      p.data[i - 1] = (int32_t)((int64_t)p.data[i] * i % p.mod());
    p.data.pop_back();
    return *this;
  })
  FUNC_(integral, {
    p.data.push_back(0);
    for (size_t i = size() - 1; i; --i)
      p.data[i] = (int32_t)((int64_t)p.data[i - 1] * p.inv[i] % p.mod());
    p.data.front() = 0;
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
  FUNC_(sin, {
    size_t sz_ = size();
    int32_t i = qpow(proot(p.mod()), (p.mod() - 1) / 4, p.mod());
    *this *= i;
    *this = (exp(*this * (p.mod() - 1)) - exp(*this)) *
            (int32_t)(i * inverse(2, p.mod()) % p.mod());
    resize(sz_);
    return *this;
  })
  FUNC_(cos, {
    size_t sz_ = size();
    int32_t i = qpow(proot(p.mod()), (p.mod() - 1) / 4, p.mod());
    *this *= i;
    *this =
      (exp(*this) + exp(*this * (p.mod() - 1))) * (int32_t)inverse(2, p.mod());
    resize(sz_);
    return *this;
  })
  FUNC_(tan, {
    size_t sz_ = size();
    int32_t i = 2 * qpow(proot(p.mod()), (p.mod() - 1) / 4, p.mod());
    (*this *= i).do_exp();
    Poly _1 = *this, _2 = *this;
    --_1[0];
    ++_2[0];
    *this = _1 * _2.do_inverse() * (p.mod() - i);
    resize(sz_);
    return *this;
  })
  FUNC_(asin, {
    size_t sz_ = size();
    Poly _1 = (*this * *this * (p.mod() - 1)).resize(sz_);
    ++_1[0];
    *this =
      (derivative(*this) * _1.do_sqrt().do_inverse()).resize(sz_).do_integral();
    resize(sz_);
    return *this;
  })
  FUNC_(acos, {
    size_t sz_ = size();
    Poly _1 = (*this * *this * (p.mod() - 1)).resize(sz_);
    ++_1[0];
    *this = (derivative(*this) * _1.do_sqrt().do_inverse() * (p.mod() - 1))
              .resize(sz_)
              .do_integral();
    resize(sz_);
    return *this;
  })
  FUNC_(atan, {
    size_t sz_ = size();
    Poly _1 = (*this * *this).resize(sz_);
    ++_1[0];
    *this = (derivative(*this) * _1.do_inverse()).resize(sz_).do_integral();
    resize(sz_);
    return *this;
  })
  FUNCP2_(pow, uint64_t, y, uint64_t, y_mod_phiMOD, {
    size_t k_ = 0, sz_ = p.data.size();
    for (; k_ < sz_; ++k_)
      if (p.data[k_]) break;
    if (k_ * y >= sz_) {
      std::fill(p.data.begin(), p.data.end(), 0);
      return *this;
    }
    shift_left(k_);
    resize(sz_ - k_ * y);
    int32_t c_ = p.data[0], inv_c_ = (int32_t)inverse(c_, p.mod()),
            c_y_ = (int32_t)qpow(c_, y_mod_phiMOD, p.mod());
    *this *= inv_c_;
    *this = (log(*this) * (int32_t)y).do_exp() * c_y_;
    shift_right(k_ * y);
    return *this;
  })
#undef FUNC_
#undef FUNCP2_
};
}  // namespace detail__
template <ptrdiff_t ID>
using d_poly = detail__::Poly<detail__::DmodPoly_base_<ID>>;
}  // namespace tifa_libs::poly
using poly = tifa_libs::poly::d_poly<0>;
void solve(int t_ = 0) {
  int n, m, p;
  cin >> n >> m >> p;
  poly::base::set_mod(p);
  poly f(n + 1), g(m + 1);
  cin >> f >> g;
  for_(i, 0, n) f[i] %= p;
  for_(i, 0, m) g[i] %= p;
  cout << f * g << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
