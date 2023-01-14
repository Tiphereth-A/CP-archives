#include <bits/stdc++.h>
using u32 = uint32_t;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using pqg = std::priority_queue<T, vec<T>, std::greater<T>>;
#undef assert
#define assert(x) 42
namespace tifa_libs {
template <class T>
using is_s128 = typename std::conditional<std::is_same_v<T, __int128_t> ||
                                            std::is_same_v<T, __int128>,
                                          std::true_type,
                                          std::false_type>::type;
template <class T>
using is_u128 =
  typename std::conditional<std::is_same_v<T, __uint128_t> ||
                              std::is_same_v<T, unsigned __int128>,
                            std::true_type,
                            std::false_type>::type;
template <class T>
using is_int =
  typename std::conditional_t<std::is_integral_v<T> || is_s128<T>::value ||
                                is_u128<T>::value,
                              std::true_type,
                              std::false_type>;
template <class T>
using is_sint =
  typename std::conditional_t<is_s128<T>::value ||
                                (is_int<T>::value && std::is_signed_v<T>),
                              std::true_type,
                              std::false_type>;
}  // namespace tifa_libs
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
template <class W, class F>
vec<W> dijkstra(adjlist<W> const &g,
                u32 s,
                F cb_relax,
                W INF = std::numeric_limits<W>::max() / 2 - 1) {
  static_assert(!is_sint<W>::value);
  vec<W> dis(g.v_size(), INF);
  vec<bool> vis(g.v_size());
  pqg<std::pair<W, u32>> q;
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    auto [dis_now, now] = q.top();
    q.pop();
    if (vis[now]) continue;
    vis[now] = true;
    for (auto [to, w] : g[now])
      if (dis[now] + w < dis[to]) {
        cb_relax(now, to);
        dis[to] = dis[now] + w;
        if (!vis[to]) q.emplace(dis[to], to);
      }
  }
  return dis;
}
}  // namespace tifa_libs::graph
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, r;
  std::cin >> n >> m >> r;
  tifa_libs::graph::adjlist<u32> g(n);
  for (u32 i = 0, u, v, w; i < m; ++i) {
    std::cin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  constexpr u32 INF = std::numeric_limits<u32>::max() / 2 - 1;
  auto d = tifa_libs::graph::dijkstra(g, r, [](u32, u32) {}, INF);
  for (u32 i : d)
    if (i == INF) std::cout << "INF\n";
    else std::cout << i << '\n';
  return 0;
}
