#include <bits/extc++.h>
#define CEXP constexpr
#define TPN typename
#define CR const &
#define cT_(...)                                            \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t), \
                     __VA_ARGS__,                           \
                     __VA_ARGS__ CR>
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
using f128 = long double;
using strn = std::string;
using strnv = std::string_view;
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) |
                ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) |
                ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);
template <class T>
struct chash {
  CEXP static u64 C = u64(pi_v<f128> * 2e18) | 71;
  CEXP u64 operator()(T x) const {
    return __builtin_bswap64(((u64)x ^ TIME) * C);
  }
};
template <class T>
using ptt = std::pair<T, T>;
template <class T>
struct edge_t {
  T w;
  u32 u, v;
  CEXP auto operator<=>(edge_t CR) const = default;
};
template <class T>
struct pt3 {
  T _0, _1, _2;
  CEXP auto operator<=>(pt3 CR) const = default;
};
template <class T>
struct pt4 {
  T _0, _1, _2, _3;
  CEXP auto operator<=>(pt4 CR) const = default;
};
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
using std::set, std::map;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                          \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)          \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T)       \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) \
        mk_(itl, A, T)
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
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
CEXP T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
concept iterable_c = requires(T v) {
  { v.begin() } -> std::same_as<TPN T::iterator>;
  { v.end() } -> std::same_as<TPN T::iterator>;
};
template <class T>
concept container_c =
  iterable_c<T> && !std::same_as<std::remove_cvref_t<T>, strn> &&
  !std::same_as<std::remove_cvref_t<T>, strnv>;
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
concept adjlist_c = requires(T g) {
  g[0].begin();
  g[0].end();
  g.build();
  g.size();
  g.cnt_arc;
  g.deg_in;
  g.deg_out;
};
template <class T> concept adjlistw_c = adjlist_c<T> && !std::is_void_v<TPN T::w_t> && (requires(T g) { g[0].begin()->first; g[0].begin()->second; } || requires(T g) { g[0].begin()->to; g[0].begin()->cost; });
template <class T>
concept tree_c = adjlist_c<T> && requires(T g) { g.root; };
template <class T>
concept treew_c = adjlistw_c<T> && requires(T g) { g.root; };
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
namespace tifa_libs::graph {
namespace euler_trail_impl_ {
template <bool cyc>
CEXP std::optional<vecptu> run_(u32 n, u32 m, cT_(vvecptu) g, u32 s) {
  vec<vecptu::const_iterator> its(n);
  flt_(u32, i, 0, n) its[i] = g[i].begin();
  veci f(n);
  if CEXP (!cyc) ++f[s];
  vecb vis(m);
  vecptu ret, stk = {{s, -1_u32}};
  while (!stk.empty()) {
    auto [i, p] = stk.back();
    auto &it = its[i];
    if (it == g[i].end()) {
      ret.emplace_back(i, p), stk.pop_back();
      continue;
    }
    if (auto [j, e] = *(it++); !vis[e])
      --f[i], ++f[j], stk.emplace_back(j, e), vis[e] = true;
  }
  if (ret.size() != m + 1) return {};
  for (i32 i : f)
    if (i < 0) return {};
  return std::ranges::reverse(ret), ret;
}
}  // namespace euler_trail_impl_
template <bool directed, bool cycle = false>
CEXP std::optional<vecptu> euler_trail(u32 n, vecptu CR edges) {
  vvecptu g(n);
  vecu deg_in(0);
  if CEXP (directed) deg_in.resize(n);
  u32 e = 0;
  for (auto [u, v] : edges) {
    g[u].emplace_back(v, e);
    if CEXP (directed) ++deg_in[v];
    else g[v].emplace_back(u, e);
    ++e;
  }
  u32 s = 0;
  flt_(u32, i, 1, (u32)g.size()) if (!g[i].empty()) s = i;
  flt_(u32, i, 0, (u32)g.size()) if CEXP (directed) {
    if (deg_in[i] < g[i].size()) s = i;
  }
  else if (g[i].size() & 1) s = i;
  return euler_trail_impl_::run_<cycle>(n, (u32)edges.size(), g, s);
}
template <adjlist_c G>
CEXP bool is_eulerian(G CR g) {
  const u32 n = g.size();
  assert(n == g.deg_in.size());
  vecb vis(n);
  u32 cnt = 0;
  auto f = [&](auto &&f, u32 x) -> void {
    for (auto v : g[x])
      if (++cnt; !vis[(u32)v]) vis[(u32)v] = 1, f(f, (u32)v);
  };
  if (vis[0] = 1, f(f, 0); g.cnt_arc != cnt) return 0;
  flt_(u32, i, 0, n) if (g.deg_in[i] != g.deg_out[i]) return 0;
  return 1;
}
}  // namespace tifa_libs::graph
using namespace std;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  u32 n;
  cin >> n;
  vecu fa(n * 2 + 1);
  vecptu edges;
  vecb deg1(n + 1), deg2(n + 1);
  fle_(u32, i, 1, n) {
    u32 x;
    cin >> x;
    deg1[i] = !deg1[i];
    if (~x) {
      fa[i] = x;
      deg1[x] = !deg1[x];
      edges.emplace_back(i, x);
    } else {
      fa[i] = 0;
      edges.emplace_back(0, i);
    }
  }
  fle_(u32, i, 1, n) {
    u32 x;
    cin >> x;
    deg2[i] = !deg2[i];
    if (~x) {
      fa[i + n] = x + n;
      deg2[x] = !deg2[x];
      edges.emplace_back(i + n, x + n);
    } else {
      fa[i + n] = 0;
      edges.emplace_back(0, i + n);
    }
  }
  fle_(u32, i, 1, n) if (deg1[i]) edges.emplace_back(i, i + n);
  if (deg1 != deg2) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  auto res = tifa_libs::graph::euler_trail<false>(n * 2 + 1, edges).value();
  veci ans(n + 1);
  flt_(u32, i, 0, (u32)res.size() - 1) {
    u32 now = res[i].first, nxt = res[i + 1].first;
    if (now && now + n == nxt) ans[now] = 1;
    else if (nxt && now == nxt + n) ans[nxt] = -1;
  }
  cout << "POSSIBLE\n";
  fle_(u32, i, 1, n) cout << ans[i] << " \n"[i == n];
  return 0;
}
