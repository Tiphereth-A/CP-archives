#include <bits/stdc++.h>
#define CEXP constexpr
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
template <class T>
using vecpt = vec<ptt<T>>;
using vecb = vec<bool>;
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
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <class EW = u32, class EC = i32>
class ssp {
  struct TIFA {
    u32 to;
    EW w;
    EC c;
    u32 inv;
  };
  const u32 N, S, T;
  vec<i64> dis;
  vec<EW> flow;
  vecpt<u32> pre;
  bool spfa(u64 inflow) {
    dis = vec<i64>(N, std::numeric_limits<i64>::max() / 2 - 1);
    vecb inq(N);
    std::queue<u32> q({S});
    dis[S] = 0, flow[S] = EW(inflow), flow[T] = 0, inq[S] = 1;
    while (!q.empty()) {
      u32 u = q.front();
      q.pop(), inq[u] = 0;
      for (u32 i = 0; i < e[u].size(); ++i) {
        auto v = e[u][i];
        if (dis[u] + v.c < dis[v.to] && v.w) {
          dis[v.to] = dis[u] + v.c;
          if (!inq[v.to]) q.push(v.to), inq[v.to] = 1;
          flow[v.to] = min(flow[u], v.w);
          pre[v.to] = {u, i};
        }
      }
    }
    return flow[T];
  }
  CEXP void update(u64 &retflow, i64 &retcost) {
    retflow += flow[T];
    for (u32 u = T; u != S; u = pre[u].first) {
      e[pre[u].first][pre[u].second].w -= flow[T];
      e[u][e[pre[u].first][pre[u].second].inv].w += flow[T];
      retcost += i64(flow[T]) * e[pre[u].first][pre[u].second].c;
    }
  }

public:
  vvec<TIFA> e;
  CEXP ssp(u32 n, u32 s, u32 t)
    : N(n), S(s), T(t), dis(), flow(n), pre(n), e(n) {}
  CEXP void add(u32 u, u32 v, EW w, EC c) {
    u32 temu = u32(e[u].size()), temv = u32(e[v].size());
    e[u].push_back({v, w, c, temv}), e[v].push_back({u, 0, -c, temu});
  }
  CEXP std::pair<u64, i64>
  operator()(u64 inflow = std::numeric_limits<u64>::max()) {
    u64 retflow = 0;
    i64 retcost = 0;
    bool flag = inflow == std::numeric_limits<EW>::max();
    while (spfa(flag ? inflow : inflow - retflow)) update(retflow, retcost);
    return {retflow, retcost};
  }
};
}  // namespace tifa_libs::graph
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, s, t;
  std::cin >> n >> m >> s >> t;
  --s, --t;
  tifa_libs::graph::ssp mcmf(n, s, t);
  i32 c;
  for (u32 i = 0, u, v, w; i < m; ++i)
    std::cin >> u >> v >> w >> c, --u, --v, mcmf.add(u, v, w, c);
  auto [flow, cost] = mcmf();
  std::cout << flow << ' ' << cost;
  return 0;
}
