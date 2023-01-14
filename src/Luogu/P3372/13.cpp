#include <bits/stdc++.h>
using i64 = int64_t;
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
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
constexpr T lowbit(T x) {
  return T(1) << cntr0(x);
}
}  // namespace tifa_libs::bit
namespace tifa_libs::ds {
template <class T>
class fenwick {
  vec<T> a;

public:
  explicit constexpr fenwick(usz sz): a(sz) { assert(sz > 1); }
  constexpr void add(usz pos, T const &x) {
    if (!pos) return;
    for (; pos < a.size(); pos += bit::lowbit(pos)) a[pos] += x;
  }
  constexpr T sum(usz pos) {
    T ret = 0;
    for (pos = std::min(pos, a.size() - 1); pos; pos -= bit::lowbit(pos))
      ret += a[pos];
    return ret;
  }
  constexpr T kth_max(usz k) {
    usz now = 0, n = bit::bceil(a.size());
    T s{};
    while (n) {
      usz to = now | n;
      if (to >= a.size()) continue;
      if (T x = s + a[to]; x < k) {
        now = to;
        s = x;
      }
    }
    return now + 1;
  }
};
}  // namespace tifa_libs::ds
namespace tifa_libs::ds {
template <class T>
class fenwick_rr {
  fenwick<T> a, ai;

public:
  explicit constexpr fenwick_rr(usz sz): a(sz), ai(sz) {}
  constexpr void add(usz pos, T const &x) {
    a.add(pos, x);
    ai.add(pos, (pos - 1) * x);
  }
  constexpr T sum(usz pos) { return pos * a.sum(pos) - ai.sum(pos); }
};
}  // namespace tifa_libs::ds
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::ds::fenwick_rr<i64> tr(n + 1);
  for (i64 i = 1, a, b = 0; i <= n; ++i) {
    std::cin >> a;
    tr.add(i, b = a - b);
    b = a;
  }
  for (i64 i = 0, op, l, r, k; i < m; ++i) {
    std::cin >> op >> l >> r;
    if (op == 1) {
      std::cin >> k;
      tr.add(l, k);
      tr.add(r + 1, -k);
    } else std::cout << tr.sum(r) - tr.sum(l - 1) << '\n';
  }
  return 0;
}
