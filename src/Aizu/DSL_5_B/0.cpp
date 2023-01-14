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
#include <bits/stdc++.h>
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
#undef assert
#define assert(x) 42
namespace tifa_libs::ds {
template <class T>
class fenwick2d {
  vvec<T> a;

public:
  explicit constexpr fenwick2d(usz row, usz col): a(row, vec<T>(col)) {
    assert(row > 1 && col > 1);
  }
  constexpr usz row() const { return a.size(); }
  constexpr usz col() const { return a[0].size(); }
  constexpr void add(usz x, usz y, T const &val) {
    if (!x || !y || x >= row() || y >= col()) return;
    for (; x < row(); x += bit::lowbit(x))
      for (usz j = y; j < col(); j += bit::lowbit(j)) a[x][j] += val;
  }
  constexpr void add(usz xl, usz yl, usz xr, usz yr, T const &val) {
    add(xl, yl, val);
    add(xl, yr, -val);
    add(xr, yl, -val);
    add(xr, yr, val);
  }
  constexpr T sum(usz x, usz y) {
    T ret = 0;
    for (x = std::min(x, row() - 1); x; x -= bit::lowbit(x))
      for (usz j = std::min(y, col() - 1); j; j -= bit::lowbit(j))
        ret += a[x][j];
    return ret;
  }
  constexpr T sum(usz xl, usz yl, usz xr, usz yr) {
    if (xl >= xr || yl >= yr) return 0;
    return sum(xr, yr) - sum(xl, yr) + sum(xl, yl) - sum(xr, yl);
  }
};
}  // namespace tifa_libs::ds
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::ds::fenwick2d<u32> tr(1003, 1003);
  usz n;
  std::cin >> n;
  for (u32 i = 0, xl, xr, yl, yr; i < n; ++i) {
    std::cin >> xl >> yl >> xr >> yr;
    tr.add(xl + 1, yl + 1, xr + 1, yr + 1, 1);
  }
  u32 mx = 0;
  for (u32 i = 1; i <= 1001; ++i)
    for (u32 j = 1; j <= 1001; ++j) mx = std::max(mx, tr.sum(i, j));
  std::cout << mx << '\n';
  return 0;
}
