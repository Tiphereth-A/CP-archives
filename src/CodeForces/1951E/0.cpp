#include <bits/stdc++.h>
#include <bits/stdtr1c++.h>
#include <ext/algorithm>
#include <ext/rb_tree>
#include <ext/rope>
#include <ext/vstring.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
template <class T>
concept iterable = requires(T v) {
  { v.begin() } -> std::same_as<typename T::iterator>;
  { v.end() } -> std::same_as<typename T::iterator>;
};
template <class T>
concept container =
  iterable<T> &&
  !std::derived_from<T, std::basic_string<typename T::value_type>>;
template <class T>
using vec = std::vector<T>;
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
#define for_(i, l, r, ...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l),                   \
                                           i##end = (r)__VA_OPT__(, ) \
                                             __VA_ARGS__;             \
       i <= i##end;                                                   \
       ++i)
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
using namespace std;
mt19937_64 mt(std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch())
                .count());
auto solve([[maybe_unused]] int t_ = 0) -> void {
  string s;
  cin >> s;
  auto is_palindrome = [&](u32 l, u32 r) -> bool {
    for (; l < r; ++l, --r)
      if (s[l] != s[r]) return 0;
    return 1;
  };
  vec<pair<u32, u32>> ints;
  auto f = [&](auto &&f, u32 l, u32 r) -> bool {
    u32 len = r - l + 1;
    if (len == 1) return 0;
    if (len == 2) {
      if (s[l] != s[r]) {
        ints.emplace_back(l, r);
        return 1;
      } else return 0;
    }
    if (!is_palindrome(l, r)) {
      ints.emplace_back(l, r);
      return 1;
    }
    u32 mid = uniform_int_distribution<u32>(l + 1, r - 1)(mt);
    return f(f, l, mid) && f(f, mid + 1, r);
  };
  auto n = s.size();
  for_(i, 0, 512) {
    ints.clear();
    if (!f(f, 0, n - 1)) continue;
    cout << "YES\n";
    cout << ints.size() << '\n';
    for_(i, 0, ints.size() - 1)
      cout << s.substr(ints[i].first, ints[i].second - ints[i].first + 1)
           << " \n"[i == ints.size() - 1];
    return;
  }
  cout << "NO\n";
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
