#include <bits/stdc++.h>
#define CEXP constexpr
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
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class U, class T>
using vvecp = vvec<std::pair<U, T>>;
template <class T>
using vecpt = vec<ptt<T>>;
using vecu = vec<u32>;
using vvecu = vvec<u32>;
using vecu64 = vec<u64>;
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
inline const auto fn_0 = [](auto &&...) {};
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
template <class T, bool with_deg = false>
struct alistw {
  using weight_type = T;
  using value_type = vvecp<u32, T>;
  value_type g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  explicit CEXP alistw(u32 n = 0): g(n), cnt_arc(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) {
    g[u].emplace_back(v, w), ++cnt_arc;
    if CEXP (with_deg) ++deg_in[v], ++deg_out[u];
  }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <bool with_deg = false>
struct alist {
  using weight_type = u32;
  using value_type = vvecu;
  value_type g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  explicit CEXP alist(u32 n = 0): g(n), cnt_arc(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v) {
    g[u].push_back(v), ++cnt_arc;
    if CEXP (with_deg) ++deg_in[v], ++deg_out[u];
  }
};
template <class G>
concept is_alist =
  (std::is_base_of_v<alist<true>, G> || std::is_base_of_v<alist<false>, G>);
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
namespace dfs_impl_ {
template <class G, class Fb, class Fp, class Fs, class Fr>
CEXP void dfs_(G CR fg,
               u32 u,
               u32 fa,
               Fb &&init,
               Fp &&pre_dfs,
               Fs &&post_dfs,
               Fr &&before_return) {
  init(u, fa);
  for (auto v : fg.g[u])
    if CEXP (is_alist<G>) {
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
CEXP void dfs(G CR fg,
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
template <class T = u32>
class dinic {
  struct TIFA {
    u32 to;
    T w;
    u32 inv;
  };
  const u32 n;

public:
  vvec<TIFA> e;
  vecu dep, cur;
  CEXP dinic(u32 n): n(n), e(n) {}
  CEXP ptt<u32> add(u32 u, u32 v, T w, T rw = 0) {
    u32 lstu = (u32)e[u].size(), lstv = (u32)e[v].size();
    e[u].push_back({v, w, lstv}), e[v].push_back({u, rw, lstu});
    return {u, e[u].size() - 1};
  }
  template <class EW = u64>
  EW get(u32 s, u32 t) {
    EW ret = 0, flow;
    while (bfs(s, t))
      while ((flow = dfs<EW>(s, t))) ret += flow;
    return ret;
  }

private:
  bool bfs(u32 s, u32 t) {
    dep = vecu(n, 0);
    std::queue<u32> q({s});
    dep[s] = 1;
    while (!q.empty()) {
      const u32 u = q.front();
      q.pop();
      for (auto v : e[u])
        if (!dep[v.to] && v.w) dep[v.to] = dep[u] + 1, q.push(v.to);
    }
    cur = vecu(n, 0);
    return dep[t];
  }
  template <class EW>
  CEXP EW dfs(u32 u, u32 t, T lim = std::numeric_limits<T>::max()) {
    if (u == t || lim == 0) return lim;
    EW ret = 0;
    for (u32 &i = cur[u]; i < e[u].size(); ++i) {
      auto v = e[u][i];
      if (dep[v.to] == dep[u] + 1 && v.w) {
        EW flow = dfs<EW>(v.to, t, min(v.w, lim));
        if (flow) {
          e[u][i].w -= flow, e[v.to][e[u][i].inv].w += flow;
          ret += flow, lim -= flow;
          if (!lim) break;
        } else dep[v.to] = 0;
      }
    }
    return ret;
  }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <class EW>
CEXP vec<std::tuple<EW, u32, u32>>
gomory_hu(u32 n, vec<std::tuple<EW, u32, u32>> CR ed) {
  vecu par(n);
  dinic<EW> D(n);
  vecpt<u32> ed_locs;
  for (auto [w, u, v] : ed) ed_locs.push_back(D.add(u, v, w, w));
  vec<std::tuple<EW, u32, u32>> ans;
  flt_(u32, i, 1, n) {
    for (auto [ed, loc] : ed_locs) {
      auto &e = D.e[ed][loc], &e_rev = D.e[e.to][e.inv];
      e.w = e_rev.w = (e.w + e_rev.w) / 2;
    }
    ans.emplace_back(D.template get<EW>(i, par[i]), i, par[i]);
    flt_(u32, j, i + 1, n) if (par[j] == par[i] && D.dep[j]) par[j] = i;
  }
  return ans;
}
}  // namespace tifa_libs::graph
void solve() {
  u32 n, m;
  std::cin >> n >> m;
  vec<std::tuple<u64, u32, u32>> edges(m);
  for (auto &[w, u, v] : edges) {
    std::cin >> u >> v >> w;
    --u;
    --v;
  }
  tifa_libs::graph::alistw<u64> mct(n);
  vvec<u64> mat(n, vecu64(n, std::numeric_limits<u64>::max()));
  for (auto mct_edges = tifa_libs::graph::gomory_hu(n, edges);
       auto &&[w, u, v] : mct_edges) {
    mct.add_arc(u, v, w);
    mct.add_arc(v, u, w);
    mat[u][v] = mat[v][u] = w;
  }
  flt_(u32, r, 0, n) {
    tifa_libs::graph::dfs(
      mct,
      r,
      fn_0,
      [&](u32 v, u32 u, u64 w) {
        mat[r][v] = std::min({mat[r][v], mat[r][u], w});
      },
      fn_0,
      fn_0);
    mat[r][r] = 0;
  }
  std::map<u64, u32> cnts;
  flt_(u32, i, 0, n) flt_(u32, j, i + 1, n)++ cnts[mat[i][j]];
  u32 q;
  std::cin >> q;
  for (u32 i = 0, x; i < q; ++i) {
    std::cin >> x;
    u32 ans = 0;
    for (auto &&[k, v] : cnts) {
      if (k > x) break;
      ans += v;
    }
    std::cout << ans << '\n';
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    solve();
    if (t) std::cout << '\n';
  }
  return 0;
}
