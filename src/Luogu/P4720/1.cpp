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
#include <tuple>
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
constexpr u64 inverse(u64 n, u64 mod) {
  auto [g, x, y] = exgcd((i64)(n % mod), (i64)mod);
  assert(g == 1);
  return x > 0 ? (u64)x : (u64)x + mod;
}
}  // namespace tifa_libs::math
#include <limits>
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
#include <functional>
#include <numeric>
#include <vector>
namespace tifa_libs::math {
u64 crt(const std::vector<u64> &b, const std::vector<u64> &m) {
  assert(b.size() == m.size());
  u64 M = std::reduce(m.begin(), m.end(), (u64)1, std::multiplies<u64>{}),
      ans = 0;
  for (size_t i = 0; i < b.size(); ++i) {
    u64 Mi = M / m[i], Ni = inverse(Mi, m[i]);
    ans = (ans + mul_mod(mul_mod(b[i], Mi, M), Ni, M)) % M;
  }
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
constexpr u32 isqrt(u64 x) {
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
class ExLucas {
  std::vector<std::pair<u64, u64>> factors_mod{};
  std::vector<std::vector<u64>> facts{}, inv_facts{};
  void push_back(u64 base, u64 factor_mod) {
    factors_mod.emplace_back(base, factor_mod);
    facts.emplace_back(factor_mod);
    inv_facts.emplace_back(factor_mod);
    auto &fact = facts.back(), &inv_fact = inv_facts.back();
    fact[0] = fact[1] = inv_fact[0] = inv_fact[1] = 1;
    for (u64 i = 2; i < factor_mod; ++i) {
      fact[i] = fact[i - 1];
      if (i % base) fact[i] = mul_mod(fact[i], i, factor_mod);
    }
    std::vector<u64> __(factor_mod);
    __[0] = __[1] = 1;
    for (u64 i = 2; i < factor_mod; ++i)
      __[i] = mul_mod(__[i - 1], fact[i], factor_mod);
    u64 inv_ = inverse(__.back(), factor_mod);
    for (u64 i = factor_mod - 1; i > 1; --i) {
      inv_fact[i] = mul_mod(inv_, __[i - 1], factor_mod);
      inv_ = mul_mod(inv_, fact[i], factor_mod);
    }
  }
  std::pair<u64, u64>
  calc_(u64 n, u64 base, u64 mod, const std::vector<u64> &v) const {
    if (n == 0) return {1, 0};
    u64 _1 = mul_mod(qpow_mod(v.back(), n / mod, mod), v[n % mod], mod),
        _2 = n / base;
    auto &&[res, cnt] = calc_(n / base, base, mod, v);
    return {mul_mod(res, _1, mod), _2 + cnt};
  }
  u64 single_mCn(size_t idx, u64 m, u64 n) const {
    auto [base, mod] = factors_mod[idx];
    auto [m_, cntm_] = calc_(m, base, mod, facts[idx]);
    auto [n_, cntn_] = calc_(n, base, mod, inv_facts[idx]);
    auto [mn_, cntmn_] = calc_(m - n, base, mod, inv_facts[idx]);
    return mul_mod(mul_mod(mul_mod(m_, n_, mod), mn_, mod),
                   qpow_mod(base, cntm_ - cntn_ - cntmn_, mod),
                   mod);
  }

public:
  explicit ExLucas(u64 mod_) {
    assert(mod_ > 1);
    for (u64 i = 2; i <= isqrt(mod_); ++i) {
      if (mod_ % i) continue;
      u64 facm = 1;
      while (mod_ % i == 0) {
        facm *= i;
        mod_ /= i;
      }
      push_back(i, facm);
    }
    if (mod_ > 1) push_back(mod_, mod_);
  }
  u64 operator()(i64 m, i64 n) const {
    if (m < n || n < 0) return 0;
    std::vector<u64> b(factors_mod.size()), md(factors_mod.size());
    for (size_t i = 0; i < factors_mod.size(); ++i) {
      b[i] = single_mCn(i, (u64)m, (u64)n);
      md[i] = std::get<1>(factors_mod[i]);
    }
    return crt(b, md);
  }
};
}  // namespace tifa_libs::math
#include <iostream>
int main() {
  tifa_libs::u64 n, m, p;
  std::cin >> n >> m >> p;
  tifa_libs::math::ExLucas mCn(p);
  std::cout << mCn(n, m) << '\n';
  return 0;
}
