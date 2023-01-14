#include <bits/stdc++.h>
#include <bits/stdtr1c++.h>
#include <ext/algorithm>
#include <ext/rb_tree>
#include <ext/rope>
#include <ext/vstring.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
template <typename T>
using remove_cvref_t =
  typename std::remove_cv_t<typename std::remove_reference_t<T>>;
template <class T>
using is_iterable = typename std::conditional_t<
  std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().begin()),
                 typename remove_cvref_t<T>::iterator> &&
    std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().end()),
                   typename remove_cvref_t<T>::iterator>,
  std::true_type,
  std::false_type>;
template <class T>
using is_container = typename std::conditional_t<
  is_iterable<T>::value &&
    !std::is_base_of_v<T, std::basic_string<typename T::value_type>>,
  std::true_type,
  std::false_type>;
using i64 = int64_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
template <class T>
constexpr auto chkmin(T &a, T b) -> bool {
  return b < a ? a = b, true : false;
}
template <class T>
constexpr auto chkmax(T &a, T b) -> bool {
  return a < b ? a = b, true : false;
}
template <class T>
constexpr auto ispow2(T i) -> bool {
  return i && (i & -i) == i;
}
template <class T, std::enable_if_t<is_container<T>::value> * = nullptr>
std::ostream &operator<<(std::ostream &os, const T &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
constexpr i64 MOD = 998244353;
using namespace std;
namespace tifa_libs::poly {
namespace detail__ {
constexpr uint64_t qpow(uint64_t a, uint64_t b, uint64_t mod) {
  uint64_t res(1);
  for (a %= mod; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
constexpr uint64_t inverse(uint64_t n, uint64_t mod) {
  assert(std::gcd(n, mod) == 1);
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
constexpr uint32_t proot(uint32_t m) {
  if (m == 2) return 1;
  if (m == 3 || m == 5) return 2;
  if (m == 104857601 || m == 167772161 || m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353 || m == 1004535809) return 3;
  uint32_t divs[20] = {2};
  uint32_t cnt = 1, x = (m - 1) / 2;
  while (!(x & 1)) x >>= 1;
  for (uint32_t i = 3; (uint64_t)i * i <= x; i += 2)
    if (x % i == 0) {
      divs[++cnt] = i;
      while (x % i == 0) x /= i;
    }
  if (x > 1) divs[++cnt] = x;
  for (uint32_t g = 2;; ++g) {
    bool ok = true;
    for (uint32_t i = 0; i < cnt; ++i)
      if (qpow(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    if (ok) return g;
  }
}
struct FFT_INFO_ {
  static std::vector<size_t> root;
  static void init(size_t n) {
    assert((n & (n - 1)) == 0);
    if (root.size() == n) return;
    root.resize(n);
    for (size_t i = 0; i < n; ++i)
      root[i] = (root[i >> 1] >> 1) | ((i & 1) * (n >> 1));
  }
};
template <uint32_t MOD>
struct NTT_ {
  constexpr NTT_() = default;
  constexpr void operator()(std::vector<uint32_t> &g, bool inv = false) {
    size_t n = g.size();
    FFT_INFO_::init(n);
    f.resize(n);
    w.resize(n);
    w[0] = 1;
    for (size_t i = 0; i < n; ++i)
      f[i] = (((uint64_t)MOD << 5) + g[FFT_INFO_::root[i]]) % MOD;
    for (size_t l = 1; l < n; l <<= 1) {
      uint64_t tG = qpow(inv ? IG : G, (MOD - 1) / (l + l), MOD);
      for (size_t i = 1; i < l; ++i) w[i] = w[i - 1] * tG % MOD;
      for (size_t k = 0; k < n; k += l + l)
        for (size_t p = 0; p < l; ++p) {
          uint32_t _ = (uint32_t)(w[p] * f[k | l | p] % MOD);
          f[k | l | p] = f[k | p] + (MOD - _);
          f[k | p] += _;
        }
      if (l == (1 << 10))
        for (size_t i = 0; i < n; ++i) f[i] %= MOD;
    }
    if (inv) {
      uint64_t in = inverse((uint32_t)n, MOD);
      for (size_t i = 0; i < n; ++i) g[i] = (int32_t)(f[i] % MOD * in % MOD);
    } else
      for (size_t i = 0; i < n; ++i) g[i] = (int32_t)(f[i] % MOD);
  }

private:
  static constexpr uint32_t G = proot(MOD), IG = inverse(G, MOD);
  static std::vector<uint64_t> f, w;
};
template <class DBL>
struct FFT_ {
  static_assert(std::is_floating_point_v<DBL>);
  using comp = std::complex<DBL>;
  constexpr FFT_() = default;
  constexpr void operator()(std::vector<comp> &g, bool inv = false) {
    size_t n = g.size();
    FFT_INFO_::init(n);
    w.resize(n);
    w[0] = 1;
    for (size_t i = 1; i < n; ++i)
      w[i] = {std::cos(TAU * (DBL)i / (DBL)n),
              (inv ? -1 : 1) * std::sin(TAU * (DBL)i / (DBL)n)};
    for (size_t i = 0; i < n; ++i)
      if (i < FFT_INFO_::root[i]) std::swap(g[i], g[FFT_INFO_::root[i]]);
    for (size_t i = 2; i <= n; i <<= 1) {
      for (size_t j = 1; j < i / 2; ++j)
        w[j] = {std::cos(TAU / (DBL)i * (DBL)j),
                (inv ? -1 : 1) * std::sin(TAU / (DBL)i * (DBL)j)};
      for (size_t j = 0; j < n; j += i) {
        auto f = g.begin() + j, h = g.begin() + j + i / 2;
        for (size_t k = 0; k < i / 2; ++k) {
          comp p = f[k], q = h[k] * w[k];
          f[k] = p + q;
          h[k] = p - q;
        }
      }
    }
  }

private:
  static constexpr DBL TAU = DBL(M_PIl * 2);
  static std::vector<comp> w;
};
struct PolyBase__ {
  static std::vector<uint32_t> naive_conv(std::vector<uint32_t> const &lhs,
                                          std::vector<uint32_t> const &rhs,
                                          uint32_t mod) {
    size_t n = lhs.size(), m = rhs.size();
    std::vector<uint32_t> ans(n + m - 1);
    if (n < m)
      for (size_t j = 0; j < m; j++)
        for (size_t i = 0; i < n; i++)
          ans[i + j] =
            (uint32_t)((ans[i + j] + (uint64_t)lhs[i] * rhs[j]) % mod);
    else
      for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
          ans[i + j] =
            (uint32_t)((ans[i + j] + (uint64_t)lhs[i] * rhs[j]) % mod);
    return ans;
  }
};
template <uint32_t MOD>
struct SmodPolyBase_: public PolyBase__ {
  static_assert((MOD & 3) == 1, "MOD must be prime with 4k+1");
  using self = SmodPolyBase_<MOD>;
  static NTT_<MOD> ntt;
  std::vector<uint32_t> data;
  explicit constexpr SmodPolyBase_(size_t sz = 1)
    : data(std::max((size_t)1, sz)) {}
  explicit constexpr SmodPolyBase_(std::initializer_list<uint32_t> v)
    : data(v) {}
  explicit constexpr SmodPolyBase_(std::vector<uint32_t> const &v): data(v) {}
  static constexpr uint32_t mod() { return MOD; }
#define OOCR_(op, ...)                            \
  constexpr self &operator op##=(self const &rhs) \
    __VA_ARGS__ constexpr friend self             \
    operator op(self lhs, self const &rhs) {      \
    return lhs op## = rhs;                        \
  }
  OOCR_(*, {
    if (data.size() + rhs.data.size() < 64) {
      data = naive_conv(data, rhs.data, MOD);
      return *this;
    }
    std::vector<uint32_t> a__(data), b__(rhs.data);
    data.resize(data.size() + rhs.data.size() - 1);
    size_t n =
      (size_t)(1) << (size_t)std::max(1., std::ceil(std::log2(data.size())));
    a__.resize(n);
    b__.resize(n);
    ntt(a__);
    ntt(b__);
    for (size_t i = 0; i < n; ++i)
      a__[i] = (uint32_t)((uint64_t)a__[i] * b__[i] % MOD);
    ntt(a__, true);
    a__.resize(data.size());
    data = a__;
    return *this;
  })
#undef OOCR_
};
template <ptrdiff_t ID, class DBL>
struct DmodPolyBase_: public PolyBase__ {
  using self = DmodPolyBase_<ID, DBL>;
  static uint32_t mod_;
  static uint32_t mod() { return mod_; }
  static void set_mod(uint32_t m) {
    assert(1 <= m);
    mod_ = m;
  }
  static FFT_<DBL> fft;
  using comp = typename decltype(fft)::comp;
  std::vector<uint32_t> data;
  explicit DmodPolyBase_(size_t sz = 1): data(std::max((size_t)1, sz)) {
    assert(1 <= mod_);
  }
  explicit DmodPolyBase_(std::initializer_list<uint32_t> v): data(v) {
    assert(1 <= mod_);
  }
  explicit DmodPolyBase_(std::vector<uint32_t> const &v): data(v) {
    assert(1 <= mod_);
  }
#define OOCR_(op, ...)                                                       \
  self &operator op##=(self const &rhs) __VA_ARGS__ friend self operator op( \
    self lhs, self const &rhs) {                                             \
    return lhs op## = rhs;                                                   \
  }
  OOCR_(*, {
    if (data.size() + rhs.data.size() < 64) {
      data = naive_conv(data, rhs.data, mod());
      return *this;
    }
    std::vector<comp> a__(data.size()), b__(rhs.data.size());
    for (size_t i = 0; i < data.size(); ++i)
      a__[i].real(data[i] & 0x7fff), a__[i].imag(data[i] >> 15);
    for (size_t i = 0; i < rhs.data.size(); ++i)
      b__[i].real(rhs.data[i] & 0x7fff), b__[i].imag(rhs.data[i] >> 15);
    data.resize(data.size() + rhs.data.size() - 1);
    size_t n =
      (size_t)(1) << (size_t)std::max(1., std::ceil(std::log2(data.size())));
    a__.resize(n);
    b__.resize(n);
    fft(a__);
    fft(b__);
    std::vector<comp> p__(n), q__(n);
    for (size_t i = 0; i < n; ++i)
      p__[i] = b__[i] * (a__[i] + conj(a__[(n - i) % n])) * comp{.5, 0};
    for (size_t i = 0; i < n; ++i)
      q__[i] = b__[i] * (a__[i] - conj(a__[(n - i) % n])) * comp{0, -.5};
    fft(p__, true);
    fft(q__, true);
    for (size_t i = 0; i < data.size(); ++i)
      data[i] =
        (uint32_t)(((uint64_t)(p__[i].real() / (double)n + .5) % mod() +
                    (((uint64_t)((p__[i].imag() + q__[i].real()) / (double)n +
                                 .5) %
                      mod())
                     << 15) +
                    (((uint64_t)(q__[i].imag() / (double)n + .5) % mod())
                     << 30)) %
                   mod());
    return *this;
  })
#undef OOCR_
};
template <class PBase>
class Poly {
  static_assert(std::is_base_of_v<PolyBase__, PBase>);
  PBase p;
  template <class Fodd, class Feven>
  constexpr void expand_base__(
    Poly &ans, size_t n, uint32_t val1, Fodd fodd, Feven feven) const {
    if (n == 1) {
      ans.p.data[0] = val1;
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
  constexpr void inv_(Poly &ans, size_t n) const {
    expand_base__(
      ans,
      n,
      (uint32_t)inverse(p.data[0], p.mod()),
      [this](Poly &ans, size_t n) -> void {
        --n;
        uint64_t _ = 0;
        for (size_t i = 0; i < n; ++i)
          _ = (_ + (uint64_t)ans[i] * p.data[n - i]) % p.mod();
        ans.p.data.push_back(
          (uint32_t)(_ * inverse(p.mod() - p.data[0], p.mod()) % p.mod()));
      },
      [this](Poly &ans, size_t n) -> void {
        Poly sA = *this;
        sA.do_resize(n);
        ans = ans * 2 - (ans * ans * sA).do_resize(n);
      });
  }
  constexpr void exp_(Poly &ans, size_t n) const {
    expand_base__(
      ans,
      n,
      1,
      [this](Poly &ans, size_t n) -> void {
        n -= 2;
        uint64_t _ = 0;
        for (size_t i = 0; i <= n; ++i)
          _ = (_ + (uint64_t)(i + 1) * p.data[i + 1] % p.mod() * ans[n - i]) %
              p.mod();
        ans.p.data.push_back(
          (uint32_t)(_ * inverse((uint32_t)n + 1, p.mod()) % p.mod()));
      },
      [this](Poly &ans, size_t n) -> void {
        Poly ans_ln = ans;
        ans_ln.do_resize(n).do_ln();
        for (size_t i = 0; i < ans_ln.size(); ++i)
          ans_ln[i] = (p.mod() + p.data[i] - ans_ln[i]) % p.mod();
        ++ans_ln[0];
        (ans *= ans_ln).do_resize(n);
      });
  }
  constexpr void sqrt_(Poly &ans, size_t n) const {
    if (n == 1) {
      int32_t qres = [](uint64_t a, uint64_t p) -> int32_t {
        auto f = [](uint64_t a, uint64_t p) { return qpow(a, p / 2, p) == 1; };
        if (!f(a, p)) return -1;
        int64_t r = 2;
        while (f(r, p)) ++r;
        auto n = std::countr_zero(p - 1);
        uint64_t m = (p - 1) >> n, g = qpow(r, m, p), e = 0,
                 b = qpow(a, m / 2, p), am = qpow(a, m, p);
        for (decltype(n) k = 1; k < n; ++k)
          e |= (uint64_t)(qpow(am * inverse(qpow(g, e, p), p) % p,
                               1 << (n - 1 - k),
                               p) == p - 1)
               << k;
        return (int32_t)(a * b % p * inverse(qpow(g, e / 2, p), p) % p);
      }(p.data[0], p.mod());
      assert(qres > 0);
      ans.p.data[0] = std::min(qres, (int32_t)(p.mod() - qres));
      return;
    }
    sqrt_(ans, (n + 1) / 2);
    Poly sA = *this;
    sA.do_resize(n);
    ans.do_resize(ans.size() * 2);
    ans = (sA + (ans * ans).do_resize(n)) * inverse(ans * 2);
    ans.do_resize(n);
  }

public:
  using base = PBase;
  explicit constexpr Poly(size_t sz = 1): p(sz) {}
  explicit constexpr Poly(std::initializer_list<uint32_t> v): p(v) {}
  explicit constexpr Poly(std::vector<uint32_t> const &v): p(v) {}
  constexpr friend std::istream &operator>>(std::istream &is, Poly &poly) {
    for (auto &val : poly.p.data) is >> val;
    return is;
  }
  constexpr friend std::ostream &operator<<(std::ostream &os,
                                            const Poly &poly) {
    if (!poly.size()) return os;
    for (size_t i = 1; i < poly.size(); ++i) os << poly[i - 1] << ' ';
    return os << poly.p.data.back();
  }
  constexpr uint32_t &operator[](size_t x) { return p.data[x]; }
  constexpr uint32_t operator[](size_t x) const { return p.data[x]; }
  constexpr size_t size() const { return p.data.size(); }
  constexpr Poly &do_resize(size_t size) {
    p.data.resize(size);
    return *this;
  }
  constexpr Poly &do_strip() {
    while (!p.data.empty() && !p.data.back()) p.data.pop_back();
    if (p.data.empty()) p.data.push_back(0);
    return *this;
  }
  constexpr Poly &do_reverse() {
    std::reverse(p.data.begin(), p.data.end());
    return *this;
  }
  constexpr Poly &operator*=(uint32_t c) {
    for (uint32_t &val : p.data) val = (uint32_t)((uint64_t)val * c % p.mod());
    return *this;
  }
  constexpr friend Poly operator*(Poly poly, uint32_t c) { return poly *= c; }
  constexpr friend Poly operator*(uint32_t c, Poly poly) { return poly *= c; }
#define OOCR_(op, ...)                                                    \
  constexpr Poly &operator op##=(Poly const &rhs) __VA_ARGS__ friend Poly \
  operator op(Poly lhs, Poly const &rhs) {                                \
    return lhs op## = rhs;                                                \
  }
#define OO_(op, ...)                                                         \
  constexpr Poly &operator op##=(Poly rhs) __VA_ARGS__ constexpr friend Poly \
  operator op(Poly lhs, Poly const &rhs) {                                   \
    return lhs op## = rhs;                                                   \
  }
  OOCR_(+, {
    do_resize(std::max(size(), rhs.size()));
    for (size_t i = 0; i < rhs.size(); ++i)
      p.data[i] = (uint32_t)((uint64_t)p.data[i] + rhs[i]) % p.mod();
    return *this;
  })
  OOCR_(-, {
    do_resize(std::max(size(), rhs.size()));
    for (size_t i = 0; i < rhs.size(); ++i)
      p.data[i] =
        (uint32_t)((uint64_t)p.data[i] + (p.mod() - rhs[i])) % p.mod();
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
    (*this *= rhs.do_resize(n_ - m_ + 1).do_inverse()).do_resize(n_ - m_ + 1);
    std::reverse(p.data.begin(), p.data.end());
    return *this;
  })
  OOCR_(%, {
    auto &&__ = rhs * (*this / rhs);
    return (*this -= __).do_resize(rhs.size() - 1);
  })
#undef OO_
#undef OOCR_
  constexpr friend std::pair<Poly, Poly> divmod(Poly const &lhs,
                                                Poly const &rhs) {
    auto &&div_ = lhs / rhs;
    return {div_, (lhs - rhs * div_).do_resize(rhs.size() - 1)};
  }
  constexpr Poly &do_shl(size_t offset) {
    if (offset == 0) return *this;
    if (offset >= size()) {
      std::fill(p.data.begin(), p.data.end(), 0);
      return *this;
    }
    std::fill(std::move(p.data.begin() + offset, p.data.end(), p.data.begin()),
              p.data.end(),
              0);
    return *this;
  }
  constexpr Poly &do_shr(size_t offset) {
    if (offset == 0) return *this;
    if (offset >= size()) {
      std::fill(p.data.begin(), p.data.end(), 0);
      return *this;
    }
    std::fill(
      p.data.begin(),
      std::move_backward(p.data.begin(), p.data.end() - offset, p.data.end()),
      0);
    return *this;
  }
#define FUNC_(name, ...)                                              \
  constexpr Poly &do_##name() __VA_ARGS__ constexpr friend Poly name( \
    Poly poly) {                                                      \
    return poly.do_##name();                                          \
  }
#define FUNCP1_(name, type1, var1, ...)                                   \
  constexpr Poly &do_##name(type1 var1) __VA_ARGS__ constexpr friend Poly \
  name(Poly poly, type1 var1) {                                           \
    return poly.do_##name(var1);                                          \
  }
  FUNC_(inverse, {
    Poly ret;
    inv_(ret, size());
    return *this = ret;
  })
  FUNC_(derivative, {
    for (size_t i = 1; i < size(); ++i)
      p.data[i - 1] = (uint32_t)((uint64_t)p.data[i] * i % p.mod());
    p.data.back() = 0;
    return *this;
  })
  FUNC_(integral, {
    p.data.push_back(0);
    for (size_t i = size() - 1; i; --i)
      p.data[i] =
        (uint32_t)((uint64_t)p.data[i - 1] * inverse(i, p.mod()) % p.mod());
    p.data[0] = 0;
    p.data.pop_back();
    return *this;
  })
  FUNC_(ln, {
    assert(p.data[0] == 1);
    size_t n = size();
    return *this =
             (derivative(*this) * inverse(*this)).do_resize(n).do_integral();
  })
  FUNC_(exp, {
    assert(p.data[0] == 0);
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
    size_t n = size();
    uint32_t i = qpow(proot(p.mod()), (p.mod() - 1) / 4, p.mod());
    *this *= i;
    return (*this = (exp(*this * (p.mod() - 1)) - exp(*this)) *
                    (uint32_t)((uint64_t)i * inverse(2, p.mod()) % p.mod()))
      .do_resize(n);
  })
  FUNC_(cos, {
    size_t n = size();
    uint32_t i = qpow(proot(p.mod()), (p.mod() - 1) / 4, p.mod());
    *this *= i;
    return (*this = (exp(*this) + exp(*this * (p.mod() - 1))) *
                    (uint32_t)inverse(2, p.mod()))
      .do_resize(n);
  })
  FUNC_(tan, {
    size_t n = size();
    uint32_t i = 2 * qpow(proot(p.mod()), (p.mod() - 1) / 4, p.mod());
    (*this *= i).do_exp();
    Poly _1 = *this, _2 = *this;
    if (--_1[0] < 0) _1[0] += p.mod();
    if (++_2[0] == p.mod()) _2[0] = 0;
    return (*this = _1 * (_2.do_inverse() * (p.mod() - i))).do_resize(n);
  })
  FUNC_(asin, {
    size_t n = size();
    Poly _1 = (*this * (*this * (p.mod() - 1))).do_resize(n);
    if (++_1[0] == p.mod()) _1[0] = 0;
    return (*this = (derivative(*this) * _1.do_sqrt().do_inverse())
                      .do_resize(n)
                      .do_integral());
  })
  FUNC_(acos, {
    size_t n = size();
    Poly _1 = (*this * *this * (p.mod() - 1)).do_resize(n);
    if (++_1[0] == p.mod()) _1[0] = 0;
    return (*this =
              (derivative(*this) * (_1.do_sqrt().do_inverse() * (p.mod() - 1)))
                .do_resize(n)
                .do_integral())
      .do_resize(n);
  })
  FUNC_(atan, {
    size_t n = size();
    Poly _1 = (*this * *this).do_resize(n);
    if (++_1[0] == p.mod()) _1[0] = 0;
    return (*this =
              (derivative(*this) * _1.do_inverse()).do_resize(n).do_integral())
      .do_resize(n);
  })
  FUNCP1_(pow, uint32_t, y, {
    assert(p.data[0] == 1);
    if (y == 0) {
      std::fill(p.data.begin() + 1, p.data.end(), 0);
      return *this;
    }
    if (y == 1) return *this;
    return *this = (ln(*this) * (int32_t)y).do_exp();
  })
#undef FUNC_
#undef FUNCP1_
};
}  // namespace detail__
#define POLYT_ detail__::Poly<T>
template <class T>
constexpr POLYT_ czt(POLYT_ const &f, uint32_t c, size_t m) {
  class RPOW_ {
    uint32_t a, mod;
    std::array<uint32_t, 65536> block1, block2;

  public:
    explicit constexpr RPOW_(): a(0), mod(0) {}
    constexpr RPOW_(uint32_t a, uint32_t p): RPOW_() { reset(a, p); }
    constexpr void reset(uint32_t a_, uint32_t p_) {
      assert(p_ > 1);
      if (a == a_ && mod == p_) return;
      a = a_;
      mod = p_;
      block1[0] = block2[0] = 1;
      for (uint32_t i = 1; i < 65536; i++)
        block1[i] = (uint32_t)((uint64_t)block1[i - 1] * a % mod);
      uint32_t _ = (uint32_t)((uint64_t)block1.back() * a % mod);
      for (uint32_t i = 1; i < 65536; i++)
        block2[i] = (uint32_t)((uint64_t)block2[i - 1] * _ % mod);
    }
    constexpr uint32_t operator()(size_t exponent) {
      return (uint32_t)((uint64_t)block1[exponent & 65535] *
                        block2[exponent >> 16] % mod);
    }
  };
  uint32_t mod = POLYT_::base::mod();
  c %= mod;
  RPOW_ rp(c, mod);
  size_t n = f.size();
  POLYT_ cc(n + m - 1), g(n);
  for (size_t i = 0; i < n + m - 1; ++i)
    cc[n + m - 2 - i] = rp((uint64_t)(i - 1) * i / 2 % (mod - 1));
  for (size_t i = 0; i < n; ++i)
    g[i] = (uint32_t)((uint64_t)rp(mod - 1 -
                                   ((uint64_t)i * (i - 1) / 2) % (mod - 1)) *
                      f[i] % mod);
  cc *= g;
  POLYT_ ans(m);
  for (size_t i = 0; i < m; ++i)
    ans[i] =
      (uint32_t)((uint64_t)cc[n + m - 2 - i] *
                 rp(mod - 1 - ((uint64_t)i * (i - 1) / 2) % (mod - 1)) % mod);
  return ans;
}
template <class T>
constexpr POLYT_ mpe(POLYT_ f, POLYT_ a) {
  class SegTree {
    std::vector<POLYT_> t;
    constexpr void init_(POLYT_ const &a, size_t k, size_t l, size_t r) {
      if (l == r) {
        t[k] = POLYT_{1, a[l] ? POLYT_::base::mod() - a[l] : 0};
        return;
      }
      size_t m = l + (r - l) / 2;
      init_(a, k * 2, l, m);
      init_(a, k * 2 + 1, m + 1, r);
      t[k] = t[k * 2] * t[k * 2 + 1];
    }
    static constexpr POLYT_ mult(POLYT_ const &f, POLYT_ g) {
      size_t m = g.size();
      return (f * g.do_reverse()).do_shl(m - 1).do_resize(f.size());
    }
    constexpr void
    calc_(POLYT_ f, POLYT_ &res, size_t k, size_t l, size_t r) const {
      f.do_resize(r - l + 1);
      if (l == r) {
        res[l] = f[0];
        return;
      }
      size_t m = l + (r - l) / 2;
      calc_(mult(f, t[k * 2 + 1]), res, k * 2, l, m);
      calc_(mult(f, t[k * 2]), res, k * 2 + 1, m + 1, r);
    }

  public:
    explicit constexpr SegTree(POLYT_ const &a): t(a.size() * 4) {
      init_(a, 1, 0, a.size() - 1);
    }
    constexpr POLYT_ operator()(POLYT_ const &f) const {
      POLYT_ res(f.size());
      calc_(mult(f, inverse(t[1])), res, 1, 0, t.size() / 4 - 1);
      return res;
    }
  };
  size_t n = f.size(), m = a.size();
  f.do_resize(std::max(n, m));
  a.do_resize(std::max(n, m));
  return SegTree(a)(f).do_resize(m);
}
template <class T>
constexpr POLYT_ interp(POLYT_ const &x, POLYT_ const &y) {
  class SegTree {
    constexpr void init_(POLYT_ const &a, size_t k, size_t l, size_t r) {
      if (l == r) {
        t[k] = POLYT_{a[l] ? POLYT_::base::mod() - a[l] : 0, 1};
        return;
      }
      size_t m = l + (r - l) / 2;
      init_(a, k * 2, l, m);
      init_(a, k * 2 + 1, m + 1, r);
      t[k] = t[k * 2] * t[k * 2 + 1];
    }
    constexpr POLYT_
    calc_(POLYT_ const &f, size_t k, size_t l, size_t r) const {
      if (l == r) return POLYT_{f[l]};
      size_t m = l + (r - l) / 2;
      return calc_(f, k * 2, l, m) * t[2 * k + 1] +
             calc_(f, k * 2 + 1, m + 1, r) * t[2 * k];
    }

  public:
    std::vector<POLYT_> t;
    explicit constexpr SegTree(POLYT_ const &a): t(a.size() * 4) {
      init_(a, 1, 0, a.size() - 1);
    }
    constexpr POLYT_ operator()(POLYT_ const &f) const {
      return calc_(f, 1, 0, t.size() / 4 - 1);
    }
  };
  assert(x.size() == y.size());
  size_t n = x.size();
  SegTree sgt(x);
  POLYT_ t = mpe(sgt.t[1].do_derivative(), x);
  for (size_t i = 0; i < n; ++i)
    t[i] = (uint32_t)(y[i] * detail__::inverse(t[i], POLYT_::base::mod()) %
                      POLYT_::base::mod());
  return sgt(t);
}
#undef POLYT_
template <int32_t MOD>
using s_poly = detail__::Poly<detail__::SmodPolyBase_<MOD>>;
}  // namespace tifa_libs::poly
using poly = tifa_libs::poly::s_poly<MOD>;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  poly x(n), y(n);
  for_(i, 0, n - 1) cin >> x[i] >> y[i];
  cout << tifa_libs::poly::interp(x, y) << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
