#include <bits/stdc++.h>
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;
#undef assert
#define assert(x) 42
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
template <class T, std::enable_if_t<is_sint<T>::value> * = nullptr>
constexpr T safe_mod(T x, typename to_uint<T>::type mod) {
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
  static constexpr u32 mod() { return MOD; }
  static constexpr mint_ss raw(u32 v) {
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
  constexpr u32 val() const { return v_; }
  constexpr i32 sval() const { return (i32)v_; }
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
using mint = tifa_libs::math::mint_ss<MOD>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  mint m;
  u64 n;
  std::cin >> m >> n;
  std::cout << tifa_libs::math::qpow(m, n).val() << '\n';
  return 0;
}
