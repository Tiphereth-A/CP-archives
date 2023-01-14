#include <bits/stdc++.h>
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
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
using pt3 = std::tuple<T, T, T>;
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
template <class EW = u32>
class dinic {
  struct YYZ {
    u32 to;
    EW w;
    u32 inv;
  };
  const u32 N;

public:
  vvec<YYZ> e;
  vecu dep, cur;
  constexpr dinic(u32 n): N(n), e(n) {}
  constexpr ptt<u32> add(u32 u, u32 v, EW w, EW rw = 0) {
    u32 temu = u32(e[u].size()), temv = u32(e[v].size());
    e[u].push_back({v, w, temv}), e[v].push_back({u, rw, temu});
    return {u, e[u].size() - 1};
  }
  u64 operator()(u32 s, u32 t) {
    u64 ret = 0, flow;
    while (bfs(s, t))
      while ((flow = dfs(s, t))) ret += flow;
    return ret;
  }

private:
  bool bfs(u32 s, u32 t) {
    dep = vecu(N, 0);
    std::queue<u32> q;
    dep[s] = 1, q.push(s);
    while (!q.empty()) {
      u32 u = q.front();
      q.pop();
      for (auto v : e[u])
        if (!dep[v.to] && v.w) dep[v.to] = dep[u] + 1, q.push(v.to);
    }
    cur = vecu(N, 0);
    return dep[t];
  }
  constexpr u64 dfs(u32 u, u32 t, EW lim = std::numeric_limits<EW>::max()) {
    if (u == t || lim == 0) return lim;
    u64 ret = 0;
    for (u32 &i = cur[u]; i < e[u].size(); ++i) {
      auto v = e[u][i];
      if (dep[v.to] == dep[u] + 1 && v.w) {
        u64 flow = dfs(v.to, t, std::min(v.w, lim));
        if (flow) {
          e[u][i].w -= flow;
          e[v.to][e[u][i].inv].w += flow;
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
constexpr vec<std::tuple<EW, u32, u32>>
gomory_hu(u32 n, vec<std::tuple<EW, u32, u32>> const &ed) {
  vec<u32> par(n);
  dinic<EW> D(n);
  vecpt<u32> ed_locs;
  for (auto [w, u, v] : ed) ed_locs.push_back(D.add(u, v, w, w));
  vec<std::tuple<EW, u32, u32>> ans;
  for (u32 i = 1; i < n; ++i) {
    for (auto [ed, loc] : ed_locs) {
      auto &e = D.e[ed][loc], &e_rev = D.e[e.to][e.inv];
      e.w = e_rev.w = (e.w + e_rev.w) / 2;
    }
    ans.emplace_back(D(i, par[i]), i, par[i]);
    for (u32 j = i + 1; j < n; ++j)
      if (par[j] == par[i] && D.dep[j]) par[j] = i;
  }
  return ans;
}
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <class T, bool with_deg = false>
struct alistw {
  using weight_type = T;
  using value_type = vvecp<u32, T>;
  value_type g;
  u32 cnt_arc;
  vecu deg_in;
  explicit constexpr alistw(u32 n = 0): g(n), cnt_arc(0), deg_in(0) {
    if constexpr (with_deg) deg_in.resize(n);
  }
  constexpr void add_arc(u32 u, u32 v, T const &w) {
    g[u].emplace_back(v, w), ++cnt_arc;
    if constexpr (with_deg) ++deg_in[v];
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
template <class G>
constexpr std::optional<vecu> path(G const &g, u32 from, u32 to) {
  vecu ret;
  bool failed = true;
  auto dfs = [&](auto &&dfs, u32 now, u32 fa) -> void {
    ret.push_back(now);
    if (now == to) {
      failed = false;
      return;
    }
    for (auto v : g.g[now]) {
      u32 to = 0;
      if constexpr (is_alist<G>) to = v;
      else to = v.first;
      if (to == fa) continue;
      dfs(dfs, to, now);
      if (!failed) return;
    }
    if (!failed) return;
    ret.pop_back();
  };
  dfs(dfs, from, -1_u32);
  if (failed) return {};
  return ret;
}
}  // namespace tifa_libs::graph
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<pt3<u32>> edges(m);
  ++n;
  for (auto &[w, u, v] : edges) std::cin >> u >> v >> w;
  auto gh_edges = tifa_libs::graph::gomory_hu(n, edges);
  u32 q;
  std::cin >> q;
  tifa_libs::graph::alistw<u32> g(n);
  for (auto &&[w, u, v] : gh_edges) g.add_arc(u, v, w), g.add_arc(v, u, w);
  std::map<ptt<u32>, u32> mp;
  for (auto &&[w, u, v] : gh_edges) mp[std::minmax(u, v)] = w;
  for (u32 i = 0, u, v; i < q; ++i) {
    std::cin >> u >> v;
    auto vs = tifa_libs::graph::path(g, u, v).value();
    u32 ans = std::numeric_limits<u32>::max();
    for (u32 j = 1; j < vs.size(); ++j) {
      u32 from = vs[j - 1], to = vs[j];
      ans = std::min(ans, mp[std::minmax(from, to)]);
    }
    std::cout << ans << '\n';
  }
  return 0;
}
