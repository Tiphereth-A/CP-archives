#include <bits/stdc++.h>
using u32 = uint32_t;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
#undef assert
#define assert(x) 42
namespace tifa_libs::graph {
namespace adjlist_impl_ {
template <class T, bool isv = std::is_void_v<T>>
struct E;
template <class T>
struct E<T, false> {
  u32 to;
  T w;
  E() {}
  E(u32 v, T const &w): to(v), w(w) {}
};
template <class T>
struct E<T, true> {
  u32 to;
  E() {}
  explicit E(u32 v): to(v) {}
};
template <class T = void>
class adjlist {
protected:
  u32 m;
  vvec<E<T>> g;

public:
  explicit adjlist(u32 n = 0): m(0), g(n) {}
  void reset_v_size(u32 n) { g.resize(n); }
  void clear() { g.clear(); }
  void shrink() { g.shrink_to_fit(); }
  template <class... Ts>
  E<T> &add_arc(u32 u, Ts &&...args) {
    ++m;
    g[u].emplace_back(args...);
    return g[u].back();
  }
  template <class... Ts>
  ptt<E<T> &> add_edge(u32 u, u32 v, Ts &&...args) {
    return {add_arc(u, v, args...), add_arc(v, u, args...)};
  }
  auto &operator[](u32 u) { return g[u]; }
  auto operator[](u32 u) const { return g[u]; }
  u32 v_size() const { return (u32)g.size(); }
  u32 arc_size() const { return m; }
};
}  // namespace adjlist_impl_
using adjlist_impl_::adjlist;
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <class T>
adjlist<T> adjlist_rev(adjlist<T> const &g) {
  adjlist<T> ret(g.v_size());
  for (u32 i = 0; i < g.v_size(); ++i)
    for (auto e : g[i])
      if constexpr (std::is_void_v<T>) ret.add_arc(e.to, i);
      else ret.add_arc(e.to, i, -e.w);
  return ret;
}
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
class SCC {
  const adjlist<void> &g, &rev_g;

public:
  adjlist<void> dag;
  vec<u32> scc_id;
  vvec<u32> belongs;
  SCC(adjlist<void> const &g, adjlist<void> const &rev_g): g(g), rev_g(rev_g) {
    build();
  }

private:
  void build() {
    vec<bool> vis(g.v_size());
    vec<u32> ord;
    auto dfs = [&, this](auto &&dfs, u32 idx) {
      if (vis[idx]) return;
      vis[idx] = true;
      for (auto [to] : g[idx]) dfs(dfs, to);
      ord.push_back(idx);
    };
    auto rdfs = [this](auto &&rdfs, u32 idx, u32 cnt) {
      if (~scc_id[idx]) return;
      scc_id[idx] = cnt;
      for (auto [to] : rev_g[idx]) rdfs(rdfs, to, cnt);
    };
    for (u32 i = 0; i < g.v_size(); ++i) dfs(dfs, i);
    std::reverse(ord.begin(), ord.end());
    scc_id.resize(g.v_size(), (u32)-1);
    u32 cnt = 0;
    for (u32 i : ord)
      if (!~scc_id[i]) rdfs(rdfs, i, cnt++);
    dag.reset_v_size(cnt);
    belongs.resize(cnt);
    for (u32 i = 0; i < g.v_size(); ++i) {
      belongs[scc_id[i]].push_back(i);
      for (auto [to] : g[i])
        if (u32 x = scc_id[i], y = scc_id[to]; x != y) dag.add_arc(x, y);
    }
  }
};
}  // namespace tifa_libs::graph
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::adjlist<void> g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    g.add_arc(u, v);
  }
  tifa_libs::graph::SCC scc(g, tifa_libs::graph::adjlist_rev(g));
  u32 q;
  std::cin >> q;
  for (u32 i = 0, u, v; i < q; ++i) {
    std::cin >> u >> v;
    std::cout << (scc.scc_id[u] == scc.scc_id[v]) << '\n';
  }
  return 0;
}
