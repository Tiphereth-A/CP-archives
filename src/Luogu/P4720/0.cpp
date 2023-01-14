#include <bits/stdc++.h>
using u32 = uint32_t;
using i64 = int64_t;
#define intlt2str_(s) STR_____(s)
#define STR_____(s) #s
#define REif_(expression)   \
  if (expression)           \
  throw std::runtime_error( \
    "Line " intlt2str_(__LINE__) ": やだもやだ、無理も無理〜")
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
template <class Tp, class Pred>
Tp binary_search(Pred check, Tp ok, Tp ng) {
  REif_(!check(ok));
  while (std::abs(ok - ng) > 1) {
    Tp x = (ng + ok) / 2;
    (check(x) ? ok : ng) = x;
  }
  return ok;
}
template <class Tp,
          class Pred,
          std::enable_if_t<std::is_floating_point_v<Tp>> * = nullptr>
Tp binary_search_real(Pred check, Tp ok, Tp ng, Tp eps) {
  REif_(!check(ok));
  while (std::abs(ok - ng) > eps) {
    Tp x = (ng + ok) / 2;
    (check(x) ? ok : ng) = x;
  }
  return (ng + ok) / 2;
}
template <class Tp>
auto discretization(Tp &var) -> Tp {
  Tp d__(var);
  std::sort(d__.begin(), d__.end());
  d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
  for (auto &i : var)
    i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
  return d__;
};
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
    return {lhs.first op rhs.first, lhs.second op rhs.second};                \
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
template <class Ch,
          class Tr,
          class Ct,
          std::enable_if_t<std::is_same_v<decltype(std::declval<Ct>().begin()),
                                          typename Ct::iterator> &&
                           std::is_same_v<decltype(std::declval<Ct>().end()),
                                          typename Ct::iterator>> * = nullptr>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Ct &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
const u32 OFFSET = 5;
const u32 M = 2e5 + OFFSET;
constexpr int64_t mul_mod(int64_t a, int64_t b, const int64_t &mod) {
  int64_t d = (int64_t)std::floor(1.0l * a * b / mod + 0.5l),
          ret = a * b - d * mod;
  return ret < 0 ? ret + mod : ret;
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
namespace CRT {
int64_t crt(std::vector<int64_t> const &b, std::vector<int64_t> const &m) {
  assert(b.size() == m.size());
  int64_t M = 1, ans = 0;
  for (auto &&i : m) M *= i;
  for (size_t i = 0; i < b.size(); ++i) {
    int64_t Mi = M / m[i], Ni = inverse(Mi, m[i]);
    (ans += mul_mod(mul_mod(b[i], Mi, M), Ni, M)) %= M;
  }
  return ans;
}
}  // namespace CRT
using CRT::crt;
constexpr int64_t qpow(int64_t a, int64_t b, int64_t mod) {
  int64_t res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
class ExLucas {
protected:
  int64_t mod;
  std::vector<std::pair<int64_t, int64_t>> factors_mod{};
  std::vector<std::vector<int64_t>> facts{}, inv_facts{};
  void push_back(int64_t base, int64_t factor_mod) {
    factors_mod.emplace_back(base, factor_mod);
    facts.emplace_back(factor_mod);
    inv_facts.emplace_back(factor_mod);
    auto &fact = facts.back();
    auto &inv_fact = inv_facts.back();
    fact[0] = fact[1] = inv_fact[0] = inv_fact[1] = 1;
    for (int64_t i = 2; i < factor_mod; ++i) {
      fact[i] = fact[i - 1];
      if (i % base) fact[i] = mul_mod(fact[i], i, factor_mod);
    }
    std::vector<int64_t> __(factor_mod);
    __[0] = __[1] = 1;
    for (int64_t i = 2; i < factor_mod; ++i)
      __[i] = mul_mod(__[i - 1], fact[i], factor_mod);
    int64_t inv_ = inverse(__.back(), factor_mod);
    for (int64_t i = factor_mod - 1; i > 1; --i) {
      inv_fact[i] = mul_mod(inv_, __[i - 1], factor_mod);
      inv_ = mul_mod(inv_, fact[i], factor_mod);
    }
  }
  std::pair<int64_t, int64_t> calc_(int64_t n,
                                    int64_t base,
                                    int64_t mod,
                                    std::vector<int64_t> const &v) const {
    if (n == 0) return {1, 0};
    int64_t _1 = mul_mod(qpow(v.back(), n / mod, mod), v[n % mod], mod),
            _2 = n / base;
    auto &&[res, cnt] = calc_(n / base, base, mod, v);
    return {mul_mod(res, _1, mod), _2 + cnt};
  }
  int64_t single_mCn(int64_t idx, int64_t m, int64_t n) const {
    auto &&[base, mod] = factors_mod[idx];
    auto [m_, cntm_] = calc_(m, base, mod, facts[idx]);
    auto [n_, cntn_] = calc_(n, base, mod, inv_facts[idx]);
    auto [mn_, cntmn_] = calc_(m - n, base, mod, inv_facts[idx]);
    return mul_mod(mul_mod(mul_mod(m_, n_, mod), mn_, mod),
                   qpow(base, cntm_ - cntn_ - cntmn_, mod),
                   mod);
  }

public:
  explicit ExLucas(int64_t mod_): mod(mod_) {
    assert(mod_ > 1);
    for (int64_t i = 2; i <= (int64_t)std::sqrt(mod_); ++i) {
      if (mod_ % i) continue;
      int64_t facm = 1;
      while (mod_ % i == 0) {
        facm *= i;
        mod_ /= i;
      }
      push_back(i, facm);
    }
    if (mod_ > 1) push_back(mod_, mod_);
  }
  int64_t m_choose_n(int64_t m, int64_t n) const {
    if (m < n) return 0;
    std::vector<int64_t> b(factors_mod.size()), md(factors_mod.size());
    for (size_t i = 0; i < factors_mod.size(); ++i) {
      b[i] = single_mCn(i, m, n);
      md[i] = std::get<1>(factors_mod[i]);
    }
    return crt(b, md);
  }
};
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  i64 n, m, p;
  cin >> n >> m >> p;
  cout << ExLucas(p).m_choose_n(n, m);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
