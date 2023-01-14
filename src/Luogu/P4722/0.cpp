#include <bits/stdc++.h>
#define CEXP constexpr
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
using vecu = vec<u32>;
using vvecu = vvec<u32>;
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
template <std::floating_point FP>
CEXP inline FP eps_v = FP(1e-8L);
using std::numbers::pi_v;
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <class T = u32>
class hlpp {
  static constexpr u32 inf = 0x3f3f3f3f;
  struct TIFA {
    u32 to;
    T w, inv;
  };
  vecu h, gap;
  const u32 n, s, t;
  u32 level;
  vvecu B;
  CEXP u32 select() {
    while (~level && B[level].empty()) --level;
    return ~level ? B[level].back() : 0;
  }

public:
  vvec<TIFA> e;
  vec<T> exf;
  CEXP hlpp(u32 n, u32 s, u32 t)
    : n(n), s(s), t(t), level(0), B(n), e(n), exf(n + 1) {}
  CEXP ptt<u32> add(u32 u, u32 v, T w, T rw = 0) {
    u32 lstu = (u32)e[u].size(), lstv = (u32)e[v].size();
    e[u].push_back({v, w, lstv}), e[v].push_back({u, rw, lstu});
    return {u, e[u].size() - 1};
  }
  T get() {
    if (!bfs_init()) return 0;
    gap = vecu(n, 0);
    flt_(u32, i, 0, n) if (h[i] != inf)++ gap[h[i]];
    h[s] = n;
    push(s);
    u32 u;
    while ((u = select())) {
      B[level].pop_back();
      if (push(u)) {
        if (!--gap[h[u]])
          flt_(u32, i, 0, n) if (i != s && h[i] > h[u] && h[i] < n + 1) h[i] =
            n + 1;
        relabel(u);
      }
    }
    return exf[t];
  }

private:
  bool bfs_init() {
    h = vecu(n, inf);
    std::queue<u32> q({t});
    h[t] = 0;
    while (!q.empty()) {
      u32 u = q.front();
      q.pop();
      for (auto [to, w, lstv] : e[u])
        if (e[to][lstv].w && h[to] > h[u] + 1) h[to] = h[u] + 1, q.push(to);
    }
    return h[s] != inf;
  }
  CEXP bool push(u32 u) {
    bool init = u == s;
    for (auto &[to, w, lstv] : e[u]) {
      if (!w || (init == false && h[u] != h[to] + 1) || h[to] == inf) continue;
      T k = init ? w : min(w, exf[u]);
      if (to != s && to != t && !exf[to])
        B[h[to]].push_back(to), level = max(level, h[to]);
      exf[u] -= k, exf[to] += k, w -= k, e[to][lstv].w += k;
      if (!exf[u]) return 0;
    }
    return 1;
  }
  CEXP void relabel(u32 u) {
    h[u] = inf;
    for (auto [to, w, _] : e[u])
      if (w) h[u] = min(h[u], h[to]);
    if (++h[u] < n) {
      B[h[u]].push_back(u);
      level = max(level, h[u]);
      ++gap[h[u]];
    }
  }
};
}  // namespace tifa_libs::graph
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, s, t;
  std::cin >> n >> m >> s >> t;
  --s, --t;
  tifa_libs::graph::hlpp<i64> maxflow(n, s, t);
  for (u32 i = 0, u, v, w; i < m; ++i)
    std::cin >> u >> v >> w, --u, --v, maxflow.add(u, v, w);
  std::cout << maxflow.get();
  return 0;
}
