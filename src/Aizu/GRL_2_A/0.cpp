#include <bits/stdc++.h>
using i32 = int32_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
#undef assert
#define assert(x) 42
namespace tifa_libs::ds {
template <bool RANK_ = false>
class dsu_basic {
  vec<i32> p;

public:
  explicit dsu_basic(usz sz): p(sz, -1) {}
  i32 find(u32 x) { return p[x] < 0 ? (i32)x : p[x] = find((u32)p[x]); }
  u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  bool same(u32 x, u32 y) { return find(x) == find(y); }
  bool merge(u32 x, u32 y) {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if constexpr (RANK_)
      if (p[x] > p[y]) std::swap(x, y);
    p[x] += p[y];
    p[y] = (i32)x;
    return true;
  }
};
}  // namespace tifa_libs::ds
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
enum state_tdfs {
  s_dfn = 1,
  s_sz = 2,
  s_fa = 4,
  s_dep = 8,
  s_maxson = 16,
  s_go = 32,
  s_sum_node_w = 64
};
template <class T = void>
struct tree: public adjlist<T> {
  u32 rt;
  vec<u32> node_w, dfn, sz, fa, dep, maxson, top;
  vec<u64> sum_node_w;
  vec<vec<u32>> go;
  explicit tree(u32 n, u32 root = 0, vec<u32> NODE_W = vec<u32>())
    : adjlist<T>(n), rt(root), node_w(NODE_W) {}
  void clear(u32 u = 0, u32 fa = 0) {
    for (auto v : this->g[u])
      if (v.to != fa) clear(v.to, u);
    this->g[u].clear();
  }
  template <int state>
  void reset_dfs_info() {
    u32 n = (u32)this->v_size();
    if constexpr (state & s_dfn) dfn = vec<u32>(n);
    if constexpr (state & (s_sz | s_maxson)) sz = vec<u32>(n);
    if constexpr (state & s_fa) fa = vec<u32>(n);
    if constexpr (state & s_dep) dep = vec<u32>(n);
    if constexpr (state & s_maxson) maxson = vec<u32>(n, n);
    if constexpr (state & s_go) go = vec<vec<u32>>(n, vec<u32>(21u, n));
    if constexpr (state & s_sum_node_w) sum_node_w = vec<u64>(n);
    u32 cnt = 0;
    auto before = [&](u32 u, u32 f) {
      if constexpr (state & s_dfn) dfn[u] = cnt++;
      if constexpr (state & (s_sz | s_maxson)) sz[u] = 1;
      if constexpr (state & s_fa) fa[u] = f;
      if constexpr (state & s_go) {
        go[u][0] = f;
        for (u32 i = 1; i <= 20u && go[u][i - 1] < n; i++)
          go[u][i] = go[go[u][i - 1]][i - 1];
      }
      if constexpr (state & s_sum_node_w) sum_node_w[u] = node_w[u];
    };
    auto pre_dfs = [&](auto const &ev, u32 u) {
      if constexpr (state & s_dep) dep[ev.to] = dep[u] + 1;
    };
    auto post_dfs = [&](auto const &ev, u32 u) {
      if constexpr (state & (s_sz | s_maxson)) sz[u] += sz[ev.to];
      if constexpr (state & s_maxson)
        if (maxson[u] == n || sz[ev.to] > sz[maxson[u]]) maxson[u] = ev.to;
      if constexpr (state & s_sum_node_w) sum_node_w[u] += sum_node_w[ev.to];
    };
    dfs_(rt, n, before, pre_dfs, post_dfs);
  }
  template <bool need_dfn = false>
  void reset_top() {
    u32 n = (u32)this->v_size();
    if (maxson.empty()) reset_dfs_info<s_maxson>();
    if constexpr (need_dfn) dfn = vec<u32>(n);
    top = vec<u32>(n, n);
    u32 cnt = 0;
    auto before = [&](u32 u, u32 top_) {
      if constexpr (need_dfn) dfn[u] = cnt++;
      top[u] = top_;
    };
    dfs_top_(rt, rt, before);
  }

private:
  template <class Fb, class Fp, class Fs>
  void dfs_(u32 u, u32 fa, Fb before, Fp pre_dfs, Fs post_dfs) {
    before(u, fa);
    for (auto v : this->g[u])
      if (v.to != fa) {
        pre_dfs(v, u);
        dfs_(v.to, u, before, pre_dfs, post_dfs);
        post_dfs(v, u);
      }
  }
  template <class F>
  void dfs_top_(u32 u, u32 top_, F before) {
    before(u, top_);
    if (maxson[u] == this->v_size()) return;
    dfs_top_(maxson[u], top_, before);
    for (auto v : this->g[u])
      if (top[v.to] == this->v_size()) dfs_top_(v.to, v.to, before);
  }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <class T>
tree<T> kruskal(vec<std::tuple<T, u32, u32>> a, u32 n, u32 root = 0) {
  std::sort(a.begin(), a.end());
  tree<T> tr(n, root);
  ds::dsu_basic dsu(n);
  u32 m = n - 1;
  for (auto [w, u, v] : a) {
    if (dsu.merge(u, v)) tr.add_edge(u, v, w), --m;
    if (m == 0) break;
  }
  return tr;
}
}  // namespace tifa_libs::graph
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<std::tuple<u32, u32, u32>> e(m);
  for (auto &[w, u, v] : e) std::cin >> u >> v >> w;
  auto tr = tifa_libs::graph::kruskal<u32>(e, n);
  u32 ret = 0;
  for (u32 i = 0; i < n; ++i)
    for (auto x : tr[i]) ret += x.w;
  std::cout << ret / 2 << '\n';
  return 0;
}
