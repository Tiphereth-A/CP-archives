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
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
using vecu = vec<u32>;
using vvecu = vvec<u32>;
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
struct tarjan {
  u32 id;
  vecu scc_id, dfn, low;
  vvecu belongs;
  CEXP void build(cT_(vvecu) g) {
    id = 0;
    u32 cnt = 0, n = u32(g.size());
    vecu s;
    vecb ins(n);
    dfn = low = scc_id = vecu(n, n);
    auto dfs = [&](auto &&dfs, u32 u) -> void {
      for (dfn[u] = low[u] = cnt++, s.push_back(u), ins[u] = 1; auto v : g[u])
        if (dfn[v] == n) dfs(dfs, v), low[u] = min(low[u], low[v]);
        else if (ins[v]) low[u] = min(low[u], dfn[v]);
      if (low[u] == dfn[u]) {
        belongs.push_back(vecu());
        do {
          const u32 v = s.back();
          s.pop_back(), ins[v] = 0, belongs[scc_id[v] = id].push_back(v);
          if (v == u) return void(++id);
        } while (1);
      }
    };
    flt_(u32, i, 0, n) if (dfn[i] == n) dfs(dfs, i);
  }
};
}  // namespace tifa_libs::graph
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  vecu a(n);
  for (auto &x : a) std::cin >> x;
  vvecu e(n);
  for (u32 i = 0, u, v; i < m; ++i)
    std::cin >> u >> v, e[u - 1].push_back(v - 1);
  tifa_libs::graph::tarjan scc;
  scc.build(e);
  vvecu g(scc.id);
  vecu in(scc.id), b(scc.id), dp(scc.id, 1'000'000'000);
  for (u32 i = 0, x, y; i < n; ++i) {
    for (b[x = scc.scc_id[i]] += a[i]; auto v : e[i])
      if (x != (y = scc.scc_id[v])) g[x].push_back(y), ++in[y];
  }
  auto dfs = [&](auto &&dfs, u32 u) -> void {
    if (dp[u] != 1'000'000'000) return;
    for (dp[u] = b[u]; auto v : g[u])
      dfs(dfs, v), dp[u] = tifa_libs::max(dp[u], b[u] + dp[v]);
  };
  u32 ret = 0;
  flt_(u32, i, 0, scc.id) if (!in[i]) dfs(dfs, i),
    ret = tifa_libs::max(ret, dp[i]);
  std::cout << ret;
  return 0;
}
