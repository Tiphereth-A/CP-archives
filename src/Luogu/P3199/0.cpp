#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define TPN typename
#define CR const &
#define cT_(...)                                                \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t) * 2, \
                     __VA_ARGS__,                               \
                     __VA_ARGS__ CR>
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using i128 = __int128_t;
using u128 = __uint128_t;
using f64 = double;
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
template <class U, class T>
using vvecp = vvec<std::pair<U, T>>;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                          \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)          \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T)       \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) \
        mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
inline const auto fn_0 = [](auto &&...) {};
using namespace std::literals;
namespace tifa_libs {
using std::swap;
template <class T>
CEXP T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <bool with_deg = false>
struct alist {
  using w_t = void;
  vvecu g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXPE alist(u32 n = 0): g(n), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v) {
    g[u].push_back(v);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void build() const {}
  CEXP u32 size() const { return (u32)g.size(); }
  CEXP auto &operator[](u32 u) { return g[u]; }
  CEXP auto CR operator[](u32 u) const { return g[u]; }
};
template <class T, bool with_deg = false>
struct alistw {
  using w_t = T;
  vvecp<u32, T> g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXPE alistw(u32 n = 0): g(n), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) {
    g[u].emplace_back(v, w);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void build() const {}
  CEXP u32 size() const { return (u32)g.size(); }
  CEXP auto &operator[](u32 u) { return g[u]; }
  CEXP auto CR operator[](u32 u) const { return g[u]; }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::math {
CEXP u32 isqrt(u64 x) {
  if (!x) return 0;
  const int sh = 31 - (std::bit_width(x) - 1) / 2;
  u32 u = [](u64 x) {
    CEXP u8 TAB[192] = {
      128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
      143, 144, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155,
      156, 156, 157, 158, 159, 160, 160, 161, 162, 163, 164, 164, 165, 166, 167,
      167, 168, 169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178,
      179, 179, 180, 181, 181, 182, 183, 183, 184, 185, 186, 186, 187, 188, 188,
      189, 190, 190, 191, 192, 192, 193, 194, 194, 195, 196, 196, 197, 198, 198,
      199, 200, 200, 201, 201, 202, 203, 203, 204, 205, 205, 206, 206, 207, 208,
      208, 209, 210, 210, 211, 211, 212, 213, 213, 214, 214, 215, 216, 216, 217,
      217, 218, 219, 219, 220, 220, 221, 221, 222, 223, 223, 224, 224, 225, 225,
      226, 227, 227, 228, 228, 229, 229, 230, 230, 231, 232, 232, 233, 233, 234,
      234, 235, 235, 236, 237, 237, 238, 238, 239, 239, 240, 240, 241, 241, 242,
      242, 243, 243, 244, 244, 245, 246, 246, 247, 247, 248, 248, 249, 249, 250,
      250, 251, 251, 252, 252, 253, 253, 254, 254, 255, 255, 255};
    u32 u = TAB[(x >> 56) - 64];
    return u = (u << 7) + (u32)(x >> 41) / u, (u << 15) + (u32)((x >> 17) / u);
  }(x << 2 * sh);
  return u >>= sh, u -= (u64)u * u > x, u;
}
}  // namespace tifa_libs::math
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
template <class, template <class...> class>
CEXP bool specialized_from_v = false;
template <template <class...> class T, class... Args>
CEXP bool specialized_from_v<T<Args...>, T> = true;
static_assert(specialized_from_v<vecu, std::vector>);
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
CEXP bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
template <class T>
concept arithm_c = is_arithm_v<T>;
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
template <class P>
concept tp_ds_c = requires(P p) {
  p->ch;
  std::is_array_v<decltype(p->ch)>;
  std::rank_v<decltype(p->ch)> == 1;
};
template <class P>
concept tp2_ds_c =
  tp_ds_c<P> && std::extent_v<decltype(std::declval<P>()->ch)> == 2;
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
template <adjlistw_c G, class F>
requires(!uint_c<TPN G::w_t>) &&
        requires(F relex, u32 now, u32 to) { relex(now, to); }
bool bellman_ford(G CR g, u32 s, F &&cb_relax, vec<TPN G::w_t> &dis) {
  const u32 n = g.size(), sn = math::isqrt(n);
  assert(dis.size() == n);
  vecb vis(n);
  vecu dep(n);
  std::deque<u32> q({s});
  auto upd_q = [&] {
    if (q.size() >= 2 && dis[q.front()] > dis[q.back()])
      swap(q.front(), q.back());
  };
  dis[s] = 0, vis[s] = true, dep[s] = 1;
  while (!q.empty()) {
    const u32 u = q.front();
    for (q.pop_front(), upd_q(), vis[u] = false; auto [v, w] : g[u])
      if (dis[u] + w < dis[v]) {
        if (cb_relax(u, v), dis[v] = dis[u] + w; vis[v]) continue;
        if (++dep[v] > n) return false;
        vis[v] = true,
        ((1 < dep[v] && dep[v] < sn) ||
             dis[v] < TPN G::w_t(q.size() ? dis[q.front()] : 0) ?
           q.push_front(v) :
           q.push_back(v)),
        upd_q();
      }
  }
  return true;
}
template <adjlistw_c G, class F>
std::optional<vec<TPN G::w_t>>
bellman_ford(G CR g,
             u32 s,
             F &&cb_relax,
             TPN G::w_t INF = std::numeric_limits<TPN G::w_t>::max() / 2 - 1) {
  vec dis(g.size(), INF);
  return bellman_ford(g, s, std::forward<F>(cb_relax), dis) ?
           std::optional{dis} :
           std::nullopt;
}
}  // namespace tifa_libs::graph
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alistw<f64> g(n + 1);
  flt_(u32, i, 0, m, u, v) {
    f64 w;
    std::cin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  f64 l = -1e7, r = 1e7, mid;
  auto chk = [&g](f64 x) {
    vec<f64> dis(g.size());
    flt_(u32, i, 1, g.size()) for (auto &[v, w] : g[i]) w -= x;
    flt_(u32, i, 1, g.size()) if (!tifa_libs::graph::bellman_ford(
                                    g, i, fn_0, dis)) {
      flt_(u32, i, 1, g.size()) for (auto &[v, w] : g[i]) w += x;
      return true;
    }
    flt_(u32, i, 1, g.size()) for (auto &[v, w] : g[i]) w += x;
    return false;
  };
  while (r - l > 1e-10) {
    mid = std::midpoint(l, r);
    (chk(mid) ? r : l) = mid;
  }
  std::cout << std::fixed << std::setprecision(8) << l;
  return 0;
}
