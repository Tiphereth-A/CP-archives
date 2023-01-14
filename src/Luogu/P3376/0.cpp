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
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
using vecu = vec<u32>;
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
    u32 lstu = (u32)e[u].size(), lstv = (u32)e[v].size();
    e[u].push_back({v, w, lstv}), e[v].push_back({u, rw, lstu});
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
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, s, t;
  std::cin >> n >> m >> s >> t;
  --s, --t;
  tifa_libs::graph::dinic maxflow(n);
  for (u32 i = 0, u, v, w; i < m; ++i)
    std::cin >> u >> v >> w, --u, --v, maxflow.add(u, v, w);
  std::cout << maxflow(s, t);
  return 0;
}
