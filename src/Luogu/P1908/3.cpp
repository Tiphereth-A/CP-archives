#include <bits/stdc++.h>
namespace tifa_libs {
using u32 = uint32_t;
using u64 = uint64_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
}  // namespace tifa_libs
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
  constexpr T kth_max(size_t k) {
    size_t now = 0, n = bit::bceil(a.size());
    T s{};
    while (n) {
      size_t to = now | n;
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
namespace tifa_libs::util {
template <class T = vec<int>>
T uniq(T const &v) {
  T _ = v;
  std::sort(_.begin(), _.end());
  _.erase(std::unique(_.begin(), _.end()), _.end());
  return _;
}
template <class T = vec<int>>
std::pair<T, vec<size_t>> gen_id(T const &v) {
  T _ = uniq(v);
  vec<size_t> _1;
  for (size_t i = 0; i < v.size(); ++i)
    _1.push_back(
      size_t(std::lower_bound(_.begin(), _.end(), v[i]) - _.begin()));
  return {_, _1};
}
}  // namespace tifa_libs::util
namespace tifa_libs::util {
template <class T>
u64 inversion(vec<T> const &v) {
  u64 ans = 0;
  auto id = gen_id(v).second;
  ds::fenwick<u64> tr(v.size() + 1);
  for (size_t i = 0; i < v.size(); ++i) {
    tr.add(id[i] + 1, 1);
    ans += i + 1 - tr.sum(id[i] + 1);
  }
  return ans;
}
}  // namespace tifa_libs::util
namespace tifa_libs::util {
template <class T>
void rsort32(vec<T> &a) {
  static_assert(sizeof(T) == 4);
  static u32 _0[256], _1[256], _2[256], _3[256];
  size_t n = a.size();
  vec<u32> b(n);
  u32 *a_ = a.data(), *b_ = b.data();
  for (u32 *_ = a_ + n, *i = a_; i < _; ++i) {
    ++_0[*i & 255];
    ++_1[*i >> 8 & 255];
    ++_2[*i >> 16 & 255];
    ++_3[*i >> 24 & 255];
  }
  for (u32 i = 1; i < 256; ++i) {
    _0[i] += _0[i - 1];
    _1[i] += _1[i - 1];
    _2[i] += _2[i - 1];
    _3[i] += _3[i - 1];
  }
  for (u32 *i = a_ + n; --i >= a_;) b_[--_0[*i & 255]] = *i;
  for (u32 *i = b_ + n; --i >= b_;) a_[--_1[*i >> 8 & 255]] = *i;
  for (u32 *i = a_ + n; --i >= a_;) b_[--_2[*i >> 16 & 255]] = *i;
  for (u32 *i = b_ + n; --i >= b_;) a_[--_3[*i >> 24 & 255]] = *i;
  if constexpr (std::is_signed_v<T>) {
    size_t i = n;
    while (i && a[i - 1] < 0) --i;
    std::rotate(a_, a_ + i, a_ + n);
  }
}
}  // namespace tifa_libs::util
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u32> a(n);
  for (auto &i : a) std::cin >> i;
  tifa_libs::u64 invs = tifa_libs::util::inversion(a);
  std::cout << invs << '\n';
  return 0;
}
