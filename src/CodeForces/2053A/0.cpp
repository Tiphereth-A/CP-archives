#include <bits/extc++.h>
template <class T>
concept iterable = requires(T v) {
  { v.begin() } -> std::same_as<typename T::iterator>;
  { v.end() } -> std::same_as<typename T::iterator>;
};
template <class T>
concept container =
  iterable<T> &&
  !std::derived_from<T, std::basic_string<typename T::value_type>>;
#define int_type(w)                                                        \
  using i##w = int##w##_t;                                                 \
  using u##w = uint##w##_t;                                                \
  constexpr auto operator""_i##w(unsigned long long x) { return (i##w)x; } \
  constexpr auto operator""_u##w(unsigned long long x) { return (u##w)x; }
int_type(8);
int_type(16);
int_type(32);
int_type(64);
#undef int_type
#define fors_(i, l, r, s, ...) \
  for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
  return is >> p.first >> p.second;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, std::pair<T, U> const &p) {
  return os << p.first << ' ' << p.second;
}
template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  return std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p), is;
}
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &p) {
  return std::apply(
           [&, n = 0](Ts const &...targs) mutable {
             ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
           },
           p),
         os;
}
template <container T>
std::istream &operator<<(std::istream &is, T &x) {
  for (auto &i : x) is >> x;
  return is;
}
template <container T>
std::ostream &operator<<(std::ostream &os, T const &x) {
  if (x.begin() == x.end()) return os;
  for (auto nxt = x.begin(), it = nxt++; nxt != x.end(); ++it, ++nxt)
    os << *it << ' ';
  os << *x.rbegin();
  return os;
}
#define dbg(...) 42
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vector<int> a(n);
  for_(i, 0, n - 1) cin >> a[i];
  for_(i, 1, n - 1, x, y) {
    if (x = a[i - 1], y = a[i]; x > y) swap(x, y);
    if (x * 2 > y) {
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";
}
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) dbg(i_), solve(i_);
  return 0;
}
