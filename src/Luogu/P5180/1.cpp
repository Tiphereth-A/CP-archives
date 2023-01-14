#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define TPN typename
#define CR const &
#define cT_(...)                                            \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t), \
                     __VA_ARGS__,                           \
                     __VA_ARGS__ CR>
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
template <class T, usz N>
using arr = std::array<T, N>;
template <class U, class T>
using vvecp = vvec<std::pair<U, T>>;
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
template <class G>
requires(adjlist_c<G> && !adjlistw_c<G>)
class domtree {
  u32 n, t;
  G CR g;
  G rg;
  vvecu bucket;
  vecu arr, par, rev, dsu, label;
  CEXP void dfs(u32 u) {
    for (rev[arr[u] = label[t] = sdom[t] = dsu[t] = t] = u, ++t; u32 w : g[u]) {
      if (!~arr[w]) dfs(w), par[arr[w]] = arr[u];
      rg.add_arc(arr[w], arr[u]);
    }
  }
  CEXP u32 find(u32 u, int x = 0) {
    if (u == dsu[u]) return x ? -1_u32 : u;
    const u32 v = find(dsu[u], x + 1);
    if (!~v) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    return dsu[u] = v, x ? v : label[u];
  }

public:
  vecu sdom, dom;
  CEXPE domtree(G CR g)
    : n((u32)g.size()), t(0), g(g), rg(n), bucket(n), arr(n, -1_u32),
      par(n, -1_u32), rev(n, -1_u32), dsu(n), label(n), sdom(n, -1_u32),
      dom(n, -1_u32) {}
  CEXP vecu get_domtree(u32 root) {
    dfs(root), rg.build(), std::iota(dom.begin(), dom.end(), 0);
    for (u32 i = t - 1; ~i; --i) {
      for (auto w : rg[i]) sdom[i] = min(sdom[i], sdom[find((u32)w)]);
      if (i) bucket[sdom[i]].push_back(i);
      for (u32 w : bucket[i])
        if (u32 v = find(w); sdom[v] == sdom[w]) dom[w] = sdom[w];
        else dom[w] = v;
      if (i > 1) dsu[i] = par[i];
    }
    flt_(u32, i, 1, t) if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
    vecu fa(n, -1_u32);
    flt_(u32, i, 1, t) fa[rev[i]] = rev[dom[i]];
    return fa[root] = root, fa;
  }
};
}  // namespace tifa_libs::graph
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
namespace tifa_libs::graph {
namespace dfs_impl_ {
template <adjlist_c G, class Fb, class Fp, class Fs, class Fr>
CEXP void dfs_(G CR g,
               u32 u,
               u32 fa,
               Fb &&init,
               Fp &&pre_dfs,
               Fs &&post_dfs,
               Fr &&before_return) {
  if CEXP (init(u, fa); adjlistw_c<G>) {
    for (auto [v, w] : g[u])
      if (v != fa)
        pre_dfs(v, u, w),
          dfs_(g,
               v,
               u,
               std::forward<Fb>(init),
               std::forward<Fp>(pre_dfs),
               std::forward<Fs>(post_dfs),
               std::forward<Fr>(before_return)),
          post_dfs(v, u, w);
  } else
    for (auto v : g[u])
      if ((u32)v != fa)
        pre_dfs((u32)v, u),
          dfs_(g,
               (u32)v,
               u,
               std::forward<Fb>(init),
               std::forward<Fp>(pre_dfs),
               std::forward<Fs>(post_dfs),
               std::forward<Fr>(before_return)),
          post_dfs((u32)v, u);
  before_return(u, fa);
}
}  // namespace dfs_impl_
template <adjlist_c G, class Fb, class Fp, class Fs, class Fr>
CEXP void dfs(G CR g,
              u32 start,
              Fb &&init,
              Fp &&pre_dfs,
              Fs &&post_dfs,
              Fr &&before_return) {
  dfs_impl_::dfs_(g,
                  start,
                  -1_u32,
                  std::forward<Fb>(init),
                  std::forward<Fp>(pre_dfs),
                  std::forward<Fs>(post_dfs),
                  std::forward<Fr>(before_return));
}
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
struct td_dfn_tag {
  vecu dfn;

protected:
  u32 cnt;
  CEXPE td_dfn_tag(u32 n): dfn(n), cnt{0} {}
  void init(u32 u, u32) { dfn[u] = cnt++; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct td_sz_tag {
  vecu sz;

protected:
  CEXPE td_sz_tag(u32 n): sz(n) {}
  void init(u32 u, u32) { sz[u] = 1; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32 to, u32 u, auto) { sz[u] += sz[to]; }
  void before_return(u32, u32) {}
};
struct td_fa_tag {
  vecu fa;

protected:
  CEXPE td_fa_tag(u32 n): fa(n) {}
  void init(u32 u, u32 f) { fa[u] = f; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct td_dep_tag {
  vecu dep;

protected:
  CEXPE td_dep_tag(u32 n): dep(n) {}
  void init(u32, u32) {}
  void pre_dfs(u32 to, u32 u, auto) { dep[to] = dep[u] + 1; }
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct td_maxson_tag: td_sz_tag {
  vecu maxson;

protected:
  CEXPE td_maxson_tag(u32 n): td_sz_tag(n), maxson(n) {}
  void init(u32 u, u32 f) { td_sz_tag::init(u, f); }
  void pre_dfs(u32 to, u32 u, auto w) { td_sz_tag::pre_dfs(to, u, w); }
  void post_dfs(u32 to, u32 u, auto w) {
    if (td_sz_tag::post_dfs(to, u, w);
        maxson[u] == (u32)maxson.size() || sz[to] > sz[maxson[u]])
      maxson[u] = to;
  }
  void before_return(u32 u, u32 f) { td_sz_tag::before_return(u, f); }
};
struct td_maxdfn_tag {
  vecu maxdfn;

protected:
  u32 cnt;
  CEXPE td_maxdfn_tag(u32 n): maxdfn(n), cnt{0} {}
  void init(u32, u32) { ++cnt; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32 u, u32) { maxdfn[u] = cnt - 1; }
};
struct td_euler_tag {
  vecu euler;

protected:
  u32 cnt;
  CEXPE td_euler_tag(u32 n): euler(n), cnt{0} {}
  void init(u32 u, u32) { euler[cnt++] = u; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct td_go_tag {
  vvecu go;

protected:
  CEXP static u32 N = 21;
  CEXPE td_go_tag(u32 n): go(n, vecu(N, n)) { assert(n < 1u << N); }
  void init(u32 u, u32 f) {
    go[u][0] = f;
    for (u32 i = 1; i < N && go[u][i - 1] < go.size(); ++i)
      go[u][i] = go[go[u][i - 1]][i - 1];
  }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
template <tree_c G>
struct td_dis_tag {
  using w_t = std::conditional_t<std::is_void_v<TPN G::w_t>, u32, TPN G::w_t>;
  vec<w_t> dis;

protected:
  CEXPE td_dis_tag(u32 n): dis(n) {}
  void init(u32, u32) {}
  void pre_dfs(u32 to, u32 u, auto w) { dis[to] = dis[u] + w; }
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
template <tree_c G, class... Ts>
struct tree_dfs_info: Ts... {
  using w_t = std::conditional_t<std::is_void_v<TPN G::w_t>, u32, TPN G::w_t>;
  CEXPE tree_dfs_info(G CR tree): Ts(tree.size())... {
    dfs(
      tree,
      tree.root,
      [this](u32 u, u32 f) { (..., Ts::init(u, f)); },
      [this](u32 to, u32 u, cT_(w_t) w = 1) { (..., Ts::pre_dfs(to, u, w)); },
      [this](u32 to, u32 u, cT_(w_t) w = 1) { (..., Ts::post_dfs(to, u, w)); },
      [this](u32 u, u32 f) { (..., Ts::before_return(u, f)); });
  }
};
}  // namespace tifa_libs::graph
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
namespace tifa_libs::graph {
struct tree: alist<> {
  u32 root;
  CEXPE tree(u32 n, u32 root = 0): alist(n), root(root) {}
};
template <class T>
struct treew: alistw<T> {
  u32 root;
  CEXPE treew(u32 n, u32 root = 0): alistw<T>(n), root(root) {}
};
}  // namespace tifa_libs::graph
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist<> g(n);
  for (u32 i = 0, u, v; i < m; ++i) std::cin >> u >> v, g.add_arc(u - 1, v - 1);
  auto fa = tifa_libs::graph::domtree(g).get_domtree(0);
  tifa_libs::graph::tree tr(n);
  flt_(u32, i, 1, n) if (~fa[i]) tr.add_arc(fa[i], i);
  tifa_libs::graph::tree_dfs_info<tifa_libs::graph::tree,
                                  tifa_libs::graph::td_sz_tag>
    dfs(tr);
  std::cout << dfs.sz << '\n';
}
