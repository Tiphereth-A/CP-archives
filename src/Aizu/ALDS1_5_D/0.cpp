#include <bits/stdc++.h>
using u32 = uint32_t;
using u64 = uint64_t;
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
namespace tifa_libs {
template <class T = vec<int>>
T uniq(T const &v) {
  T _ = v;
  std::sort(_.begin(), _.end());
  _.erase(std::unique(_.begin(), _.end()), _.end());
  return _;
}
template <class T = vec<int>>
std::pair<T, vec<usz>> gen_id(T const &v) {
  T _ = uniq(v);
  vec<usz> _1;
  for (usz i = 0; i < v.size(); ++i)
    _1.push_back(usz(std::lower_bound(_.begin(), _.end(), v[i]) - _.begin()));
  return {_, _1};
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
u64 inversion(vec<T> const &v) {
  u64 ans = 0;
  auto id = gen_id(v).second;
  ds::fenwick<u64> tr(v.size() + 1);
  for (usz i = 0; i < v.size(); ++i) {
    tr.add(id[i] + 1, 1);
    ans += i + 1 - tr.sum(id[i] + 1);
  }
  return ans;
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
using remove_cvref_t =
  typename std::remove_cv_t<typename std::remove_reference_t<T>>;
template <class T>
using is_iterable = typename std::conditional_t<
  std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().begin()),
                 typename remove_cvref_t<T>::iterator> &&
    std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().end()),
                   typename remove_cvref_t<T>::iterator>,
  std::true_type,
  std::false_type>;
template <class T>
using is_container = typename std::conditional_t<
  is_iterable<T>::value &&
    !std::is_base_of_v<T, std::basic_string<typename T::value_type>>,
  std::true_type,
  std::false_type>;
}  // namespace tifa_libs
template <class T,
          std::enable_if_t<tifa_libs::is_container<T>::value> * = nullptr>
std::istream &operator>>(std::istream &is, T &x) {
  for (auto &i : x) is >> i;
  return is;
}
template <class T,
          std::enable_if_t<tifa_libs::is_container<T>::value> * = nullptr>
std::ostream &operator<<(std::ostream &os, const T &x) {
  if (x.begin() == x.end()) return os;
  auto it = x.begin();
  os << *it++;
  for (; it != x.end(); ++it) os << ' ' << *it;
  return os;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<u32> a(n);
  std::cin >> a;
  std::cout << tifa_libs::inversion(a) << '\n';
  return 0;
}
