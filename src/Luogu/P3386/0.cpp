#include <bits/stdc++.h>
#define CEXP constexpr
#define CR const &
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
template <class T>
using vecpt = vec<ptt<T>>;
using vecu = vec<u32>;
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
inline vecpt<u32> hopkap(u32 l, u32 r, vecpt<u32> CR e) {
  vvec<u32> adj(l);
  vecu pre(r, -1_u32), nxt(l, -1_u32);
  for (auto [u, v] : e) adj[u].push_back(v);
  while (1) {
    vecu lev(l), ptr(l);
    u32 max_lev = 0;
    std::queue<u32> q;
    flt_(u32, i, 0, l) if (!~nxt[i]) lev[i] = 1, q.push(i);
    while (!q.empty()) {
      u32 x = q.front();
      q.pop();
      for (u32 y : adj[x])
        if (u32 z = pre[y]; !~z) max_lev = lev[x];
        else if (!lev[z]) lev[z] = lev[x] + 1, q.push(z);
      if (max_lev) break;
    }
    if (!max_lev) break;
    flt_(u32, i, 0, l) if (lev[i] > max_lev) lev[i] = 0;
    auto f = [&](auto &&f, u32 x) -> bool {
      for (; ptr[x] < adj[x].size(); ++ptr[x]) {
        u32 y = adj[x][ptr[x]], z = pre[y];
        if (!~z || (lev[z] == lev[x] + 1 && f(f, z)))
          return nxt[x] = y, pre[y] = x, ptr[x] = (u32)adj[x].size(), 1;
      }
      return 0;
    };
    flt_(u32, i, 0, l) if (!~nxt[i]) f(f, i);
  }
  vecpt<u32> ans;
  flt_(u32, i, 0, l) if (~nxt[i]) ans.emplace_back(i, nxt[i]);
  return ans;
}
}  // namespace tifa_libs::graph
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 l, r, m;
  std::cin >> l >> r >> m;
  vecpt<u32> edges(m);
  ++l, ++r;
  for (auto &[u, v] : edges) std::cin >> u >> v;
  auto ans = tifa_libs::graph::hopkap(l, r, edges);
  std::cout << ans.size() << '\n';
  return 0;
}
