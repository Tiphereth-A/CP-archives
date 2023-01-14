#include <bits/stdc++.h>
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
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
template <class T, usz N>
using arr = std::array<T, N>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
using vecu = vec<u32>;
using vvecu = vvec<u32>;
#undef assert
#define assert(x) 42
using namespace std::literals;
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
namespace tifa_libs::graph {
template <bool with_deg = false>
struct alist {
  using weight_type = u32;
  using value_type = vvecu;
  value_type g;
  u32 cnt_arc;
  vecu deg_in;
  explicit constexpr alist(u32 n = 0): g(n), cnt_arc(0), deg_in(0) {
    if constexpr (with_deg) deg_in.resize(n);
  }
  constexpr void add_arc(u32 u, u32 v) {
    g[u].push_back(v), ++cnt_arc;
    if constexpr (with_deg) ++deg_in[v];
  }
};
template <class G>
concept is_alist =
  (std::is_base_of_v<alist<true>, G> || std::is_base_of_v<alist<false>, G>);
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
class domtree {
  u32 n, t;
  alist<> const &g;
  alist<> rg;
  vvecu bucket;
  vecu arr, par, rev, dsu, label;
  void dfs(u32 u) {
    rev[arr[u] = label[t] = sdom[t] = dsu[t] = t] = u;
    ++t;
    for (u32 w : g.g[u]) {
      if (arr[w] == -1_u32) {
        dfs(w);
        par[arr[w]] = arr[u];
      }
      rg.add_arc(arr[w], arr[u]);
    }
  }
  u32 find(u32 u, int x = 0) {
    if (u == dsu[u]) return x ? -1_u32 : u;
    u32 v = find(dsu[u], x + 1);
    if (!~v) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
  }

public:
  vecu sdom, dom;
  domtree(alist<> const &g)
    : n((u32)g.g.size()), t(0), g(g), rg(n), bucket(n), arr(n, -1_u32),
      par(n, -1_u32), rev(n, -1_u32), dsu(n), label(n), sdom(n, -1_u32),
      dom(n, -1_u32) {}
  vecu get_domtree(u32 root) {
    dfs(root);
    std::iota(dom.begin(), dom.end(), 0);
    for (u32 i = t - 1; ~i; --i) {
      for (u32 w : rg.g[i]) sdom[i] = std::min(sdom[i], sdom[find(w)]);
      if (i) bucket[sdom[i]].push_back(i);
      for (u32 w : bucket[i])
        if (u32 v = find(w); sdom[v] == sdom[w]) dom[w] = sdom[w];
        else dom[w] = v;
      if (i > 1) dsu[i] = par[i];
    }
    for (u32 i = 1; i < t; ++i)
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
    vecu fa(n, -1_u32);
    for (u32 i = 1; i < t; ++i) fa[rev[i]] = rev[dom[i]];
    fa[root] = root;
    return fa;
  }
};
}  // namespace tifa_libs::graph
namespace tifa_libs {
template <class T>
concept iterable_c = requires(T v) {
  { v.begin() } -> std::same_as<typename T::iterator>;
  { v.end() } -> std::same_as<typename T::iterator>;
};
template <class T>
concept container_c =
  iterable_c<T> &&
  !std::derived_from<T, std::basic_string<typename T::value_type>>;
template <class T>
constexpr bool is_char_v =
  std::is_same_v<T, char> || std::is_same_v<T, signed char> ||
  std::is_same_v<T, unsigned char>;
template <class T>
concept char_c = is_char_v<T>;
template <class T>
constexpr bool is_s128_v =
  std::is_same_v<T, __int128_t> || std::is_same_v<T, __int128>;
template <class T>
concept s128_c = is_s128_v<T>;
template <class T>
constexpr bool is_u128_v =
  std::is_same_v<T, __uint128_t> || std::is_same_v<T, unsigned __int128>;
template <class T>
concept u128_c = is_u128_v<T>;
template <class T>
constexpr bool is_i128_v = is_s128_v<T> || is_u128_v<T>;
template <class T>
concept i128_c = is_u128_v<T>;
template <class T>
constexpr bool is_int_v = std::is_integral_v<T> || is_i128_v<T>;
template <class T>
concept int_c = is_int_v<T>;
template <class T>
constexpr bool is_sint_v = is_s128_v<T> || (is_int_v<T> && std::is_signed_v<T>);
template <class T>
concept sint_c = is_sint_v<T>;
template <class T>
constexpr bool is_uint_v =
  is_u128_v<T> || (is_int_v<T> && std::is_unsigned_v<T>);
template <class T>
concept uint_c = is_uint_v<T>;
template <class T>
concept mint_c = requires(T x) {
  { x.mod() } -> uint_c;
  { x.val() } -> uint_c;
};
template <class T>
constexpr bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
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
std::ostream &operator<<(std::ostream &os, T const &x) {
  if (x.begin() == x.end()) return os;
  auto it = x.begin();
  os << *it++;
  for (; it != x.end(); ++it) os << ' ' << *it;
  return os;
}
namespace tifa_libs::graph {
namespace dfs_impl_ {
template <class G, class Fb, class Fp, class Fs, class Fr>
constexpr void dfs_(G const &fg,
                    u32 u,
                    u32 fa,
                    Fb &&init,
                    Fp &&pre_dfs,
                    Fs &&post_dfs,
                    Fr &&before_return) {
  init(u, fa);
  for (auto v : fg.g[u])
    if constexpr (is_alist<G>) {
      if (v != fa) {
        pre_dfs(v, u);
        dfs_(fg,
             v,
             u,
             std::forward<Fb>(init),
             std::forward<Fp>(pre_dfs),
             std::forward<Fs>(post_dfs),
             std::forward<Fr>(before_return));
        post_dfs(v, u);
      }
    } else {
      if (v.first != fa) {
        pre_dfs(v.first, u, v.second);
        dfs_(fg,
             v.first,
             u,
             std::forward<Fb>(init),
             std::forward<Fp>(pre_dfs),
             std::forward<Fs>(post_dfs),
             std::forward<Fr>(before_return));
        post_dfs(v.first, u, v.second);
      }
    }
  before_return(u, fa);
}
}  // namespace dfs_impl_
template <class G, class Fb, class Fp, class Fs, class Fr>
constexpr void dfs(G const &fg,
                   u32 start,
                   Fb &&init,
                   Fp &&pre_dfs,
                   Fs &&post_dfs,
                   Fr &&before_return) {
  dfs_impl_::dfs_(fg,
                  start,
                  -1_u32,
                  std::forward<Fb>(init),
                  std::forward<Fp>(pre_dfs),
                  std::forward<Fs>(post_dfs),
                  std::forward<Fr>(before_return));
}
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
enum tree_dfs_info_mask {
  td_dfn = 1,
  td_sz = 2,
  td_fa = 4,
  td_dep = 8,
  td_maxson = 16,
  td_maxdfn = 32,
  td_euler = 64,
  td_go = 128,
  td_dis = 256
};
template <class G>
struct tree_dfs_info {
  using weight_type = typename G::weight_type;
  vecu dfn, sz, fa, dep, maxson, maxdfn, euler;
  vvecu go;
  vec<weight_type> dis;
  template <int state>
  constexpr tree_dfs_info &reset_dfs_info(G const &tree) {
    u32 n = (u32)tree.g.size();
    if constexpr (state & td_dfn) dfn = vecu(n);
    if constexpr (state & (td_sz | td_maxson)) sz = vecu(n);
    if constexpr (state & td_fa) fa = vecu(n);
    if constexpr (state & td_dep) dep = vecu(n);
    if constexpr (state & td_maxson) maxson = vecu(n, n);
    if constexpr (state & td_maxdfn) maxdfn = vecu(n);
    if constexpr (state & td_euler) euler = vecu(n);
    if constexpr (state & td_go) go = vvecu(n, vecu(21u, n));
    if constexpr (state & td_dis) dis = vec<weight_type>(n);
    u32 cnt = 0;
    dfs(
      tree,
      tree.root,
      [&](u32 u, u32 f) {
        if constexpr (state & td_dfn) dfn[u] = cnt;
        if constexpr (state & td_euler) euler[cnt] = u;
        if constexpr (state & (td_dfn | td_maxdfn | td_euler)) ++cnt;
        if constexpr (state & (td_sz | td_maxson)) sz[u] = 1;
        if constexpr (state & td_fa) fa[u] = f;
        if constexpr (state & td_go) {
          go[u][0] = f;
          for (u32 i = 1; i <= 20u && go[u][i - 1] < n; i++)
            go[u][i] = go[go[u][i - 1]][i - 1];
        }
      },
      [&](u32 to, u32 u, weight_type const &w = 1) {
        if constexpr (state & td_dep) dep[to] = dep[u] + 1;
        if constexpr (state & td_dis) dis[to] = dis[u] + w;
      },
      [&](u32 to, u32 u, weight_type const & = 1) {
        if constexpr (state & (td_sz | td_maxson)) sz[u] += sz[to];
        if constexpr (state & td_maxson)
          if (maxson[u] == n || sz[to] > sz[maxson[u]]) maxson[u] = to;
      },
      [&](u32 u, u32) {
        if constexpr (state & td_maxdfn) maxdfn[u] = cnt - 1;
      });
    return *this;
  }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
struct tree: alist<false> {
  u32 root;
  explicit constexpr tree(u32 n, u32 root = 0): alist(n), root(root) {}
};
}  // namespace tifa_libs::graph
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist<> g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u - 1, v - 1);
  }
  auto fa = tifa_libs::graph::domtree(g).get_domtree(0);
  tifa_libs::graph::tree tr(n);
  for (u32 i = 1; i < n; ++i)
    if (~fa[i]) tr.add_arc(fa[i], i);
  tifa_libs::graph::tree_dfs_info<tifa_libs::graph::tree> dfs;
  dfs.reset_dfs_info<tifa_libs::graph::td_sz>(tr);
  std::cout << dfs.sz << '\n';
  return 0;
}
