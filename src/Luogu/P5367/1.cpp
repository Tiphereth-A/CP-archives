namespace tifa_libs::bit {
template <typename T>
constexpr int cntr0(T x) {
  constexpr int nd = sizeof(T) * 8;
  static_assert(nd <= 128);
  if (x == 0) return nd;
  constexpr int nd_ull = sizeof(unsigned long long) * 8;
  constexpr int nd_ul = sizeof(unsigned long) * 8;
  constexpr int nd_u = sizeof(unsigned) * 8;
  if constexpr (nd <= nd_u) return __builtin_ctz(x);
  else if constexpr (nd <= nd_ul) return __builtin_ctzl(x);
  else if constexpr (nd <= nd_ull) return __builtin_ctzll(x);
  else {
    unsigned long long lo = x & (unsigned long long)(-1);
    if (lo != 0) return __builtin_ctzll(lo);
    unsigned long long hi = x >> nd_ull;
    return __builtin_ctzll(hi) + nd_ull;
  }
}
}  // namespace tifa_libs::bit
#include <bits/stdc++.h>
namespace tifa_libs {
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
template <class T>
using vec = std::vector<T>;
}  // namespace tifa_libs
namespace tifa_libs::ds {
template <class T>
class fenwick {
  vec<T> a;
  constexpr size_t lowbit(size_t x) { return (size_t)1 << bit::cntr0(x); }

public:
  explicit constexpr fenwick(size_t sz): a(sz) { assert(sz > 1); }
  constexpr void add(size_t pos, T const &x) {
    if (!pos) return;
    for (; pos < a.size(); pos += lowbit(pos)) a[pos] += x;
  }
  constexpr T sum(size_t pos) {
    T ret = 0;
    for (pos = std::min(pos, a.size() - 1); pos; pos -= lowbit(pos))
      ret += a[pos];
    return ret;
  }
};
}  // namespace tifa_libs::ds
namespace tifa_libs::bit {
template <typename T>
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
template <typename T>
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
vec<u64> fact_mod_gen(size_t sz, u64 mod) {
  assert(sz > 1 && mod >= sz);
  vec<u64> ans(sz, 1);
  for (size_t i = 2; i < sz; ++i) ans[i] = mul_mod_u(ans[i - 1], i, mod);
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
u64 cantor(vec<u32> const &a, u64 mod) {
  size_t n = a.size();
  ds::fenwick<u64> tr(n + 1);
  vec<u64> fact = fact_mod_gen(n + 1, mod);
  u64 ret = 1;
  vec<u64> p(n);
  for (size_t i = n - 1; ~i; --i) {
    p[i] = tr.sum(a[i]);
    tr.add(a[i], 1);
  }
  for (u64 i = 0; i < n; ++i)
    (ret += mul_mod_u(p[i], fact[n - i - 1], mod)) %= mod;
  return ret;
}
}  // namespace tifa_libs::math
void solve() {
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u32> a(n);
  for (auto &i : a) std::cin >> i;
  std::cout << tifa_libs::math::cantor(a, 998244353) << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}
