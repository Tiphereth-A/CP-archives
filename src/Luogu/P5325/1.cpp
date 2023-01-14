#include <bits/stdc++.h>
namespace tifa_libs {
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f64 = double;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
}  // namespace tifa_libs
namespace tifa_libs::math {
constexpr i64 div_i64d(i64 a, i64 b) { return i64(f64(a) / f64(b)); }
constexpr u64 div_u64d(u64 a, u64 b) { return u64(f64(a) / f64(b)); }
constexpr i64 div_i64(i64 a, i64 b) {
  return a <= 1000000000000 ? div_i64d(a, b) : a / b;
}
constexpr u64 div_u64(u64 a, u64 b) {
  return a <= 1000000000000 ? div_u64d(a, b) : a / b;
}
}  // namespace tifa_libs::math
namespace tifa_libs::bit {
template <class T>
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
template <class T>
constexpr int bwidth(T x) {
  return (int)sizeof(T) * 8 - cntl0(x);
}
}  // namespace tifa_libs::bit
namespace tifa_libs::math {
constexpr u32 isqrt(u64 x) {
  if (!x) return 0;
  int c = (bit::bwidth(x) - 1) / 2, sh = 31 - c;
  u32 u = [](u64 x) {
    constexpr uint8_t TAB[192] = {
      128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
      143, 144, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155,
      156, 156, 157, 158, 159, 160, 160, 161, 162, 163, 164, 164, 165, 166, 167,
      167, 168, 169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178,
      179, 179, 180, 181, 181, 182, 183, 183, 184, 185, 186, 186, 187, 188, 188,
      189, 190, 190, 191, 192, 192, 193, 194, 194, 195, 196, 196, 197, 198, 198,
      199, 200, 200, 201, 201, 202, 203, 203, 204, 205, 205, 206, 206, 207, 208,
      208, 209, 210, 210, 211, 211, 212, 213, 213, 214, 214, 215, 216, 216, 217,
      217, 218, 219, 219, 220, 220, 221, 221, 222, 223, 223, 224, 224, 225, 225,
      226, 227, 227, 228, 228, 229, 229, 230, 230, 231, 232, 232, 233, 233, 234,
      234, 235, 235, 236, 237, 237, 238, 238, 239, 239, 240, 240, 241, 241, 242,
      242, 243, 243, 244, 244, 245, 246, 246, 247, 247, 248, 248, 249, 249, 250,
      250, 251, 251, 252, 252, 253, 253, 254, 254, 255, 255, 255};
    u32 u = TAB[(x >> 56) - 64];
    u = (u << 7) + (u32)(x >> 41) / u;
    return (u << 15) + (u32)((x >> 17) / u);
  }(x << 2 * sh);
  u >>= sh;
  u -= (u64)u * u > x;
  return u;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
inline vec<u32> prime_seq(u32 n) {
  vec<bool> sieve(n / 3 + 1, 1);
  for (u32 p = 5, d = 4, i = 1, sqn = isqrt(n); p <= sqn; p += d = 6 - d, ++i) {
    if (!sieve[i]) continue;
    for (u64 q = p * p / 3,
             r = d * p / 3 + (d * p % 3 == 2),
             s = 2 * p,
             qe = sieve.size();
         q < qe;
         q += r = s - r)
      sieve[q] = 0;
  }
  vec<u32> ret{2, 3};
  for (u32 p = 5, d = 4, i = 1; p <= n; p += d = 6 - d, ++i)
    if (sieve[i]) ret.push_back(p);
  while (!ret.empty() && ret.back() > n) ret.pop_back();
  return ret;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
constexpr T qpow(T a, u64 b) {
  T res(1);
  for (; b; b >>= 1, a *= a)
    if (b & 1) res *= a;
  return res;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
constexpr T sum_i0(T n) {
  return n;
}
template <class T>
constexpr T sum_i1(T n) {
  return n * (n + 1) / 2;
}
template <class T>
constexpr T sum_i2(T n) {
  return sum_i1(n) * (n * 2 + 1) / 3;
}
template <class T>
constexpr T sum_i3(T n) {
  auto _ = sum_i1(n);
  return _ * _;
}
template <class T>
constexpr T sum_i4(T n) {
  return sum_i2(n) * (sum_i1(n) * 6 - 1) / 5;
}
template <class T>
constexpr T sum_i5(T n) {
  return sum_i3(n) * (sum_i1(n) * 4 - 1) / 3;
}
template <class T>
constexpr T sum_i6(T n) {
  auto _ = sum_i1(n);
  return sum_i2(n) * (_ * (_ * 2 - 1) * 6 + 1) / 7;
}
template <class T>
constexpr T sum_i7(T n) {
  return sum_i3(n) * 2 - sum_i5(n);
}
template <class T>
constexpr T (*sum_ik[])(T) = {sum_i0<T>,
                              sum_i1<T>,
                              sum_i2<T>,
                              sum_i3<T>,
                              sum_i4<T>,
                              sum_i5<T>,
                              sum_i6<T>,
                              sum_i7<T>};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <typename T, T (*f)(u64, u64)>
class min25_seive {
  u64 m, sqm, s;
  vec<u32> p;
  u64 idx(u64 n) const { return n <= sqm ? s - n : div_u64d(m, n); }

public:
  min25_seive(u64 m): m(m), sqm(isqrt(m)) {
    assert(m < (1ll << 42));
    if (m) {
      u64 hls = div_u64d(m, sqm);
      if (hls != 1 && div_u64d(m, hls - 1) == sqm) --hls;
      s = hls + sqm;
      p = prime_seq((u32)sqm);
    }
  }
  vec<T> sum_pk(u32 k) const {
    auto sik = sum_ik<T>[k];
    if (!m) return {};
    u64 hls = div_u64d(m, sqm);
    if (hls != 1 && div_u64d(m, hls - 1) == sqm) --hls;
    vec<T> h(s);
    for (u64 i = 1; i < hls; ++i) h[i] = sik(div_u64d(m, i)) - 1;
    for (u64 i = 1; i <= sqm; ++i) h[s - i] = sik(i) - 1;
    for (u32 x : p) {
      T _ = x, pi = h[s - x + 1];
      _ = qpow(_, k);
      u64 x2 = u64(x) * x, mx = std::min(hls, div_u64d(m, x2) + 1);
      for (u64 i = 1, ix = x; i < mx; ++i, ix += x)
        h[i] -= ((ix < hls ? h[ix] : h[s - div_u64d(m, ix)]) - pi) * _;
      for (u64 n = sqm; n >= x2; --n)
        h[s - n] -= (h[s - div_u64d(n, x)] - pi) * _;
    }
    assert(h.size() == s);
    return h;
  }
  T run(vec<T> fprime) const {
    if (!m) return {};
    assert(fprime.size() == s);
    T ans = fprime[idx(m)] + 1;
    auto dfs = [&, this](auto &&dfs, u32 i, u32 c, u64 prod, T cur) -> void {
      ans += cur * f(p[i], c + 1);
      u64 lim = div_u64d(m, prod);
      if (lim >= (u64)p[i] * p[i]) dfs(dfs, i, c + 1, p[i] * prod, cur);
      cur *= f(p[i], c);
      ans += cur * (fprime[idx(lim)] - fprime[idx(p[i])]);
      u32 j = i + 1;
      for (; j < p.size() && (u64)p[j] * p[j] * p[j] <= lim; ++j)
        dfs(dfs, j, 1, prod * p[j], cur);
      for (; j < p.size() && (u64)p[j] * p[j] <= lim; ++j) {
        T sm = f(p[j], 2);
        u64 id1 = idx(div_u64d(lim, p[j])), id2 = idx(p[j]);
        ans += cur * (sm += f(p[j], 1) * (fprime[id1] - fprime[id2]));
      }
    };
    for (u32 i = 0; i < p.size(); ++i) dfs(dfs, i, 1, p[i], 1);
    return ans;
  }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr std::tuple<u64, i64, i64> exgcd(i64 a, i64 b) {
  i64 x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b) {
    i64 c = a / b;
    std::tie(x1, x2, x3, x4, a, b) =
      std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
  }
  return {a, x1, x2};
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T, std::enable_if_t<std::is_signed_v<T>, int> = 0>
constexpr T safe_mod(T x, std::make_unsigned_t<T> mod) {
  return ((x %= (T)mod) < 0 ? x + (T)mod : x);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr std::pair<u64, u64> inv_gcd(u64 n, u64 mod) {
  auto [g, x, y] = exgcd((i64)(n % mod), (i64)mod);
  return {g, safe_mod(x, mod)};
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr u64 inverse(u64 n, u64 mod) {
  auto [g, x] = inv_gcd(n % mod, mod);
  assert(g == 1);
  return x;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <u32 MOD>
class mint_ss {
  static_assert(MOD >= 1);
  u32 v_;

public:
  constexpr static u32 mod() { return MOD; }
  constexpr static mint_ss raw(u32 v) {
    mint_ss x;
    x.v_ = v;
    return x;
  }
  constexpr mint_ss(): v_(0) {}
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_signed<T>::value> * = nullptr>
  constexpr mint_ss(T v): mint_ss() {
    i64 x = (i64)(v % (i64)mod());
    v_ = (u32)(x + (x < 0 ? mod() : 0));
  }
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_unsigned<T>::value> * = nullptr>
  constexpr mint_ss(T v): v_((u32)(v % mod())) {}
  friend std::istream &operator>>(std::istream &is, mint_ss &x) {
    i64 xx;
    is >> xx;
    xx %= mod();
    x.v_ = (u32)(xx + (xx < 0 ? mod() : 0));
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_ss &x) {
    return os << x.v_;
  }
  constexpr const u32 &val() const { return v_; }
  constexpr explicit operator u32() const { return val(); }
  constexpr u32 &data() { return v_; }
  constexpr mint_ss &operator++() {
    if (++v_ == mod()) v_ = 0;
    return *this;
  }
  constexpr mint_ss &operator--() {
    if (!v_) v_ = mod();
    --v_;
    return *this;
  }
  constexpr mint_ss operator++(int) {
    mint_ss result = *this;
    ++*this;
    return result;
  }
  constexpr mint_ss operator--(int) {
    mint_ss result = *this;
    --*this;
    return result;
  }
  constexpr mint_ss &operator+=(const mint_ss &r) {
    v_ += r.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr mint_ss &operator-=(const mint_ss &r) {
    v_ -= r.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr mint_ss &operator*=(const mint_ss &r) {
    v_ = (u32)((u64)v_ * r.v_ % mod());
    return *this;
  }
  constexpr mint_ss &operator/=(const mint_ss &r) {
    return *this = *this * r.inv();
  }
  constexpr mint_ss operator+() const { return *this; }
  constexpr mint_ss operator-() const { return mint_ss() - *this; }
  constexpr mint_ss inv() const { return inverse(v_, mod()); }
  constexpr friend mint_ss operator+(mint_ss l, const mint_ss &r) {
    return l += r;
  }
  constexpr friend mint_ss operator-(mint_ss l, const mint_ss &r) {
    return l -= r;
  }
  constexpr friend mint_ss operator*(mint_ss l, const mint_ss &r) {
    return l *= r;
  }
  constexpr friend mint_ss operator/(mint_ss l, const mint_ss &r) {
    return l /= r;
  }
  constexpr friend bool operator==(const mint_ss &l, const mint_ss &r) {
    return l.v_ == r.v_;
  }
  constexpr friend bool operator!=(const mint_ss &l, const mint_ss &r) {
    return l.v_ != r.v_;
  }
  constexpr friend bool operator<(const mint_ss &l, const mint_ss &r) {
    return l.v_ < r.v_;
  }
};
}  // namespace tifa_libs::math
using mint = tifa_libs::math::mint_ss<1'000'000'000 + 7>;
mint f(tifa_libs::u64 p, tifa_libs::u64 c) {
  auto _ = tifa_libs::math::qpow(mint(p), c);
  return _ * (_ - 1);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  tifa_libs::math::min25_seive<mint, f> min25(n);
  auto h1 = min25.sum_pk(1), h2 = min25.sum_pk(2);
  for (size_t i = 1; i < h2.size(); ++i) h2[i] -= h1[i];
  std::cout << min25.run(h2) << '\n';
  return 0;
}
