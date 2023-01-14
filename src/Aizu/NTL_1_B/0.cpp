#include <bits/stdc++.h>
using i32 = int32_t;
using u32 = uint32_t;
using u64 = uint64_t;
#undef assert
#define assert(x) 42
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
  template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
  mint_d31(T v): v_(tsf(norm((i32)(v % (T)SMOD)))) {}
  u32 val() const {
    u32 h = redc(v_ >> OFFSET);
    return ((h - v_) * R & MASK) * MOD_ODD + h;
  }
  i32 sval() const { return (i32)val(); }
  constexpr u32 &data() { return v_; }
  constexpr u32 data() const { return v_; }
  bool is_zero() const { return v_ == 0; }
  template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
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
namespace tifa_libs::math {
template <class T>
constexpr T qpow(T a, u64 b) {
  T res(1);
  for (; b; b >>= 1, a *= a)
    if (b & 1) res *= a;
  return res;
}
}  // namespace tifa_libs::math
constexpr u64 MOD = 1'000'000'007;
using mint = tifa_libs::math::mint_d31<-1>;
int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  mint m;
  u64 n;
  std::cin >> m >> n;
  std::cout << tifa_libs::math::qpow(m, n).val() << '\n';
  return 0;
}
