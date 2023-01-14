#include <bits/stdc++.h>
template <class Tp>
using vc = std::vector<Tp>;
struct CustomHash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
      std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
using i64 = int64_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
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
using namespace std;
namespace Simulated_annealing {
using data_t = int64_t;
using fit_t = double;
using index_t = size_t;
using temperature_t = double;
template <class Tp>
using seq_t = std::vector<Tp>;
using data_seq_t = seq_t<data_t>;
std::default_random_engine g(time(nullptr));
std::uniform_int_distribution<data_t> data_gen;
std::uniform_int_distribution<index_t> idx_gen;
std::uniform_real_distribution<temperature_t> p_gen(0, 1);
const temperature_t delta_T = 1 - 1e-5;
const temperature_t initial_T = 2e13;
const temperature_t minimum_T = 1. / initial_T;
constexpr bool is_valid_seq(const data_seq_t &seq) { return true; }
data_seq_t new_seq_shuffle(const data_seq_t &seq) {
  data_seq_t ret(seq);
  do { std::shuffle(ret.begin(), ret.end(), g); } while (!is_valid_seq(ret));
  return ret;
}
data_seq_t new_seq_generate(const data_seq_t &&minimum,
                            const data_seq_t &&maximum) {
  data_seq_t ret;
  do {
    ret.clear();
    for (auto i = minimum.begin(), j = maximum.begin();
         i != minimum.end() && j != maximum.end();
         ++i, ++j)
      ret.push_back(data_gen(g) % (*j - *i) + *i);
  } while (!is_valid_seq(ret));
  return ret;
}
data_seq_t new_seq_generate_n(const data_t &&minimum,
                              const data_t &&maximum,
                              const index_t &&n) {
  data_seq_t ret;
  ret.resize(n);
  do {
    for (index_t i = 0; i < n; ++i)
      ret[i] = data_gen(g) % (maximum - minimum) + minimum;
  } while (!is_valid_seq(ret));
  return ret;
}
void swap_two_elements(data_seq_t &seq, const index_t &x, const index_t &y) {
  iter_swap(seq.begin() + x, seq.begin() + y);
}
std::pair<index_t, index_t> swap_two_elements_randomly(data_seq_t &seq) {
  index_t x, y;
  do {
    x = idx_gen(g) % seq.size();
    y = idx_gen(g) % seq.size();
  } while (x == y);
  swap_two_elements(seq, x, y);
  return {x, y};
}
bool accept(const fit_t &delta_fitness, const temperature_t &now_T) {
  return delta_fitness <= 0 || exp(-delta_fitness / now_T) > p_gen(g);
}
template <typename fitness_func = std::function<fit_t(data_seq_t const &)>>
fit_t main_seq(data_seq_t &ans_seq, fitness_func fitness) {
  fit_t ans = fitness(ans_seq), now_ans;
  index_t x, y;
  for (temperature_t T = initial_T; T > minimum_T; T *= delta_T) {
    std::tie(x, y) = swap_two_elements_randomly(ans_seq);
    now_ans = fitness(ans_seq);
    if (accept(now_ans - ans, T)) ans = now_ans;
    else swap_two_elements(ans_seq, x, y);
  }
  return ans;
}
template <typename fitness_func = std::function<fit_t(data_seq_t const &)>>
fit_t main_range(const data_seq_t &&minimum,
                 const data_seq_t &&maximum,
                 fitness_func fitness) {
  data_seq_t ans_seq(new_seq_generate(std::move(minimum), std::move(maximum))),
    now_seq;
  fit_t ans = fitness(ans_seq), now_ans;
  for (temperature_t T = initial_T; T > minimum_T; T *= delta_T) {
    now_seq = new_seq_generate(std::move(minimum), std::move(maximum));
    now_ans = fitness(now_seq);
    if (accept(now_ans - ans, T)) {
      ans = now_ans;
      ans_seq = now_seq;
    }
  }
  return ans;
}
template <typename fitness_func = std::function<fit_t(data_seq_t const &)>>
fit_t main_range_n(const data_t &&minimum,
                   const data_t &&maximum,
                   const index_t &&n,
                   fitness_func fitness) {
  data_seq_t ans_seq(
    new_seq_generate_n(std::move(minimum), std::move(maximum), std::move(n))),
    now_seq;
  fit_t ans = fitness(ans_seq), now_ans;
  for (temperature_t T = initial_T; T > minimum_T; T *= delta_T) {
    now_seq =
      new_seq_generate_n(std::move(minimum), std::move(maximum), std::move(n));
    now_ans = fitness(now_seq);
    if (accept(now_ans - ans, T)) {
      ans = now_ans;
      ans_seq = now_seq;
    }
  }
  return ans;
}
}  // namespace Simulated_annealing
using Simulated_annealing::main_range;
using Simulated_annealing::main_range_n;
using Simulated_annealing::main_seq;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m, c;
  cin >> n >> m >> c;
  vc<i64> maps;
  maps.reserve(n * m);
  for_(i, 1, c, p) {
    cin >> p;
    for_(_, 1, p) maps.push_back(i);
  }
  auto encode = [&](int x, int y) -> int { return x * m + y; };
  main_seq(maps, [&](vc<i64> const &seq) -> i64 {
    i64 ans = 0;
    for_(i, 0, n - 1)
      for_(j, 0, m - 1) {
        if (i + 1 < n) ans += seq[encode(i, j)] != seq[encode(i + 1, j)];
        if (j + 1 < m) ans += seq[encode(i, j)] != seq[encode(i, j + 1)];
      }
    return ans;
  });
  for_(i, 0, n - 1)
    for_(j, 0, m - 1) cout << maps[encode(i, j)] << " \n"[j == m - 1];
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
