#include <bits/stdc++.h>
template <class Tp>
using vc = std::vector<Tp>;
struct CustomHash {
  static constexpr uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static constexpr size_t append(size_t x, size_t y) {
    return x ^ (y >> 1) ^ ((y & 1) << (sizeof(size_t) * 8 - 1));
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
      std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
  template <class Tp, class Up>
  size_t operator()(std::pair<Tp, Up> const &p) const {
    return append((*this)(p.first), (*this)(p.second));
  }
  template <typename... Ts>
  size_t operator()(std::tuple<Ts...> const &tp) const {
    size_t ret = 0;
    std::apply(
      [&](Ts const &...targs) { ((ret = append(ret, (*this)(targs))), ...); },
      tp);
    return ret;
  }
  template <
    class Tp,
    std::enable_if_t<std::is_same<decltype(std::declval<Tp>().begin()),
                                  typename Tp::iterator>::value &&
                     std::is_same<decltype(std::declval<Tp>().end()),
                                  typename Tp::iterator>::value> * = nullptr>
  size_t operator()(Tp const &tp) const {
    size_t ret = 0;
    for (auto &&i : tp) ret = append(ret, (*this)(i));
    return ret;
  }
};
using u32 = uint32_t;
using i64 = int64_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define all_(a) (a).begin(), (a).end()
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
}
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
}
template <class Tp>
constexpr auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
#define TPL_SIZE_(Tuple) std::tuple_size_v<std::remove_reference_t<Tuple>>
namespace tuple_detail_ {
template <std::size_t Begin, class Tuple, std::size_t... Is>
constexpr auto subtuple_impl_(Tuple &&t, std::index_sequence<Is...>) {
  return std::make_tuple(std::get<Is + Begin>(t)...);
}
template <class Tuple, class BinOp, std::size_t... Is>
constexpr auto
apply2_impl_(BinOp &&f, Tuple &&lhs, Tuple &&rhs, std::index_sequence<Is...>) {
  return std::make_tuple(
    std::forward<BinOp>(f)(std::get<Is>(lhs), std::get<Is>(rhs))...);
}
}  // namespace tuple_detail_
template <std::size_t Begin, std::size_t Len, class Tuple>
constexpr auto subtuple(Tuple &&t) {
  static_assert(Begin <= TPL_SIZE_(Tuple) && Len <= TPL_SIZE_(Tuple) &&
                  Begin + Len <= TPL_SIZE_(Tuple),
                "Out of range");
  return tuple_detail_::subtuple_impl_<Begin>(t,
                                              std::make_index_sequence<Len>());
}
template <std::size_t Pos, class Tp, class Tuple>
constexpr auto tuple_push(Tp &&v, Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        std::make_tuple(v),
                        subtuple<Pos, TPL_SIZE_(Tuple) - Pos>(t));
}
template <class Tp, class Tuple>
constexpr auto tuple_push_front(Tp &&v, Tuple &&t) {
  return tuple_push<0>(v, t);
}
template <class Tp, class Tuple>
constexpr auto tuple_push_back(Tp &&v, Tuple &&t) {
  return tuple_push<TPL_SIZE_(Tuple)>(v, t);
}
template <std::size_t Pos, class Tuple>
constexpr auto tuple_pop(Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        subtuple<Pos + 1, TPL_SIZE_(Tuple) - Pos - 1>(t));
}
template <class Tuple>
constexpr auto tuple_pop_front(Tuple &&t) {
  return tuple_pop<0>(t);
}
template <class Tuple>
constexpr auto tuple_pop_back(Tuple &&t) {
  return tuple_pop<TPL_SIZE_(Tuple) - 1>(t);
}
template <class Tuple, class BinOp>
constexpr auto apply2(BinOp &&f, Tuple &&lhs, Tuple &&rhs) {
  return tuple_detail_::apply2_impl_(
    f, lhs, rhs, std::make_index_sequence<TPL_SIZE_(Tuple)>());
}
#define OO_PTEQ_(op)                                                          \
  template <class Tp, class Up>                                               \
  constexpr auto operator op(std::pair<Tp, Up> lhs,                           \
                             const std::pair<Tp, Up> &rhs) {                  \
    return std::pair<Tp, Up>{lhs.first op rhs.first,                          \
                             lhs.second op rhs.second};                       \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op(std::tuple<Ts...> const &lhs,                    \
                             std::tuple<Ts...> const &rhs) {                  \
    return apply2([](auto &&l, auto &&r) { return l op r; }, lhs, rhs);       \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator op##=(std::pair<Tp, Up> &lhs,         \
                                              const std::pair<Tp, Up> &rhs) { \
    lhs.first op## = rhs.first;                                               \
    lhs.second op## = rhs.second;                                             \
    return lhs;                                                               \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op##=(std::tuple<Ts...> &lhs,                       \
                                const std::tuple<Ts...> &rhs) {               \
    return lhs = lhs op rhs;                                                  \
  }
OO_PTEQ_(+)
OO_PTEQ_(-)
OO_PTEQ_(*)
OO_PTEQ_(/)
OO_PTEQ_(%)
OO_PTEQ_(&)
OO_PTEQ_(|)
OO_PTEQ_(^)
OO_PTEQ_(<<)
OO_PTEQ_(>>)
#undef OO_PTEQ_
#undef TPL_SIZE_
template <class Tp, class Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <typename... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p);
  return is;
}
template <typename... Ts>
std::ostream &operator<<(std::ostream &os, const std::tuple<Ts...> &p) {
  std::apply(
    [&](Ts const &...targs) {
      std::size_t n{0};
      ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
    },
    p);
  return os;
}
template <
  class Ch,
  class Tr,
  class Ct,
  std::enable_if_t<std::is_same<decltype(std::declval<Ct>().begin()),
                                typename Ct::iterator>::value &&
                   std::is_same<decltype(std::declval<Ct>().end()),
                                typename Ct::iterator>::value> * = nullptr>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Ct &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
const u32 OFFSET = 5;
const u32 N = 5e5 + OFFSET;
const i64 MOD = 998244353;
using namespace std;
constexpr int64_t qpow(int64_t a, int64_t b, int64_t mod) {
  int64_t res(1);
  a %= mod;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
constexpr int64_t inverse(int64_t n, int64_t mod) {
  int64_t b = mod, m0 = 0;
  for (int64_t q = 0, _ = 0, m1 = 1; n;) {
    _ = b - n * (q = b / n);
    b = n;
    n = _;
    _ = m0 - m1 * q;
    m0 = m1;
    m1 = _;
  }
  return (m0 + (m0 < 0 ? mod / b : 0)) % mod;
}
std::vector<int64_t> fact, inv_fact;
void init_fact(int64_t n = N, int64_t mod = MOD) {
  std::vector<int64_t> ffact(n);
  fact.resize(n * 2);
  inv_fact.resize(n);
  ffact[0] = fact[0] = inv_fact[0] = fact[1] = inv_fact[1] = 1;
  for (size_t i = 2; i < std::min(mod, n * 2); ++i)
    fact[i] = fact[i - 1] * i % mod;
  for (size_t i = 1; i < std::min(mod, n); ++i)
    ffact[i] = ffact[i - 1] * fact[i] % mod;
  int64_t _ = inverse(ffact[std::min(mod, n) - 1], mod);
  for (ptrdiff_t i = std::min(mod, n) - 1; i > 1; --i) {
    inv_fact[i] = _ * ffact[i - 1] % mod;
    _ = _ * fact[i] % mod;
  }
}
constexpr int64_t mCn(int m, int n, int64_t mod = MOD) {
  return m < n || n < 0 ? 0 :
                          fact[m] * inv_fact[n] % mod * inv_fact[m - n] % mod;
}
int64_t lagrange_interp_fixed_key(std::vector<int64_t> const &v,
                                  uint64_t x,
                                  int64_t mod) {
  const size_t n = v.size();
  if (x < n) return v[x];
  std::vector<int64_t> ifact(n);
  ifact[0] = ifact[1] = 1;
  for (size_t i = 2; i < n; ++i)
    ifact[i] = mod - mod / i * ifact[mod % i] % mod;
  for (size_t i = 3; i < n; ++i) (ifact[i] *= ifact[i - 1]) %= mod;
  std::vector<int64_t> pre(n);
  for (size_t i = 0; i < n; ++i) pre[i] = x - i;
  for (size_t i = 1; i < n; ++i) (pre[i] *= pre[i - 1]) %= mod;
  std::vector<int64_t> suc(n);
  for (size_t i = 0; i < n; ++i) suc[i] = x - i;
  for (ptrdiff_t i = n - 2; i >= 0; --i) (suc[i] *= suc[i + 1]) %= mod;
  int64_t ans = 0;
  for (size_t i = 0; i < n; ++i) {
    int64_t _ = v[i];
    if (i) _ = _ * pre[i - 1] % mod;
    if (i + 1 < n) _ = _ * suc[i + 1] % mod;
    _ = _ * ifact[i] % mod * ifact[n - i - 1] % mod;
    ans = (ans + ((n - i) % 2 ? _ : mod - _)) % mod;
  }
  return ans;
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 n, k;
  cin >> n >> k;
  i64 ans = 0;
  vc<i64> f(n + 3);
  for_(i, 1, n)
    for_(x, 0, i - 1)
      for_(y, x + 1, n - i)
        for_(t, 1, n + 2)
          (f[t] += t * mCn(i - 1, x) % MOD * qpow(t - 1, x, MOD) % MOD *
                   qpow(k - t + 1, i - x - 1, MOD) % MOD * mCn(n - i, y) % MOD *
                   qpow(k - t, y, MOD) % MOD * qpow(t, n - i - y, MOD) % MOD) %=
            MOD;
  partial_sum(all_(f), f.begin(), [](i64 x, i64 y) { return (x + y) % MOD; });
  cout << lagrange_interp_fixed_key(f, k, MOD);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  init_fact();
  solve(i_);
  return 0;
}
