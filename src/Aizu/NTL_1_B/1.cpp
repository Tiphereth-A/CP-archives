#include <bits/stdc++.h>
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
#undef assert
#define assert(x) 42
namespace tifa_libs::math {
template <int>
class mint_d63 {
  u64 v_{};
  static u64 mul_high(u64 x, u64 y) {
    u64 a = x >> 32, b = (u32)(x), c = y >> 32, d = (u32)(y), ad = a * d,
        bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) +
           (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static u64 redc_mul(u64 x, u64 y) {
    u64 res = mul_high(x, y) - mul_high(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static u64 norm(i64 x) { return (u64)(x + (i64)(MOD & (u64)(-(x < 0)))); }
  static inline u64 MOD, R, R2;
  static inline i64 SMOD;

public:
  static void set_mod(u64 m) {
    assert(!((m & 1) == 0 || m == 1 || m >> 63));
    MOD = m;
    {
      u64 t = 2, iv = MOD * (t - MOD * MOD);
      iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;
      R = iv * (t - MOD * iv);
    }
    {
      R2 = -MOD % MOD;
      for (int i = 0; i != 64; ++i)
        if ((R2 *= 2) >= MOD) R2 -= MOD;
    }
    SMOD = (i64)(MOD);
  }
  static u64 mod() { return MOD; }
  static i64 smod() { return SMOD; }
  mint_d63() {}
  template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
  mint_d63(T v): v_(redc_mul(norm(i64(v % (T)SMOD)), R2)) {}
  u64 val() const {
    u64 res = -mul_high(v_ * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  i64 sval() const { return val(); }
  constexpr u64 &data() { return v_; }
  constexpr u64 data() const { return v_; }
  bool is_zero() const { return v_ == 0; }
  template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
  explicit operator T() const {
    return (T)(val());
  }
  mint_d63 operator-() const {
    mint_d63 res;
    res.v_ = (MOD & -(v_ != 0)) - v_;
    return res;
  }
  mint_d63 inv() const {
    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_d63(x1);
  }
  mint_d63 &operator+=(const mint_d63 &rhs) {
    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  mint_d63 &operator-=(const mint_d63 &rhs) {
    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  mint_d63 &operator*=(const mint_d63 &rhs) {
    v_ = redc_mul(v_, rhs.v_);
    return *this;
  }
  mint_d63 &operator/=(const mint_d63 &rhs) { return operator*=(rhs.inv()); }
  friend mint_d63 operator+(const mint_d63 &lhs, const mint_d63 &rhs) {
    return mint_d63(lhs) += rhs;
  }
  friend mint_d63 operator-(const mint_d63 &lhs, const mint_d63 &rhs) {
    return mint_d63(lhs) -= rhs;
  }
  friend mint_d63 operator*(const mint_d63 &lhs, const mint_d63 &rhs) {
    return mint_d63(lhs) *= rhs;
  }
  friend mint_d63 operator/(const mint_d63 &lhs, const mint_d63 &rhs) {
    return mint_d63(lhs) /= rhs;
  }
  friend bool operator==(const mint_d63 &lhs, const mint_d63 &rhs) {
    return lhs.v_ == rhs.v_;
  }
  friend bool operator!=(const mint_d63 &lhs, const mint_d63 &rhs) {
    return lhs.v_ != rhs.v_;
  }
  friend constexpr bool operator<(const mint_d63 &lhs, const mint_d63 &rhs) {
    return lhs.val() < rhs.val();
  }
  friend std::istream &operator>>(std::istream &is, mint_d63 &rhs) {
    i64 x;
    is >> x;
    rhs = mint_d63(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_d63 &rhs) {
    return os << rhs.val();
  }
  friend constexpr u64 abs(mint_d63 const &x) { return x.val(); }
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
using mint = tifa_libs::math::mint_d63<-1>;
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
