#include <bits/stdc++.h>
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
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
namespace tifa_libs::math {
vec<u32> cantor_seq(vec<u32> const &p) {
  usz n = p.size();
  ds::fenwick<u32> tr(n + 1);
  vec<u32> s(n);
  for (usz i = n - 1; ~i; --i) {
    s[i] = tr.sum(p[i]);
    tr.add(p[i], 1);
  }
  return s;
}
}  // namespace tifa_libs::math
namespace tifa_libs::ds {
class weighted_segtree {
  const usz n;
  vec<usz> t;
  void ins_(usz x, usz l, usz r, usz pos) {
    if (l == r) return void(++t[x]);
    usz mid = l + (r - l) / 2;
    if (pos <= mid) ins_(x << 1, l, mid, pos);
    else ins_(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  void del_(usz x, usz l, usz r, usz pos) {
    if (l == r) return void(--t[x]);
    usz mid = l + (r - l) / 2;
    if (pos <= mid) del_(x << 1, l, mid, pos);
    else del_(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  usz kth_min_(usz x, usz l, usz r, usz k) const {
    if (l == r) return l;
    usz mid = l + (r - l) / 2;
    if (k <= t[x << 1]) return kth_min_(x << 1, l, mid, k);
    return kth_min_(x << 1 | 1, mid + 1, r, k - t[x << 1]);
  }
  usz kth_max_(usz x, usz l, usz r, usz k) const {
    if (l == r) return l;
    usz mid = l + (r - l) / 2;
    if (k <= t[x << 1 | 1]) return kth_max_(x << 1 | 1, mid + 1, r, k);
    return kth_max_(x << 1, l, mid, k - t[x << 1 | 1]);
  }
  usz frequency_(usz x, usz l, usz r, usz L, usz R) const {
    if (L <= l && R >= r) return t[x];
    usz mid = l + (r - l) / 2, ret = usz(0);
    if (L <= mid) ret = frequency_(x << 1, l, mid, L, R);
    if (R > mid) ret += frequency_(x << 1 | 1, mid + 1, r, L, R);
    return ret;
  }

public:
  explicit weighted_segtree(usz N): n(N), t(N * 4) {}
  void ins(usz pos) { ins_(1, 0, n - 1, pos); }
  void del(usz pos) { del_(1, 0, n - 1, pos); }
  usz kth_min(usz k) { return kth_min_(1, 0, n - 1, k); }
  usz kth_max(usz k) { return kth_max_(1, 0, n - 1, k); }
  usz frequency(usz k) { return frequency_(1, 0, n - 1, k, k); }
  usz frequency(usz l, usz r) { return frequency_(1, 0, n - 1, l, r); }
};
}  // namespace tifa_libs::ds
namespace tifa_libs::math {
vec<u32> cantor_inv_seq(vec<u32> const &s) {
  usz n = s.size();
  ds::weighted_segtree tr(n + 1);
  for (usz i = 1; i <= n; ++i) tr.ins(i);
  vec<u32> p(n);
  for (usz i = 0; i < n; ++i) tr.del(p[i] = (u32)tr.kth_min(s[i] + 1));
  return p;
}
}  // namespace tifa_libs::math
namespace tifa_libs::bit {
template <class T>
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
vec<u64> fact_mod_gen(usz sz, u64 mod) {
  vec<u64> ans(sz, 1);
  for (usz i = 2; i < sz; ++i) ans[i] = mul_mod_u(ans[i - 1], i, mod);
  return ans;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
u64 cantor_seq2val(vec<u32> const &s, vec<u64> const &fact, u64 mod = (u64)-1) {
  usz n = s.size();
  u64 ret = 1;
  for (u64 i = 0; i < n; ++i)
    (ret += mul_mod_u(s[i], fact[n - i - 1], mod)) %= mod;
  return ret;
}
u64 cantor_seq2val(vec<u32> const &s, u64 mod = (u64)-1) {
  return cantor_seq2val(s, fact_mod_gen(s.size(), mod), mod);
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
vec<u32> cantor_val2seq(u64 cv, vec<u64> const &fact) {
  usz n = fact.size();
  --cv;
  vec<u32> s;
  s.reserve(n);
  for (u64 i = 0; i < n; cv %= fact[n - i - 1], ++i)
    s.push_back(u32(cv / fact[n - i - 1]));
  return s;
}
vec<u32> cantor_val2seq(u64 cv, usz n) {
  return cantor_val2seq(cv, fact_mod_gen(n, (u64)-1));
}
}  // namespace tifa_libs::math
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
  vec<u32> p(n);
  std::cin >> p;
  auto s = tifa_libs::math::cantor_seq(p);
  auto fact = tifa_libs::math::fact_mod_gen(s.size(), (u64)-1);
  u64 v = tifa_libs::math::cantor_seq2val(s, fact);
  if (v > 1)
    std::cout << tifa_libs::math::cantor_inv_seq(
                   tifa_libs::math::cantor_val2seq(v - 1, fact))
              << '\n';
  std::cout << p << '\n';
  if (v < fact.back() * n)
    std::cout << tifa_libs::math::cantor_inv_seq(
                   tifa_libs::math::cantor_val2seq(v + 1, fact))
              << '\n';
  return 0;
}
