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
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;
constexpr i8 operator""_i8(unsigned long long x) { return (i8)x; }
constexpr i16 operator""_i16(unsigned long long x) { return (i16)x; }
constexpr i32 operator""_i32(unsigned long long x) { return (i32)x; }
constexpr i64 operator""_i64(unsigned long long x) { return (i64)x; }
constexpr isz operator""_iz(unsigned long long x) { return (isz)x; }
constexpr u8 operator""_u8(unsigned long long x) { return (u8)x; }
constexpr u16 operator""_u16(unsigned long long x) { return (u16)x; }
constexpr u32 operator""_u32(unsigned long long x) { return (u32)x; }
constexpr u64 operator""_u64(unsigned long long x) { return (u64)x; }
constexpr usz operator""_uz(unsigned long long x) { return (usz)x; }
#define fors_(i, l, r, s, ...) \
  for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
#define run_(cmd, post_cmd) \
  {                         \
    cmd;                    \
    post_cmd;               \
  }
#define runreturn_(cmd, ...) run_(cmd, return __VA_OPT__((__VA_ARGS__)))
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
  std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p);
  return is;
}
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &p) {
  std::apply(
    [&](Ts const &...targs) {
      usz n = 0;
      ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
    },
    p);
  return os;
}
template <container T>
std::istream &operator<<(std::istream &is, T &x) {
  for (auto &i : x) is >> x;
  return is;
}
template <container T>
std::ostream &operator<<(std::ostream &os, T const &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
template <class T>
constexpr auto chkmin(T &a, T b) -> bool {
  return b < a ? a = b, true : false;
}
template <class T>
constexpr auto chkmax(T &a, T b) -> bool {
  return a < b ? a = b, true : false;
}
template <std::floating_point T>
constexpr int sgn(T x, double EPS = 1e-8) {
  return (x > EPS) - (x < -EPS);
}
#define dbg(...) 42
#define 42
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n, m;
  cin >> n >> m;
  vector<int> s(m);
  for (auto &i : s) cin >> i;
  ranges::reverse(s);
  if (n == 1) runreturn_(cout << s[0] << '\n');
  vector<int> a(n + 1);
  for_(i, 1, n, idx, _) {
    if (a[i] >= m) runreturn_(cout << "-1\n");
    for (int j = i * 2; j <= n; j += i) a[j] = max<int>(a[j], a[i] + 1);
  }
  if (ranges::max(a) >= m) runreturn_(cout << "-1\n");
  for_(i, 1, n) cout << s[a[i]] << " \n"[i == n];
}
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) dbg(i_), solve(i_);
  return 0;
}
