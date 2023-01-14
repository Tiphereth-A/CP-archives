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
namespace tifa_libs {
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
#include <bits/stdc++.h>
using i128 = __int128_t;
using u128 = __uint128_t;
#undef assert
#define assert(x) 42
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
using is_uint =
  typename std::conditional_t<is_u128<T>::value ||
                                (is_int<T>::value && std::is_unsigned_v<T>),
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
template <class T, std::enable_if_t<is_uint<T>::value> * = nullptr>
constexpr T gcd_u128(T a, T b) {
  if (!a) return b;
  if (!b) return a;
  const int i = bit::cntr0(a), j = bit::cntr0(b), k = std::min(i, j);
  a >>= i;
  b >>= j;
  while (true) {
    if (a > b) std::swap(a, b);
    b -= a;
    if (!b) return a << k;
    b >>= bit::cntr0(b);
  }
}
template <class T, std::enable_if_t<is_int<T>::value> * = nullptr>
constexpr T gcd_128(T a, T b) {
  return gcd_u128<typename to_uint<T>::type>(abs(a), abs(b));
}
}  // namespace tifa_libs::math
std::istream &operator>>(std::istream &is, i128 &n) {
  bool neg = false;
  while (!neg && !isdigit(is.peek())) {
    if (is.peek() == '-') neg = true;
    is.get();
  }
  n = 0;
  while (isdigit(is.peek())) (n *= 10) += is.get() & 15;
  if (neg) n = -n;
  return is;
}
std::istream &operator>>(std::istream &is, u128 &n) {
  while (!isdigit(is.peek())) is.get();
  n = 0;
  while (isdigit(is.peek())) (n *= 10) += is.get() & 15;
  return is;
}
std::ostream &operator<<(std::ostream &os, u128 n) {
  if (n > 9) os << n / 10;
  os << (uint_fast32_t)(n % 10);
  return os;
}
std::ostream &operator<<(std::ostream &os, i128 n) {
  if (n < 0) {
    os << '-';
    n = -n;
  }
  return os << (u128)n;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i128 x, y;
  std::cin >> x >> y;
  std::cout << tifa_libs::math::gcd_128(x, y) << '\n';
  return 0;
}
