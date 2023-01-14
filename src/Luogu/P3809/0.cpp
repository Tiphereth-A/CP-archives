#include <bits/stdc++.h>
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
namespace SA {
std::vector<int> sa_naive(const std::vector<int> &s) {
  int n = int(s.size());
  std::vector<int> sa(n);
  std::iota(sa.begin(), sa.end(), 0);
  std::sort(sa.begin(), sa.end(), [&](int l, int r) {
    if (l == r) return false;
    while (l < n && r < n) {
      if (s[l] != s[r]) return s[l] < s[r];
      l++;
      r++;
    }
    return l == n;
  });
  return sa;
}
std::vector<int> sa_doubling(const std::vector<int> &s) {
  int n = int(s.size());
  std::vector<int> sa(n), rnk = s, tmp(n);
  std::iota(sa.begin(), sa.end(), 0);
  for (int k = 1; k < n; k *= 2) {
    auto cmp = [&](int x, int y) {
      if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
      int rx = x + k < n ? rnk[x + k] : -1;
      int ry = y + k < n ? rnk[y + k] : -1;
      return rx < ry;
    };
    std::sort(sa.begin(), sa.end(), cmp);
    tmp[sa[0]] = 0;
    for (int i = 1; i < n; i++)
      tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
    std::swap(tmp, rnk);
  }
  return sa;
}
template <int THRN = 10, int THRD = 40>
std::vector<int> sa_is(const std::vector<int> &s, int upper) {
  int n = int(s.size());
  if (n == 0) return std::vector<int>{};
  if (n == 1) return std::vector<int>{0};
  if (n == 2)
    return s[0] < s[1] ? std::vector<int>{0, 1} : std::vector<int>{1, 0};
  if (n < THRN) return sa_naive(s);
  if (n < THRD) return sa_doubling(s);
  std::vector<int> sa(n);
  std::vector<bool> ls(n);
  for (int i = n - 2; i >= 0; i--)
    ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
  std::vector<int> sum_l(upper + 1), sum_s(upper + 1);
  for (int i = 0; i < n; i++) (ls[i] ? sum_l[s[i] + 1] : sum_s[s[i]])++;
  for (int i = 0; i <= upper; i++) {
    sum_s[i] += sum_l[i];
    if (i < upper) sum_l[i + 1] += sum_s[i];
  }
  auto induce = [&](const std::vector<int> &lms) {
    std::fill(sa.begin(), sa.end(), -1);
    std::vector<int> buf(upper + 1);
    std::copy(sum_s.begin(), sum_s.end(), buf.begin());
    for (auto d : lms) {
      if (d == n) continue;
      sa[buf[s[d]]++] = d;
    }
    std::copy(sum_l.begin(), sum_l.end(), buf.begin());
    sa[buf[s[n - 1]]++] = n - 1;
    for (int i = 0, v; i < n; i++)
      if ((v = sa[i]) >= 1 && !ls[v - 1]) sa[buf[s[v - 1]]++] = v - 1;
    std::copy(sum_l.begin(), sum_l.end(), buf.begin());
    for (int i = n - 1, v; i >= 0; i--)
      if ((v = sa[i]) >= 1 && ls[v - 1]) sa[--buf[s[v - 1] + 1]] = v - 1;
  };
  std::vector<int> lms_map(n + 1, -1);
  int m = 0;
  for (int i = 1; i < n; i++)
    if (!ls[i - 1] && ls[i]) lms_map[i] = m++;
  std::vector<int> lms;
  lms.reserve(m);
  for (int i = 1; i < n; i++)
    if (!ls[i - 1] && ls[i]) lms.push_back(i);
  induce(lms);
  if (m) {
    std::vector<int> sorted_lms;
    sorted_lms.reserve(m);
    for (int v : sa)
      if (lms_map[v] != -1) sorted_lms.push_back(v);
    std::vector<int> rec_s(m);
    int rec_upper = 0;
    rec_s[lms_map[sorted_lms[0]]] = 0;
    for (int i = 1; i < m; i++) {
      int l = sorted_lms[i - 1], r = sorted_lms[i];
      int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
      int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
      bool same = true;
      if (end_l - l != end_r - r) {
        same = false;
      } else {
        while (l < end_l) {
          if (s[l] != s[r]) break;
          l++;
          r++;
        }
        if (l == n || s[l] != s[r]) same = false;
      }
      if (!same) rec_upper++;
      rec_s[lms_map[sorted_lms[i]]] = rec_upper;
    }
    auto rec_sa = sa_is<THRN, THRD>(rec_s, rec_upper);
    for (int i = 0; i < m; i++) sorted_lms[i] = lms[rec_sa[i]];
    induce(sorted_lms);
  }
  return sa;
}
std::vector<int> suffix_array(const std::string &s) {
  int n = int(s.size());
  std::vector<int> s2(n);
  for (int i = 0; i < n; i++) s2[i] = s[i];
  return sa_is(s2, 255);
}
}  // namespace SA
using SA::suffix_array;
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  string s;
  cin >> s;
  auto &&_ = suffix_array(s);
  for (auto &&i : _) cout << i + 1 << ' ';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
