#include <bits/stdc++.h>
using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
#undef assert
#define assert(x) 42
namespace tifa_libs::graph {
namespace adjmat_impl_ {
template <class T = u32>
class adjmat {
  u32 m;
  vvec<T> g;

public:
  explicit adjmat(u32 n, T val = T{}): m(0), g(n, vec<T>(n, val)) {
    for (u32 i = 0; i < n; ++i) g[i][i] = 0;
  }
  T &add_arc(u32 u, u32 v, T const &w) {
    ++m;
    return g[u][v] = w;
  }
  auto &operator[](usz u) { return g[u]; }
  auto operator[](usz u) const { return g[u]; }
  auto &data() { return g; }
  auto data() const { return g; }
  auto &operator()(usz u, usz v) { return g[u][v]; }
  auto operator()(usz u, usz v) const { return g[u][v]; }
  usz v_size() const { return g.size(); }
  usz arc_size() const { return m; }
};
}  // namespace adjmat_impl_
using adjmat_impl_::adjmat;
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <class W>
std::optional<adjmat<W>> floyd(adjmat<W> g,
                               W INF = std::numeric_limits<W>::max() / 2 - 1) {
  u32 n = g.v_size();
  for (u32 k = 0; k < n; ++k)
    for (u32 x = 0; x < n; ++x) {
      if (g[x][k] == INF) continue;
      for (u32 y = 0; y < n; ++y) {
        if (g[k][y] == INF) continue;
        g[x][y] = std::min(g[x][y], g[x][k] + g[k][y]);
      }
    }
  for (u32 x = 0; x < n; ++x)
    if (g[x][x] < 0) return {};
  return g;
}
}  // namespace tifa_libs::graph
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  constexpr i64 INF = std::numeric_limits<i64>::max() / 2 - 1;
  tifa_libs::graph::adjmat<i64> g(n, INF);
  for (u32 i = 0; i < m; ++i) {
    u32 u, v;
    i32 w;
    std::cin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  auto d = tifa_libs::graph::floyd(g, INF);
  if (!d.has_value()) {
    std::cout << "NEGATIVE CYCLE\n";
    return 0;
  }
  for (auto const &i : d.value().data())
    for (u32 j = 0; j < n; ++j) {
      if (i[j] == INF) std::cout << "INF" << " \n"[j + 1 == n];
      else std::cout << i[j] << " \n"[j + 1 == n];
    }
  return 0;
}
