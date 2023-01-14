#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>
namespace tifa_libs {
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
}  // namespace tifa_libs
#include <limits>
namespace tifa_libs::bit {
template <typename T>
constexpr int cntr0(T x) {
  constexpr int nd = sizeof(T) * 8;
  if (x == 0) return nd;
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u) return __builtin_ctz(x);
  else if constexpr (nd <= nd_ul) return __builtin_ctzl(x);
  else if constexpr (nd <= nd_ull) return __builtin_ctzll(x);
  else {
    static_assert(nd <= (2 * nd_ull),
                  "Maximum supported integer size is 128-bit");
    unsigned long long lo = x & (unsigned long long)(-1);
    if (lo != 0) return __builtin_ctzll(lo);
    unsigned long long hi = x >> nd_ull;
    return __builtin_ctzll(hi) + nd_ull;
  }
}
}  // namespace tifa_libs::bit
namespace tifa_libs::bit {
template <typename T>
constexpr int cntl0(T x) {
  constexpr int nd = sizeof(T) * 8;
  if (x == 0) return nd;
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u) return __builtin_clz(x) - (nd_u - nd);
  else if constexpr (nd <= nd_ul) return __builtin_clzl(x) - (nd_ul - nd);
  else if constexpr (nd <= nd_ull) return __builtin_clzll(x) - (nd_ull - nd);
  else {
    static_assert(nd <= (2 * nd_ull),
                  "Maximum supported integer size is 128-bit");
    unsigned long long hi = x >> nd_ull;
    if (hi != 0) return __builtin_clzll(hi) - ((2 * nd_ull) - nd);
    unsigned long long lo = x & (unsigned long long)(-1);
    return (nd - nd_ull) + __builtin_clzll(lo);
  }
}
}  // namespace tifa_libs::bit
namespace tifa_libs::bit {
template <typename T>
constexpr int bwidth(T x) {
  return (int)sizeof(T) * 8 - cntl0(x);
}
}  // namespace tifa_libs::bit
namespace tifa_libs::math {
constexpr u64 mul_mod(i64 a, i64 b, u64 mod) {
  if (bit::bwidth((u64)(a < 0 ? -a : a)) + bit::bwidth((u64)(b < 0 ? -b : b)) <
      64)
    return (u64)((a * b % (i64)mod) + (i64)mod) % mod;
  else return (u64)((i128)a * b % mod + mod) % mod;
}
constexpr u64 mul_mod(u64 a, u64 b, u64 mod) {
  if (bit::bwidth(a) + bit::bwidth(b) <= 64) return a * b % mod;
  else return (u64)((u128)a * b % mod);
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
constexpr u64 qpow_mod(u64 a, u64 b, u64 mod) {
  u64 res(1);
  for (a %= mod; b; b >>= 1, a = mul_mod(a, a, mod))
    if (b & 1) res = mul_mod(res, a, mod);
  return res;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr bool is_prime(u64 n) {
  if (n <= 2) return n == 2;
  if (~n & 1) return false;
  if (n < 8) return true;
  constexpr u64 bases[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  u64 d = (n - 1) >> bit::cntr0(n - 1);
  for (u64 i : bases) {
    if (n == i) return true;
    u64 t = d, y = qpow_mod(i, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = mul_mod(y, y, n);
      t <<= 1;
    }
    if (y != n - 1 && (~t & 1)) return false;
  }
  return true;
}
}  // namespace tifa_libs::math
#include <vector>
namespace tifa_libs::math {
class FactSeq {
  std::vector<u64> data;

public:
  FactSeq(u64 mod, u64 sz): data(sz) {
    assert(sz > 1 && mod >= sz);
    data[0] = 1;
    for (u64 i = 1; i < sz; ++i) data[i] = mul_mod(data[i - 1], i, mod);
  }
  u64 operator[](size_t n) const { return data[n]; }
  u64 &operator[](size_t n) { return data[n]; }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
class InvSeq {
  std::vector<u64> data;

public:
  InvSeq(u64 mod, u64 sz): data(sz, 1) {
    assert(sz > 1 && mod >= sz);
    for (u64 i = 2; i < sz; ++i)
      data[i] = mul_mod(mod - mod / i, data[mod % i], mod);
  }
  u64 operator[](size_t n) const { return data[n]; }
  u64 &operator[](size_t n) { return data[n]; }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
class InvFactSeq {
  InvSeq data;

public:
  InvFactSeq(u64 mod, u64 sz): data(mod, sz) {
    for (u64 i = 2; i < sz; ++i) data[i] = mul_mod(data[i], data[i - 1], mod);
  }
  u64 operator[](size_t n) const { return data[n]; }
  u64 &operator[](size_t n) { return data[n]; }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
class MCN {
  u64 m_;
  FactSeq fact;
  InvFactSeq inv_fact;

public:
  MCN(u64 mod, u64 m_n_max)
    : m_(mod), fact(mod, m_n_max), inv_fact(mod, m_n_max) {}
  constexpr u64 mod() const { return m_; }
  u64 operator()(i64 m, i64 n) const {
    return m < n || n < 0 ?
             0 :
             mul_mod(mul_mod(fact[(size_t)m], inv_fact[(size_t)n], m_),
                     inv_fact[(size_t)(m - n)],
                     m_);
  }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
class Lucas {
  MCN mCn;
  u64 lucas__(const MCN &mCn, u64 m, u64 n) const {
    const u64 mod = mCn.mod();
    return n == 0 ? 1 :
                    mul_mod(mCn((i64)(m % mod), (i64)(n % mod)),
                            lucas__(mCn, m / mod, n / mod),
                            mod);
  }

public:
  explicit Lucas(u64 mod): mCn(mod, mod) { assert(mod); }
  u64 operator()(i64 m, i64 n) const {
    return m < n || n < 0 ? 0 : lucas__(mCn, (u64)m, (u64)n);
  }
};
}  // namespace tifa_libs::math
#include <iostream>
int main() {
  tifa_libs::u32 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::u64 n, m, p;
    std::cin >> n >> m >> p;
    tifa_libs::math::Lucas mCn(p);
    std::cout << mCn(n + m, n) << '\n';
  }
  return 0;
}
