#include <bits/extc++.h>
namespace tifa_libs {
#define CEXP constexpr
#define CEXPE constexpr explicit
#define CR const &
#define TPN typename
#define NE noexcept
#define CNE const noexcept
#define cT_(...)                                                \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t) * 2, \
                     __VA_ARGS__,                               \
                     __VA_ARGS__ CR>
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
using namespace std::ranges;
using namespace std::literals;
template <class T>
CEXP T abs(T x) NE {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs {
#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) NE { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using i128 = __int128_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f128 = long double;
}  // namespace tifa_libs
namespace tifa_libs {
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) NE {
  eps_v<FP> = v;
}
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) |
                ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) |
                ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);
inline const auto fn_0 = [](auto &&...) NE {};
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
struct chash {
  CEXP static u64 C = u64(pi_v<f128> * 2e18) | 71;
  CEXP u64 operator()(T x) CNE {
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
using vecp = vec<std::pair<U, T>>;
template <class U, class T>
using vvecp = vvec<std::pair<U, T>>;
using std::set, std::map;
template <class T, class C = std::less<T>>
using pq = std::priority_queue<T, vec<T>, C>;
template <class T>
using pqg = pq<T, std::greater<T>>;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                          \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)          \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T)       \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) \
        mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
}  // namespace tifa_libs
namespace tifa_libs::ds {
template <std::unsigned_integral K, class V, class C = std::less<K>>
class radix_heap {
  static CEXP u32 B = sizeof(K) * 8;
  static CEXP C comp{};
  arr<vecp<K, V>, B + 1> vs;
  arr<K, B + 1> ms;
  u32 s;
  K last;

public:
  CEXPE radix_heap() NE: s(0), last(0) { fill(ms, K(-1)); }
  CEXP u32 size() CNE { return s; }
  CEXP bool empty() CNE { return !s; }
  CEXP void emplace(K key, cT_(V) val) NE {
    const K b = (K)std::bit_width(key ^ last);
    ++s, vs[b].emplace_back(key, val), ms[b] = min(key, ms[b], comp);
  }
  CEXP std::pair<K, V> top() NE {
    if (!~ms[0]) {
      const u32 idx =
        u32(find_if(ms, [](auto x) NE { return !!~x; }) - ms.begin());
      for (last = ms[idx]; auto &p : vs[idx]) {
        const K b = (K)std::bit_width(p.first ^ last);
        vs[b].emplace_back(p), ms[b] = min(p.first, ms[b], comp);
      }
      vs[idx].clear(), ms[idx] = K(-1);
    }
    return vs[0].back();
  }
  CEXP void pop() NE {
    if (top(), --s, vs[0].pop_back(); vs[0].empty()) ms[0] = K(-1);
  }
};
template <class K, class V>
using rheap = std::conditional_t<std::unsigned_integral<K>,
                                 ds::radix_heap<K, V>,
                                 pqg<std::pair<K, V>>>;
}  // namespace tifa_libs::ds
namespace tifa_libs {
template <class C>
requires(std::is_array_v<C> && std::integral<decltype(std::declval<C>()[0])> &&
         sizeof(std::declval<C>()[0]) == 4) ||
        (std::contiguous_iterator<TPN C::iterator> &&
         std::integral<TPN C::value_type> && sizeof(TPN C::value_type) == 4)
void rsort32(C &a) NE {
  if (a.size() <= 1) return;
  u32 _0[256]{}, _1[256]{}, _2[256]{}, _3[256]{};
  const u32 n = (u32)a.size();
  vecu b(n);
  u32 *a_ = (u32 *)a.data(), *b_ = (u32 *)b.data();
  for (u32 *_ = a_ + n, *i = a_; i < _; ++i)
    ++_0[*i & 255], ++_1[*i >> 8 & 255], ++_2[*i >> 16 & 255],
      ++_3[*i >> 24 & 255];
  flt_(u32, i, 1, 256) _0[i] += _0[i - 1], _1[i] += _1[i - 1],
    _2[i] += _2[i - 1], _3[i] += _3[i - 1];
  for (u32 *i = a_ + n; --i >= a_;) b_[--_0[*i & 255]] = *i;
  for (u32 *i = b_ + n; --i >= b_;) a_[--_1[*i >> 8 & 255]] = *i;
  for (u32 *i = a_ + n; --i >= a_;) b_[--_2[*i >> 16 & 255]] = *i;
  for (u32 *i = b_ + n; --i >= b_;) a_[--_3[*i >> 24 & 255]] = *i;
  if CEXP (std::is_signed_v<TPN C::value_type>) {
    u32 i = n;
    while (i && a[i - 1] < 0) --i;
    rotate(a_, a_ + n, a_ + i);
  }
}
template <class C>
requires(std::is_array_v<C> && std::integral<decltype(std::declval<C>()[0])> &&
         sizeof(std::declval<C>()[0]) == 4) ||
        range<C>
void sort(C &a) NE {
  if CEXP (std::is_array_v<C> ||
           (std::contiguous_iterator<TPN C::iterator> &&
            std::integral<TPN C::value_type> && sizeof(TPN C::value_type) == 4))
    rsort32(a);
  else std::ranges::sort(a);
}
}  // namespace tifa_libs
namespace tifa_libs {
template <common_range T>
CEXP T uniq(T v) NE {
  tifa_libs::sort(v);
  auto r = unique(v.begin(), v.end());
  return {v.begin(), r.begin()};
}
template <common_range T>
CEXP std::pair<T, vecu> gen_id(T CR v) NE {
  const T _ = uniq(v);
  vecu _1;
  _1.reserve(v.size());
  flt_(u32, i, 0, (u32)v.size())
    _1.push_back(u32(lower_bound(_, v[i]) - _.begin()));
  return {_, _1};
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T> concept sparse_graph_c = requires(T g) { g.cnt_arc; g.deg_in; g.deg_out; g.size(); g.foreach(0, fn_0); } && (requires(T g) { g.add_arc(0, 0); g.add_edge(0, 0); } || requires(T g) { g.add_arc(0, 0, {}); g.add_edge(0, 0, {}); });
template <class T>
concept alist_c = sparse_graph_c<T> && requires(T g) {
  { g[0] } -> common_range;
  g.build();
};
template <class T>
concept eog_c = sparse_graph_c<T> && requires(T g) {
  g.head;
  g.e;
  g.pop_startwith(0);
};
template <class T>
concept tree_c = alist_c<T> && requires(T g) { g.root; };
template <class T>
concept sparse_graphw_c = sparse_graph_c<T> && !std::is_void_v<TPN T::w_t> &&
                          requires(T g, TPN T::w_t w) {
                            g.add_arc(0, 0, w);
                            g.add_edge(0, 0, w);
                          };
template <class T> concept alistw_c = alist_c<T> && sparse_graphw_c<T> && (requires(T g) { g[0].begin()->first; g[0].begin()->second; } || requires(T g) { g[0].begin()->to; g[0].begin()->cost; });
template <class T>
concept eogw_c = eog_c<T> && sparse_graphw_c<T> && requires(T g) {
  g[0].to;
  g[0].w;
  g[0].nxt;
};
template <class T>
concept treew_c = tree_c<T> && alistw_c<T>;
}  // namespace tifa_libs
namespace tifa_libs {
template <class T>
concept char_c = std::same_as<T, char> || std::same_as<T, signed char> ||
                 std::same_as<T, unsigned char>;
template <class T>
concept s128_c = std::same_as<T, __int128_t> || std::same_as<T, __int128>;
template <class T>
concept u128_c =
  std::same_as<T, __uint128_t> || std::same_as<T, unsigned __int128>;
template <class T>
concept i128_c = s128_c<T> || u128_c<T>;
template <class T>
concept imost64_c = std::integral<T> && sizeof(T) * __CHAR_BIT__ <= 64;
template <class T>
concept smost64_c = imost64_c<T> && std::signed_integral<T>;
template <class T>
concept umost64_c = imost64_c<T> && std::unsigned_integral<T>;
template <class T>
concept int_c = i128_c<T> || imost64_c<T>;
template <class T>
concept sint_c = s128_c<T> || smost64_c<T>;
template <class T>
concept uint_c = u128_c<T> || umost64_c<T>;
template <class T>
concept arithm_c = std::is_arithmetic_v<T> || int_c<T>;
template <class T>
concept mint_c = requires(T x) {
  { x.mod() } -> uint_c;
  { x.val() } -> uint_c;
};
template <class T>
concept dft_c = requires(T x, std::vector<TPN T::data_t> v, u32 n) {
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
struct to_sint: std::make_signed<T> {};
template <>
struct to_sint<u128> {
  using type = i128;
};
template <>
struct to_sint<i128> {
  using type = i128;
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
template <class T>
using to_uint_t = TPN to_uint<T>::type;
template <arithm_c T>
struct to_bigger: std::make_unsigned<T> {};
#define _(w, ww)        \
  template <>           \
  struct to_bigger<w> { \
    using type = ww;    \
  }
#define _2(w, ww) \
  _(i##w, i##ww); \
  _(u##w, u##ww);
_2(8, 16);
_2(16, 32);
_2(32, 64);
_2(64, 128);
_(f32, f64);
_(f64, f128);
#undef _2
#undef _
template <arithm_c T>
CEXP T inf_v = [] {
  if CEXP (sint_c<T>) return T(to_uint_t<T>(-1) / 4 - 1);
  else if CEXP (uint_c<T>) return T(-1) / 2 - 1;
  else return std::numeric_limits<T>::max() / 2 - 1;
}();
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <bool get_edges, alistw_c G, class T = TPN G::w_t>
auto steiner_tree(G CR g, spnu x, vec<T> CR vw = {}, T INF = inf_v<T>) NE {
  const u32 n = (u32)g.size(), k = (u32)x.size();
  const bool has_vweight = !vw.empty();
  if (has_vweight) assert(!uint_c<T>);
  vvec<T> dp(n, vecu(1 << k, INF));
  vvec<std::pair<u32, T>> pre;
  if CEXP (get_edges) pre.resize(n, vec<std::pair<u32, T>>(1 << k));
  flt_(u32, i, 0, k) dp[x[i]][1 << i] = 0;
  ds::rheap<T, u32> q;
  auto dij = [&](u32 s) {
    while (!q.empty()) {
      auto [dis, u] = q.top();
      if (q.pop(); dp[u][s] != dis) continue;
      for (auto [v, w] : g[u])
        if (dp[v][s] > dis + w)
          if CEXP (q.emplace(dp[v][s] = dis + w, v); get_edges)
            pre[v][s] = {u, s};
    }
  };
  std::queue<u32> qw;
  auto bm = [&](u32 s) {
    vecb inq(n);
    while (!qw.empty()) {
      u32 u = qw.front();
      qw.pop(), inq[u] = false;
      for (auto [v, w] : g[u])
        if (dp[v][s] > dp[u][s] + w + vw[v]) {
          if (dp[v][s] = dp[u][s] + w + vw[v]; !inq[v])
            inq[v] = true, qw.push(v);
          if CEXP (get_edges) pre[v][s] = {u, s};
        }
    }
  };
  if (has_vweight) flt_(u32, s, 1, 1_u32 << k) {
      flt_(u32, i, 0, n) {
        for (u32 t = s & (s - 1); t; t = s & (t - 1))
          if (dp[i][s] > dp[i][t] + dp[i][s ^ t] - vw[i])
            if CEXP (dp[i][s] = dp[i][t] + dp[i][s ^ t] - vw[i]; get_edges)
              pre[i][s] = {i, t};
        if (dp[i][s] < INF) qw.push(i);
      }
      bm(s);
    }
  else flt_(u32, s, 1, 1_u32 << k) {
      flt_(u32, i, 0, n) {
        for (u32 t = s & (s - 1); t; t = s & (t - 1))
          if (dp[i][s] > dp[i][t] + dp[i][s ^ t])
            if CEXP (dp[i][s] = dp[i][t] + dp[i][s ^ t]; get_edges)
              pre[i][s] = {i, t};
        if (dp[i][s] < INF) q.emplace(dp[i][s], i);
      }
      dij(s);
    }
  if CEXP (get_edges) {
    vecptu edges;
    auto dfs = [&](auto &&dfs, u32 u, u32 fa, u32 s) {
      if (!pre[u][s].second) return;
      if (u != fa) edges.push_back(std::minmax(u, fa));
      if (pre[u][s].first == u) dfs(dfs, u, fa, s ^ pre[u][s].second);
      dfs(dfs, pre[u][s].first, u, pre[u][s].second);
    };
    for (auto i : x) dfs(dfs, i, i, (1 << k) - 1);
    return std::make_pair(dp[x[0]].back(), uniq(edges));
  } else return dp[x[0]].back();
}
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <bool with_deg = false>
struct alist {
  using w_t = void;
  vvecu g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXPE alist(u32 n = 0) NE: g(n), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v) NE {
    g[u].push_back(v);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void add_edge(u32 u, u32 v) NE { add_arc(u, v), add_arc(v, u); }
  CEXP void build() CNE {}
  CEXP u32 size() CNE { return (u32)g.size(); }
  CEXP auto &operator[](u32 u) NE { return g[u]; }
  CEXP auto CR operator[](u32 u) CNE { return g[u]; }
  template <class F>
  requires requires(F f, u32 v) { f(v); }
  CEXP void foreach(u32 u, F && f) CNE {
    for (auto v : g[u]) f(v);
  }
};
template <class T, bool with_deg = false>
struct alistw {
  using w_t = T;
  vvecp<u32, T> g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXPE alistw(u32 n = 0) NE: g(n), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) NE {
    g[u].emplace_back(v, w);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void add_edge(u32 u, u32 v, cT_(T) w) NE {
    add_arc(u, v, w), add_arc(v, u, w);
  }
  CEXP void build() CNE {}
  CEXP u32 size() CNE { return (u32)g.size(); }
  CEXP auto &operator[](u32 u) NE { return g[u]; }
  CEXP auto CR operator[](u32 u) CNE { return g[u]; }
  template <class F>
  requires requires(F f, u32 v, T w) { f(v, w); }
  CEXP void foreach(u32 u, F && f) CNE {
    for (auto [v, w] : g[u]) f(v, w);
  }
};
}  // namespace tifa_libs::graph
using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, k;
  std::cin >> n >> m >> k;
  graph::alistw<u32> e(n);
  for (u32 i = 0, u, v, w; i < m; ++i)
    std::cin >> u >> v >> w, --u, --v, e.add_arc(u, v, w), e.add_arc(v, u, w);
  vecu a(k);
  for (auto &x : a) std::cin >> x, --x;
  std::cout << graph::steiner_tree<false>(e, a);
}
