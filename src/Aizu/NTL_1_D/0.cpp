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
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
#undef assert
#define assert(x) 42
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
constexpr u32 euler_phi_u32(u32 n) {
  u32 ans = n;
  for (u32 i = 2; i <= isqrt(n); ++i)
    if (!(n % i)) {
      ans = ans / i * (i - 1);
      while (!(n % i)) n /= i;
    }
  if (n > 1) ans = ans / n * (n - 1);
  return ans;
}
}  // namespace tifa_libs::math
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
namespace tifa_libs::rand {
template <class Distri>
class Gen {
  std::conditional_t<sizeof(typename Distri::result_type) <= 4,
                     std::mt19937,
                     std::mt19937_64>
    re;
  Distri dist;

public:
  using random_engine = decltype(re);
  using result_type = typename Distri::result_type;
  Gen(): re(std::random_device{}()), dist() {}
  Gen(result_type a, result_type b): re(std::random_device{}()), dist(a, b) {}
  void set_range(result_type a, result_type b) { dist = Distri(a, b); }
  random_engine &rand_eng() { return re; }
  Distri &distrib() { return dist; }
  result_type operator()() { return dist(re); }
};
}  // namespace tifa_libs::rand
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
constexpr bool is_prime(u64 n) {
  if (n <= 2) return n == 2;
  if (~n & 1) return false;
  if (n < 8 || n == 61) return true;
  auto f = [n, d = (n - 1) >> bit::cntr0(n - 1)](auto const &bases) -> bool {
    for (u64 i : bases) {
      if (!(i % n)) continue;
      u64 t = d, y = qpow_mod(i, t, n);
      while (t != n - 1 && y != 1 && y != n - 1) {
        y = mul_mod_u(y, y, n);
        t *= 2;
      }
      if (y != n - 1 && (~t & 1)) return false;
    }
    return true;
  };
  if (n < (1 << 30)) {
    constexpr u64 bases[3] = {2, 7, 61};
    return f(bases);
  }
  constexpr u64 bases[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  return f(bases);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
namespace pfactors_impl_ {
class PollardRho {
  rand::Gen<std::uniform_int_distribution<u64>> e;
  u64 rho(u64 n) {
    e.set_range(2, n - 1);
    auto f = [n, r = e()](u64 x) { return (mul_mod_u(x, x, n) + r) % n; };
    u64 g = 1, x = 0, y = e(), yy = 0;
    const u32 LIM = 128;
    for (u64 r = 1, q = 1; g == 1; r *= 2) {
      x = y;
      for (u64 i = 0; i < r; ++i) y = f(y);
      for (u64 k = 0; g == 1 && k < r; k += LIM) {
        yy = y;
        for (u64 i = 0; i < LIM && i < r - k; ++i)
          q = mul_mod_u(q, (x + (n - (y = f(y)))) % n, n);
        g = std::gcd(q, n);
      }
    }
    if (g == n) do {
        g = std::gcd((x + (n - (yy = f(yy)))) % n, n);
      } while (g == 1);
    return g == n ? rho(n) : g;
  }

public:
  explicit PollardRho(): e() {}
  void operator()(u64 n, std::map<u64, u32> &ans) {
    if (n < 2) return;
    if (is_prime(n)) {
      ++ans[n];
      return;
    }
    auto g = rho(n);
    (*this)(n / g, ans);
    (*this)(g, ans);
  }
};
}  // namespace pfactors_impl_
std::map<u64, u32> pfactors(u64 n) {
  std::map<u64, u32> ans;
  if (n < 2) return ans;
  if (~n & 1) n >>= (ans[2] = (u32)bit::cntr0(n));
  using pfactors_impl_::PollardRho;
  PollardRho()(n, ans);
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
u64 euler_phi_u64(u64 n) {
  if (n <= (u32)(-1)) return euler_phi_u32((u32)n);
  auto pf = pfactors(n);
  for (auto [p, k] : pf) n = n / p * (p - 1);
  return n;
}
}  // namespace tifa_libs::math
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::euler_phi_u64(n) << '\n';
  return 0;
}
