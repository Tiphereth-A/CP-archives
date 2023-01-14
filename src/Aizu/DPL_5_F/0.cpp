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
#include <bits/stdc++.h>
using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::math {
constexpr u64 mul_mod_u(u64 a, u64 b, u64 mod) {
  if (bit::bwidth(a) + bit::bwidth(b) <= 64) return a * b % mod;
  else return (u64)((u128)a * b % mod);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
vec<u64> fact_mod_gen(usz sz, u64 mod) {
  vec<u64> ans(sz, 1);
  for (usz i = 2; i < sz; ++i) ans[i] = mul_mod_u(ans[i - 1], i, mod);
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
vec<u64> inv_mod_gen(usz sz, u64 mod) {
  vec<u64> ans(sz, 1);
  for (usz i = 2; i < sz; ++i)
    ans[i] = mul_mod_u(mod - mod / i, ans[mod % i], mod);
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
vec<u64> ifact_mod_gen(usz sz, u64 mod, vec<u64> const &inv) {
  vec<u64> ans = inv;
  for (usz i = 2; i < sz; ++i) ans[i] = mul_mod_u(ans[i], ans[i - 1], mod);
  return ans;
}
vec<u64> ifact_mod_gen(usz sz, u64 mod) {
  return ifact_mod_gen(sz, mod, inv_mod_gen(sz, mod));
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
class Binom {
  u64 m_;

public:
  const vec<u64> fact, ifact;
  Binom(u64 mod, usz max_m)
    : m_(mod), fact(fact_mod_gen(max_m, mod)),
      ifact(ifact_mod_gen(max_m, mod)) {}
  constexpr u64 mod() const { return m_; }
  u64 mCn(u64 m, u64 n) const {
    return m < n ? 0 :
                   mul_mod_u(mul_mod_u(fact[(usz)m], ifact[(usz)n], m_),
                             ifact[(usz)(m - n)],
                             m_);
  }
  u64 mCn(i64 m, i64 n) const {
    return m < n || n < 0 ? 0 : mCn((u64)m, (u64)n);
  }
  u64 mPn(u64 m, u64 n) const {
    return m < n ? 0 : mul_mod_u(fact[(usz)m], ifact[(usz)(m - n)], m_);
  }
  u64 mPn(i64 m, i64 n) const {
    return m < n || n < 0 ? 0 : mPn((u64)m, (u64)n);
  }
  u64 mHn(u64 m, u64 n) const { return n <= 0 ? n == 0 : mCn(m + n - 1, n); }
  u64 mHn(i64 m, i64 n) const {
    return m < 0 || n <= 0 ? n == 0 : mHn((u64)m, (u64)n);
  }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class mint>
mint ball_box_idl(u64 ball, u64 box, Binom const &binom) {
  return binom.mCn(ball - 1, box - 1);
}
}  // namespace tifa_libs::math
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
constexpr u32 MOD = 1000000000 + 7;
using mint = tifa_libs::math::mint_s30<MOD>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n, k;
  std::cin >> n >> k;
  tifa_libs::math::Binom binom(MOD, 2001);
  std::cout << tifa_libs::math::ball_box_idl<mint>(n, k, binom) << '\n';
  return 0;
}
