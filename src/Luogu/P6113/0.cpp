#include <bits/stdc++.h>
#define CEXP constexpr
#define TPN typename
#define CR const &
#define fle_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; ++i)
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
using ptt = std::pair<T, T>;
template <class T>
using pt3 = std::tuple<T, T, T>;
template <class T>
using pt4 = std::tuple<T, T, T, T>;
template <class E>
using itl = std::initializer_list<E>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using v3ec = vec<vvec<T>>;
template <class T>
using vecpt = vec<ptt<T>>;
template <class T>
using vvecpt = vvec<ptt<T>>;
template <class T>
using ptvec = ptt<vec<T>>;
template <class T>
using ptvvec = ptt<vvec<T>>;
template <class T, usz ext = std::dynamic_extent>
using spn = std::span<T const, ext>;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                              \
  mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T) mk_(vec, A, T) mk_(vvec, A, T) \
    mk_(v3ec, A, T) mk_(vecpt, A, T) mk_(vvecpt, A, T) mk_(ptvec, A, T)       \
      mk_(ptvvec, A, T) mk_(spn, A, T) mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
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
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
using std::numbers::pi_v;
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
class blossom {
  u32 n;
  vvecu g;
  vecu mate, first;
  vecb white;
  vecptu label;

public:
  CEXP explicit blossom(u32 n) { init(n); }
  CEXP void init(u32 n_) {
    n = n_, g = vvecu(n + 1), mate = first = vecu(n + 1), label = vecptu(n + 1),
    white = vecb(n + 1);
  }
  CEXP void add_edge(u32 u, u32 v) { g[u].push_back(v), g[v].push_back(u); }
  vecptu operator()() {
    fle_(u32, s, 1, n) if (!mate[s]) augment(s);
    fle_(u32, s, 1, n) if (!mate[s] && !white[s]) assert(!augment(s));
    vecptu ans;
    fle_(u32, s, 1, n) if (s < mate[s]) ans.emplace_back(s, mate[s]);
    return ans;
  }

private:
  CEXP u32 gf(u32 x) {
    return !white[first[x]] ? first[x] : first[x] = gf(first[x]);
  }
  CEXP void match(u32 p, u32 b) {
    if (swap(b, mate[p]); mate[b] != p) return;
    if (auto [k, v] = label[p]; !v) mate[b] = k, match(k, b);
    else match(k, v), match(v, k);
  }
  bool augment(u32 s) {
    assert(s);
    white[s] = 1, first[s] = 0, label[s] = {0, 0};
    std::queue<u32> q({s});
    while (!q.empty()) {
      const u32 a = q.front();
      for (q.pop(); auto b : g[a]) {
        assert(b);
        if (white[b]) {
          u32 x = gf(a), y = gf(b), lca = 0;
          while (x || y) {
            if (y) swap(x, y);
            if (label[x] == pttu{a, b}) {
              lca = x;
              break;
            }
            label[x] = {a, b}, x = gf(label[mate[x]].first);
          }
          for (u32 v : {gf(a), gf(b)})
            while (v != lca) {
              assert(!white[v]);
              q.push(v), white[v] = true, first[v] = lca,
                         v = gf(label[mate[v]].first);
            }
        } else if (!mate[b])
          return match(mate[b] = a, b), white = vecb(n + 1), true;
        else if (!white[mate[b]])
          white[mate[b]] = true, label[first[mate[b]] = b] = {0, 0},
          label[mate[b]] = {a, 0}, q.push(mate[b]);
      }
    }
    return false;
  }
};
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
  for (os << *it++; it != x.end(); ++it) os << ' ' << *it;
  return os;
}
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::blossom bl(n + 1);
  for (u32 i = 0, x, y; i < m; ++i) {
    std::cin >> x >> y;
    bl.add_edge(x, y);
  }
  auto me = bl();
  std::cout << me.size() << '\n';
  vecu ans(n);
  for (auto [u, v] : me) ans[u - 1] = v, ans[v - 1] = u;
  std::cout << ans << '\n';
  return 0;
}
