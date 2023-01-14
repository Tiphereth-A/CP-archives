#include <bits/stdc++.h>
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::math {
template <u32 MOD>
class mint_s30 {
  u32 v_{};
  static constexpr u32 get_r() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
  }

public:
  static constexpr u32 reduce(u64 x) {
    return (u32)((x + (u64)((u32)(x)*R) * MOD) >> 32);
  }
  static constexpr u32 norm(u32 x) {
    return x - (MOD & -((MOD - 1 - x) >> 31));
  }
  static constexpr u32 MOD2 = MOD << 1;
  static constexpr u32 R = get_r();
  static constexpr u32 R2 = -(u64)(MOD) % MOD;
  static constexpr i32 SMOD = (i32)(MOD);
  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);
  static constexpr u32 mod() { return MOD; }
  static constexpr i32 smod() { return SMOD; }
  constexpr mint_s30() {}
  template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
  constexpr mint_s30(T v): v_(reduce((u64)(v % SMOD + SMOD) * R2)) {}
  constexpr u32 val() const { return norm(reduce(v_)); }
  constexpr i32 sval() const { return (i32)norm(reduce(v_)); }
  constexpr u32 &data() { return v_; }
  constexpr u32 data() const { return v_; }
  constexpr bool is_zero() const { return v_ == 0 || v_ == MOD; }
  template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
  explicit constexpr operator T() const {
    return (T)(val());
  }
  constexpr mint_s30 operator-() const {
    mint_s30 res;
    res.v_ = (MOD2 & -(v_ != 0)) - v_;
    return res;
  }
  constexpr mint_s30 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_s30(x1);
  }
  constexpr mint_s30 &operator+=(const mint_s30 &rhs) {
    v_ += rhs.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &operator-=(const mint_s30 &rhs) {
    v_ -= rhs.v_, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &operator*=(const mint_s30 &rhs) {
    v_ = reduce((u64)(v_)*rhs.v_);
    return *this;
  }
  constexpr mint_s30 &operator/=(const mint_s30 &rhs) {
    return operator*=(rhs.inv());
  }
  friend constexpr mint_s30 operator+(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) += rhs;
  }
  friend constexpr mint_s30 operator-(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) -= rhs;
  }
  friend constexpr mint_s30 operator*(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) *= rhs;
  }
  friend constexpr mint_s30 operator/(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) /= rhs;
  }
  friend constexpr bool operator==(const mint_s30 &lhs, const mint_s30 &rhs) {
    return norm(lhs.v_) == norm(rhs.v_);
  }
  friend constexpr bool operator!=(const mint_s30 &lhs, const mint_s30 &rhs) {
    return norm(lhs.v_) != norm(rhs.v_);
  }
  friend constexpr bool operator<(const mint_s30 &lhs, const mint_s30 &rhs) {
    return lhs.val() < rhs.val();
  }
  friend std::istream &operator>>(std::istream &is, mint_s30 &rhs) {
    i32 x;
    is >> x;
    rhs = mint_s30(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_s30 &rhs) {
    return os << rhs.val();
  }
  friend constexpr u32 abs(mint_s30 const &x) { return x.val(); }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class U, class T = U>
vec<T> conv_naive(vec<U> const &l, vec<U> const &r, usz ans_size) {
  static_assert(sizeof(U) <= sizeof(T));
  usz n = l.size(), m = r.size();
  vec<T> ans(ans_size);
  if (n < m)
    for (usz j = 0; j < m; ++j)
      for (usz i = 0; i < n; ++i) {
        if (i + j >= ans_size) break;
        ans[i + j] += (T)l[i] * (T)r[j];
      }
  else
    for (usz i = 0; i < n; ++i)
      for (usz j = 0; j < m; ++j) {
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
template <class T>
constexpr int cntr0(T x) {
  constexpr int nd = sizeof(T) * 8;
  static_assert(nd <= 128);
  if (x == 0) return nd;
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  if constexpr (nd <= sizeof(unsigned) * 8) return __builtin_ctz(x);
  else if constexpr (nd <= sizeof(unsigned long) * 8) return __builtin_ctzl(x);
  else if constexpr (nd <= nd_ull) return __builtin_ctzll(x);
  else {
    unsigned long long lo = x & (unsigned long long)(-1);
    if (lo != 0) return __builtin_ctzll(lo);
    unsigned long long hi = x >> nd_ull;
    return __builtin_ctzll(hi) + nd_ull;
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
constexpr u64 mul_mod_u(u64 a, u64 b, u64 mod) {
  if (bit::bwidth(a) + bit::bwidth(b) <= 64) return a * b % mod;
  else return (u64)((u128)a * b % mod);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr u64 qpow_mod(u64 a, u64 b, u64 mod) {
  u64 res(1);
  for (a %= mod; b; b >>= 1, a = mul_mod_u(a, a, mod))
    if (b & 1) res = mul_mod_u(res, a, mod);
  return res;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T, class It>
constexpr bool is_proot(T g, T m, It pf_begin, It pf_end) {
  static_assert(std::is_unsigned_v<T>);
  if (!g) return false;
  for (; pf_begin != pf_end; ++pf_begin)
    if (qpow_mod(g, (m - 1) / *pf_begin, m) == 1) return false;
  return true;
}
}  // namespace tifa_libs::math
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
constexpr u32 proot_u32(u32 m) {
  if (m == 2) return 1;
  if (m == 3 || m == 5) return 2;
  if (m == 104857601 || m == 167772161 || m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353 || m == 1004535809) return 3;
  u32 divs[20] = {2};
  u32 cnt = 1, x = (m - 1) / 2;
  x >>= bit::cntr0(x);
  for (u32 i = 3, ed_ = isqrt(x); i <= ed_; i += 2)
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) x /= i;
    }
  if (x > 1) divs[cnt++] = x;
  for (u32 g = 2;; ++g)
    if (is_proot(g, m, divs, divs + cnt)) return g;
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
template <class mint>
struct NTT32 {
  static_assert((mint::mod() & 3) == 1, "MOD must be prime with 4k+1");
  NTT32(): root() {}
  usz size() const { return root.size(); }
  void bzr(usz len) {
    usz n = bit::bceil(len);
    assert((mint::mod() - 1) % n == 0);
    if (n == size()) return;
    root.resize(n);
    root[0] = 1;
    mint w = qpow(G, (mint::mod() - 1) / n);
    for (usz i = 1; i < n; ++i) root[i] = root[i - 1] * w;
  }
  void dif(vec<mint> &f) const {
    usz n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (usz i = n / 2, d = 1; i; i /= 2, d *= 2)
      for (usz j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint u, t;
        for (usz k = 0; k < i; ++k, w += d) {
          f[j | k] = (u = f[j | k]) + (t = f[i | j | k]);
          f[i | j | k] = (u - t) * (*w);
        }
      }
  }
  void dit(vec<mint> &f) const {
    usz n = size();
    assert(f.size() <= n);
    f.resize(n);
    for (usz i = 1, d = n / 2; d; i *= 2, d /= 2)
      for (usz j = 0; j < n; j += i * 2) {
        auto w = root.begin();
        mint t;
        for (usz k = 0; k < i; ++k, w += d) {
          f[i | j | k] = f[j | k] - (t = f[i | j | k] * (*w));
          f[j | k] += t;
        }
      }
    std::reverse(f.begin() + 1, f.end());
    mint t = mint(n).inv();
    for (usz i = 0; i < n; ++i) f[i] *= t;
  }

private:
  static constexpr mint G = proot_u32(mint::mod());
  vec<mint> root;
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint>
vec<mint> conv_ntt32(vec<mint> l, vec<mint> r, usz ans_size) {
  static NTT32<mint> ntt;
  ntt.bzr(std::max(
    {l.size(), r.size(), std::min(l.size() + r.size() - 1, ans_size)}));
  ntt.dif(l);
  ntt.dif(r);
  for (usz i = 0; i < ntt.size(); ++i) l[i] *= r[i];
  ntt.dit(l);
  l.resize(ans_size);
  return l;
}
template <class mint>
vec<mint> conv_ntt32(vec<mint> const &l, vec<mint> const &r) {
  return conv_ntt32(l, r, l.size() + r.size() - 1);
}
template <class mint, class T = u32>
vec<mint> conv_ntt32(vec<T> const &l, vec<T> const &r, usz ans_size) {
  static_assert(sizeof(T) <= 32);
  vec<mint> l_, r_;
  l_.reserve(l.size());
  r_.reserve(r.size());
  for (auto i : l) l_.push_back(i);
  for (auto i : r) r_.push_back(i);
  return conv_ntt32(l_, r_, ans_size);
}
template <class mint, class T = u32>
vec<mint> conv_ntt32(vec<T> const &l, vec<T> const &r) {
  return conv_ntt32<mint, T>(l, r, l.size() + r.size() - 1);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T>
vec<u128> conv_u128(vec<T> const &l, vec<T> const &r, usz ans_size) {
  static constexpr u32 m0 = 167772161, m1 = 469762049, m2 = 754974721;
  using mint0 = mint_s30<m0>;
  using mint1 = mint_s30<m1>;
  using mint2 = mint_s30<m2>;
  static constexpr u32 r01 = mint1(m0).inv().val(), r02 = mint2(m0).inv().val(),
                       r12 = mint2(m1).inv().val(),
                       r02r12 = (u64)r02 * r12 % m2;
  static constexpr u64 w1 = m0, w2 = (u64)m0 * m1;
  if (l.empty() && r.empty()) return {};
  if (std::min(l.size(), r.size()) < 128) return conv_naive<T, u128>(l, r);
  vec<mint0> d0 = conv_ntt32<mint0>(l, r, ans_size);
  vec<mint1> d1 = conv_ntt32<mint1>(l, r, ans_size);
  vec<mint2> d2 = conv_ntt32<mint2>(l, r, ans_size);
  vec<u128> ret(ans_size);
  for (usz i = 0; i < ans_size; ++i) {
    u64 n1 = d1[i].val(), n2 = d2[i].val(), a = d0[i].val(),
        b = (n1 + m1 - a) * r01 % m1;
    u128 c = ((n2 + m2 - a) * r02r12 + (m2 - b) * r12) % m2;
    ret[i] = a + b * w1 + c * w2;
  }
  return ret;
}
template <class T>
vec<u128> conv_u128(vec<T> const &l, vec<T> const &r) {
  return conv_u128<T>(l, r, l.size() + r.size() - 1);
}
}  // namespace tifa_libs::math
namespace tifa_libs::bit {
template <class T>
constexpr T bswap(T x) {
  if constexpr (sizeof(T) == 2) return __builtin_bswap16(x);
  if constexpr (sizeof(T) == 4) return __builtin_bswap32(x);
  if constexpr (sizeof(T) == 8) return __builtin_bswap64(x);
  if constexpr (sizeof(T) == 16) return __builtin_bswap128(x);
}
}  // namespace tifa_libs::bit
namespace tifa_libs::bit {
enum class endian {
  little = __ORDER_LITTLE_ENDIAN__,
  big = __ORDER_BIG_ENDIAN__,
  native = __BYTE_ORDER__
};
}
namespace tifa_libs {
constexpr u32 str2uint_si64(const char * const s) {
  u64 _ = *((u64 *)(s));
  if (bit::endian::native == bit::endian::big) _ = bit::bswap(_);
  _ = (_ & 0x0F0F0F0F0F0F0F0F) * 2561 >> 8;
  _ = (_ & 0x00FF00FF00FF00FF) * 6553601 >> 16;
  _ = (_ & 0x0000FFFF0000FFFF) * 42949672960001 >> 32;
  return (u32)_;
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
using is_s128 = typename std::conditional<std::is_same_v<T, __int128_t> ||
                                            std::is_same_v<T, __int128>,
                                          std::true_type,
                                          std::false_type>::type;
template <class T>
using is_u128 =
  typename std::conditional<std::is_same_v<T, __uint128_t> ||
                              std::is_same_v<T, unsigned __int128>,
                            std::true_type,
                            std::false_type>::type;
template <class T>
using to_u128 = typename std::
  conditional<std::is_same_v<T, __int128_t>, __uint128_t, unsigned __int128>;
template <class T>
using is_int =
  typename std::conditional_t<std::is_integral_v<T> || is_s128<T>::value ||
                                is_u128<T>::value,
                              std::true_type,
                              std::false_type>;
template <class T>
using is_sint =
  typename std::conditional_t<is_s128<T>::value ||
                                (is_int<T>::value && std::is_signed_v<T>),
                              std::true_type,
                              std::false_type>;
template <class T>
using to_uint =
  typename std::conditional_t<std::is_same_v<T, i128>,
                              to_u128<T>,
                              typename std::conditional_t<std::is_signed_v<T>,
                                                          std::make_unsigned<T>,
                                                          std::common_type<T>>>;
}  // namespace tifa_libs
namespace tifa_libs::math {
class mpi {
  static constexpr u32 D = 100000000, lgD = 8;
  bool neg;
  vec<u32> dt;

public:
  explicit mpi(): neg(false), dt() {}
  mpi(bool n, vec<u32> const &d): neg(n), dt(d) {}
  template <class T, std::enable_if_t<is_int<T>::value> * = nullptr>
  mpi(T x): neg(false) {
    if constexpr (is_sint<T>::value)
      if (x < 0) neg = true, x = -x;
    while (x) dt.push_back(u32(typename to_uint<T>::type(x) % D)), x /= D;
  }
  mpi(std::string s): neg(false) {
    assert(!s.empty());
    if (s.size() == 1u) {
      if (s[0] == '0') return;
      assert(isdigit(s[0]));
      dt.push_back(s[0] & 15);
      return;
    }
    usz l = 0;
    if (s[0] == '-') ++l, neg = true;
    u32 _ = 0;
    if ((s.size() - l) & 7) {
      for (usz i = l; i < l + ((s.size() - l) & 7); ++i)
        _ = _ * 10 + (s[i] & 15);
      l += (s.size() - l) & 7;
    }
    if (l) s = s.substr(l);
    for (usz ie = s.size(); ie >= lgD; ie -= lgD)
      dt.push_back(str2uint_si64(s.data() + ie - lgD));
    if (_) dt.push_back(_);
  }
  static constexpr u32 digit() { return D; }
  static constexpr u32 log_digit() { return lgD; }
  void set_neg(bool s) { neg = s; }
  bool is_neg() const { return neg; }
  vec<u32> &data() { return dt; }
  vec<u32> data() const { return dt; }
  friend mpi operator+(mpi const &lhs, mpi const &rhs) {
    if (lhs.neg == rhs.neg) return {lhs.neg, add_(lhs.dt, rhs.dt)};
    if (leq_(lhs.dt, rhs.dt)) {
      auto c = sub_(rhs.dt, lhs.dt);
      return {is0_(c) ? false : rhs.neg, c};
    }
    auto c = sub_(lhs.dt, rhs.dt);
    return {is0_(c) ? false : lhs.neg, c};
  }
  friend mpi operator-(mpi const &lhs, mpi const &rhs) { return lhs + (-rhs); }
  friend mpi operator*(mpi const &lhs, mpi const &rhs) {
    auto c = mul_(lhs.dt, rhs.dt);
    bool n = is0_(c) ? false : (lhs.neg ^ rhs.neg);
    return {n, c};
  }
  friend ptt<mpi> divmod(mpi const &lhs, mpi const &rhs) {
    auto dm = divmod_newton_(lhs.dt, rhs.dt);
    return {mpi{is0_(dm.first) ? false : lhs.neg != rhs.neg, dm.first},
            mpi{is0_(dm.second) ? false : lhs.neg, dm.second}};
  }
  friend mpi operator/(mpi const &lhs, mpi const &rhs) {
    return divmod(lhs, rhs).first;
  }
  friend mpi operator%(mpi const &lhs, mpi const &rhs) {
    return divmod(lhs, rhs).second;
  }
  mpi &operator+=(mpi const &rhs) { return (*this) = (*this) + rhs; }
  mpi &operator-=(mpi const &rhs) { return (*this) = (*this) - rhs; }
  mpi &operator*=(mpi const &rhs) { return (*this) = (*this) * rhs; }
  mpi &operator/=(mpi const &rhs) { return (*this) = (*this) / rhs; }
  mpi &operator%=(mpi const &rhs) { return (*this) = (*this) % rhs; }
  mpi operator-() const {
    if (is_zero()) return *this;
    return {!neg, dt};
  }
  mpi operator+() const { return *this; }
  friend mpi abs(mpi const &m) { return {false, m.dt}; }
  bool is_zero() const { return is0_(dt); }
  friend bool operator==(mpi const &lhs, mpi const &rhs) {
    return lhs.neg == rhs.neg && lhs.dt == rhs.dt;
  }
  friend bool operator!=(mpi const &lhs, mpi const &rhs) {
    return !(lhs == rhs);
  }
  friend bool operator<(mpi const &lhs, mpi const &rhs) {
    return lhs == rhs ? false : neq_lt_(lhs, rhs);
  }
  friend bool operator<=(mpi const &lhs, mpi const &rhs) {
    return lhs == rhs ? true : neq_lt_(lhs, rhs);
  }
  friend bool operator>(mpi const &lhs, mpi const &rhs) {
    return lhs == rhs ? false : neq_lt_(rhs, lhs);
  }
  friend bool operator>=(mpi const &lhs, mpi const &rhs) {
    return lhs == rhs ? true : neq_lt_(rhs, lhs);
  }
  usz size() const { return dt.size(); }
  void shrink() { shrink_(dt); }
  std::string to_str() const {
    if (is_zero()) return "0";
    std::string res;
    if (neg) res.push_back('-');
    for (usz i = size() - 1; ~i; --i) res += itos_((u32)dt[i], i != size() - 1);
    return res;
  }
  i64 to_i64() const {
    i64 res = to_i64_(dt);
    return neg ? -res : res;
  }
  i128 to_i128() const {
    i128 res = 0;
    for (usz i = dt.size() - 1; ~i; --i) res = res * D + dt[i];
    return neg ? -res : res;
  }
  friend std::istream &operator>>(std::istream &is, mpi &m) {
    std::string s;
    is >> s;
    m = mpi{s};
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, mpi const &m) {
    return os << m.to_str();
  }

private:
  static bool lt_(vec<u32> const &a, vec<u32> const &b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (usz i = a.size() - 1; ~i; --i)
      if (a[i] != b[i]) return a[i] < b[i];
    return false;
  }
  static bool leq_(vec<u32> const &a, vec<u32> const &b) {
    return a == b || lt_(a, b);
  }
  static bool neq_lt_(mpi const &lhs, mpi const &rhs) {
    assert(lhs != rhs);
    if (lhs.neg != rhs.neg) return lhs.neg;
    return lt_(lhs.dt, rhs.dt) ^ lhs.neg;
  }
  static bool is0_(vec<u32> const &a) { return a.empty(); }
  static bool is1_(vec<u32> const &a) { return a.size() == 1 && a[0] == 1; }
  static void shrink_(vec<u32> &a) {
    while (a.size() && !a.back()) a.pop_back();
  }
  static vec<u32> add_(vec<u32> const &a, vec<u32> const &b) {
    vec<u32> c(std::max(a.size(), b.size()) + 1);
    for (usz i = 0; i < a.size(); ++i) c[i] += a[i];
    for (usz i = 0; i < b.size(); ++i) c[i] += b[i];
    for (usz i = 0; i < c.size() - 1; ++i)
      if (c[i] >= D) c[i] -= D, c[i + 1]++;
    shrink_(c);
    return c;
  }
  static vec<u32> sub_(vec<u32> const &a, vec<u32> const &b) {
    assert(leq_(b, a));
    vec<u32> c = a;
    u32 borrow = 0;
    for (usz i = 0; i < a.size(); ++i) {
      if (i < b.size()) borrow += b[i];
      c[i] -= borrow;
      borrow = 0;
      if ((i32)c[i] < 0) c[i] += D, borrow = 1;
    }
    assert(!borrow);
    shrink_(c);
    return c;
  }
  static vec<u32> mul_3ntt_(vec<u32> const &a, vec<u32> const &b) {
    if (a.empty() || b.empty()) return {};
    auto m = conv_u128(a, b);
    vec<u32> c;
    c.reserve(m.size() + 3);
    u128 x = 0;
    for (usz i = 0;; ++i) {
      if (i >= m.size() && !x) break;
      if (i < m.size()) x += m[i];
      c.push_back(u32(x % D));
      x /= D;
    }
    shrink_(c);
    return c;
  }
  static vec<u32> mul_bf_(vec<u32> const &a, vec<u32> const &b) {
    if (a.empty() || b.empty()) return {};
    vec<u64> prod(a.size() + b.size() - 1 + 1);
    for (usz i = 0; i < a.size(); ++i)
      for (usz j = 0; j < b.size(); ++j)
        if ((prod[i + j] += (u64)a[i] * b[j]) >= (u64)4 * D * D)
          prod[i + j] -= (u64)4 * D * D, prod[i + j + 1] += (u64)4 * D;
    vec<u32> c(prod.size() + 1);
    u64 x = 0;
    usz i = 0;
    for (; i < prod.size(); ++i) x += prod[i], c[i] = u32(x % D), x /= D;
    while (x) c[i] = u32(x % D), x /= D, ++i;
    shrink_(c);
    return c;
  }
  static vec<u32> mul_(vec<u32> const &a, vec<u32> const &b) {
    if (is0_(a) || is0_(b)) return {};
    if (is1_(a)) return b;
    if (is1_(b)) return a;
    if (std::min(a.size(), b.size()) <= 128)
      return a.size() < b.size() ? mul_bf_(b, a) : mul_bf_(a, b);
    return mul_3ntt_(a, b);
  }
  static ptt<vec<u32>> divmod_li_(vec<u32> const &a, vec<u32> const &b) {
    assert(a.size() <= 2 && b.size() == 1);
    i64 va = to_i64_(a);
    u32 vb = b[0];
    return {itov_(va / vb), itov_(va % vb)};
  }
  static ptt<vec<u32>> divmod_ll_(vec<u32> const &a, vec<u32> const &b) {
    assert(a.size() <= 2 && b.size() && b.size() <= 2);
    i64 va = to_i64_(a), vb = to_i64_(b);
    return {itov_(va / vb), itov_(va % vb)};
  }
  static ptt<vec<u32>> divmod_1e8_(vec<u32> const &a, vec<u32> const &b) {
    assert(b.size() == 1);
    if (b[0] == 1) return {a, {}};
    if (a.size() <= 2) return divmod_li_(a, b);
    vec<u32> quo(a.size());
    u64 d = 0;
    u32 b0 = b[0];
    for (usz i = a.size() - 1; ~i; --i) {
      d = d * D + a[i];
      assert(d < (u64)D * b0);
      quo[i] = u32(d / b0);
      d = d % b0;
    }
    shrink_(quo);
    return {quo, d ? vec<u32>{u32(d)} : vec<u32>{}};
  }
  static ptt<vec<u32>> divmod_bf_(vec<u32> const &a, vec<u32> const &b) {
    assert(!is0_(b) && b.size());
    if (b.size() == 1) return divmod_1e8_(a, b);
    if (std::max(a.size(), b.size()) <= 2) return divmod_ll_(a, b);
    if (lt_(a, b)) return {{}, a};
    u32 norm = D / (b.back() + 1);
    vec<u32> x = mul_(a, {norm}), y = mul_(b, {norm});
    u32 yb = y.back();
    vec<u32> quo(x.size() - y.size() + 1),
      rem(x.end() - (int)y.size(), x.end());
    for (usz i = quo.size() - 1; ~i; --i) {
      if (rem.size() == y.size()) {
        if (leq_(y, rem)) quo[i] = 1, rem = sub_(rem, y);
      } else if (rem.size() > y.size()) {
        assert(y.size() + 1 == rem.size());
        u32 q =
          (u32)(((u64)rem[rem.size() - 1] * D + rem[rem.size() - 2]) / yb);
        vec<u32> yq = mul_(y, {q});
        while (lt_(rem, yq)) --q, yq = sub_(yq, y);
        rem = sub_(rem, yq);
        while (leq_(y, rem)) ++q, rem = sub_(rem, y);
        quo[i] = q;
      }
      if (i) rem.insert(rem.begin(), x[i - 1]);
    }
    shrink_(quo), shrink_(rem);
    auto [q2, r2] = divmod_1e8_(rem, {norm});
    assert(is0_(r2));
    return {quo, q2};
  }
  static vec<u32> inv_(vec<u32> const &a, u32 deg) {
    assert(!a.empty() && D / 2 <= a.back() and a.back() < D);
    u32 k = deg, c = (u32)a.size();
    while (k > 64) k = (k + 1) / 2;
    vec<u32> z(usz(c + k + 1));
    z.back() = 1;
    z = divmod_bf_(z, a).first;
    while (k < deg) {
      vec<u32> s = mul_(z, z);
      s.insert(s.begin(), 0);
      u32 d = std::min(c, 2 * k + 1);
      vec<u32> t{a.end() - d, a.end()}, u = mul_(s, t);
      u.erase(u.begin(), u.begin() + d);
      vec<u32> w(usz(k + 1)), w2 = add_(z, z);
      std::copy(w2.begin(), w2.end(), std::back_inserter(w));
      (z = sub_(w, u)).erase(z.begin());
      k *= 2;
    }
    z.erase(z.begin(), z.begin() + k - deg);
    return z;
  }
  static ptt<vec<u32>> divmod_newton_(vec<u32> const &a, vec<u32> const &b) {
    assert(!is0_(b));
    if (b.size() <= 64) return divmod_bf_(a, b);
    if ((int)(a.size() - b.size()) <= 64) return divmod_bf_(a, b);
    u32 norm = D / (b.back() + 1);
    vec<u32> x = mul_(a, {norm}), y = mul_(b, {norm});
    u32 s = (u32)x.size(), t = (u32)y.size();
    u32 deg = s + 2 - t;
    vec<u32> z = inv_(y, deg), q = mul_(x, z);
    q.erase(q.begin(), q.begin() + t + deg);
    vec<u32> yq = mul_(y, {q});
    while (lt_(x, yq)) q = sub_(q, {1}), yq = sub_(yq, y);
    vec<u32> r = sub_(x, yq);
    while (leq_(y, r)) q = add_(q, {1}), r = sub_(r, y);
    shrink_(q), shrink_(r);
    auto [q2, r2] = divmod_1e8_(r, {norm});
    assert(is0_(r2));
    return {q, q2};
  }
  static std::string itos_(u32 x, bool zero_padding) {
    assert(x < D);
    std::string res;
    for (u32 i = 0; i < lgD; ++i) res.push_back(char(48 + x % 10)), x /= 10;
    if (!zero_padding) {
      while (res.size() && res.back() == '0') res.pop_back();
      assert(!res.empty());
    }
    std::reverse(res.begin(), res.end());
    return res;
  }
  template <class T, std::enable_if_t<is_int<T>::value> * = nullptr>
  static vec<u32> itov_(T x) {
    if constexpr (is_sint<T>::value) assert(x >= 0);
    vec<u32> res;
    while (x) res.push_back((u32)(x % D)), x /= D;
    return res;
  }
  static i64 to_i64_(vec<u32> const &a) {
    i64 res = 0;
    for (usz i = a.size() - 1; ~i; --i) res = res * D + a[i];
    return res;
  }
};
}  // namespace tifa_libs::math
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::math::mpi a, b;
  std::cin >> a >> b;
  std::cout << a - b << '\n';
  return 0;
}
