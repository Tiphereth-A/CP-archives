#include <bits/stdc++.h>
#define CEXP constexpr
#define TPN typename
#define CR const &
#define fle_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; ++i)
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
using vecu = vec<u32>;
using vecb = vec<bool>;
using namespace std::literals;
CEXP i8 operator""_i8(unsigned long long x) { return (i8)x; }
CEXP i16 operator""_i16(unsigned long long x) { return (i16)x; }
CEXP i32 operator""_i32(unsigned long long x) { return (i32)x; }
CEXP i64 operator""_i64(unsigned long long x) { return (i64)x; }
CEXP isz operator""_iz(unsigned long long x) { return (isz)x; }
CEXP u8 operator""_u8(unsigned long long x) { return (u8)x; }
CEXP u16 operator""_u16(unsigned long long x) { return (u16)x; }
CEXP u32 operator""_u32(unsigned long long x) { return (u32)x; }
CEXP u64 operator""_u64(unsigned long long x) { return (u64)x; }
CEXP usz operator""_uz(unsigned long long x) { return (usz)x; }
template <std::floating_point FP>
CEXP inline FP eps_v = FP(1e-8L);
using std::numbers::pi_v;
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <class T>
CEXP vec<T> hungarian(vvec<T> CR g, T INF = std::numeric_limits<T>::max()) {
  u32 J = (u32)g.size(), W = (u32)g[0].size();
  assert(J <= W);
  vecu job(W + 1, -1_u32);
  vec<T> ys(J), yt(W + 1), ret;
  flt_(u32, j_now, 0, J) {
    u32 w_now = W;
    job[w_now] = j_now;
    vec<T> min_to(W + 1, INF);
    vecu prv(W + 1, -1_u32);
    vecb vis(W + 1);
    while (~job[w_now]) {
      vis[w_now] = true;
      u32 j = job[w_now], w_nxt = -1_u32;
      T _ = INF;
      flt_(u32, w, 0, W) {
        if (!vis[w]) {
          if (min_to[w] > g[j][w] - ys[j] - yt[w])
            min_to[w] = g[j][w] - ys[j] - yt[w], prv[w] = w_now;
          if (_ > min_to[w]) _ = min_to[w_nxt = w];
        }
      }
      fle_(u32, w, 0, W) {
        if (vis[w]) ys[job[w]] += _, yt[w] -= _;
        else min_to[w] -= _;
      }
      w_now = w_nxt;
    }
    for (u32 w; ~w_now && ~prv[w_now]; w_now = w)
      job[w_now] = job[w = prv[w_now]];
    ret.push_back(-yt[W]);
  }
  return ret;
}
}  // namespace tifa_libs::graph
namespace tifa_libs {
template <class T>
concept iterable_c = requires(T v) {
  { v.begin() } -> std::same_as<TPN T::iterator>;
  { v.end() } -> std::same_as<TPN T::iterator>;
};
template <class T>
concept container_c =
  iterable_c<T> &&
  !std::derived_from<T, std::basic_string<TPN T::value_type>> &&
  !std::derived_from<T, std::basic_string_view<TPN T::value_type>>;
template <class T>
CEXP bool is_char_v =
  std::is_same_v<T, char> || std::is_same_v<T, signed char> ||
  std::is_same_v<T, unsigned char>;
template <class T>
concept char_c = is_char_v<T>;
template <class T>
CEXP bool is_s128_v =
  std::is_same_v<T, __int128_t> || std::is_same_v<T, __int128>;
template <class T>
concept s128_c = is_s128_v<T>;
template <class T>
CEXP bool is_u128_v =
  std::is_same_v<T, __uint128_t> || std::is_same_v<T, unsigned __int128>;
template <class T>
concept u128_c = is_u128_v<T>;
template <class T>
CEXP bool is_i128_v = is_s128_v<T> || is_u128_v<T>;
template <class T>
concept i128_c = is_u128_v<T>;
template <class T>
CEXP bool is_int_v = std::is_integral_v<T> || is_i128_v<T>;
template <class T>
concept int_c = is_int_v<T>;
template <class T>
CEXP bool is_sint_v = is_s128_v<T> || (is_int_v<T> && std::is_signed_v<T>);
template <class T>
concept sint_c = is_sint_v<T>;
template <class T>
CEXP bool is_uint_v = is_u128_v<T> || (is_int_v<T> && std::is_unsigned_v<T>);
template <class T>
concept uint_c = is_uint_v<T>;
template <class T>
concept mint_c = requires(T x) {
  { x.mod() } -> uint_c;
  { x.val() } -> uint_c;
};
template <class T>
concept dft_c = requires(T x, vec<TPN T::data_t> v, u32 n) {
  { x.size() } -> std::same_as<u32>;
  x.bzr(n);
  x.dif(v, n);
  x.dit(v, n);
};
template <class T>
concept ntt_c = dft_c<T> && requires(T x) {
  T::max_size;
  T::G;
};
template <class T>
CEXP bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
template <class T>
concept arithm_c = is_arithm_v<T>;
template <class T>
struct to_sint: std::make_signed<T> {};
template <>
struct to_sint<u128> {
  using type = u128;
};
template <>
struct to_sint<i128> {
  using type = u128;
};
template <class T>
struct to_uint: std::make_unsigned<T> {};
template <>
struct to_uint<u128> {
  using type = u128;
};
template <>
struct to_uint<i128> {
  using type = u128;
};
}  // namespace tifa_libs
template <tifa_libs::container_c T>
std::istream &operator>>(std::istream &is, T &x) {
  for (auto &i : x) is >> i;
  return is;
}
template <tifa_libs::container_c T>
std::ostream &operator<<(std::ostream &os, T CR x) {
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
  vvec<i32> c1(n, vec<i32>(n));
  for (auto &i : c1) std::cin >> i;
  auto c2 = c1;
  for (auto &i : c2)
    for (auto &j : i) j = -j;
  std::cout << tifa_libs::graph::hungarian(c1).back() << '\n';
  std::cout << -tifa_libs::graph::hungarian(c2).back() << '\n';
  return 0;
}
