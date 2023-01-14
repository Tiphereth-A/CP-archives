#include <bits/extc++.h>
#define CEXP constexpr
#define CR const &
#define cT_(...)                                                \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t) * 2, \
                     __VA_ARGS__,                               \
                     __VA_ARGS__ CR>
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using f128 = long double;
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) |
                ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) |
                ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);
template <class T>
struct chash {
  CEXP static u64 C = u64(pi_v<f128> * 2e18) | 71;
  CEXP u64 operator()(T x) const {
    return __builtin_bswap64(((u64)x ^ TIME) * C);
  }
};
template <class T>
using ptt = std::pair<T, T>;
template <class T>
struct edge_t {
  T w;
  u32 u, v;
  CEXP auto operator<=>(edge_t CR) const = default;
};
template <class T>
struct pt3 {
  T _0, _1, _2;
  CEXP auto operator<=>(pt3 CR) const = default;
};
template <class T>
struct pt4 {
  T _0, _1, _2, _3;
  CEXP auto operator<=>(pt4 CR) const = default;
};
template <class E>
using itl = std::initializer_list<E>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using v3ec = vec<vvec<T>>;
template <class T>
using vecpt = vec<ptt<T>>;
template <class T>
using vvecpt = vvec<ptt<T>>;
template <class T>
using ptvec = ptt<vec<T>>;
template <class T>
using ptvvec = ptt<vvec<T>>;
template <class T, usz ext = std::dynamic_extent>
using spn = std::span<T const, ext>;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                          \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)          \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T)       \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) \
        mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
using namespace std::literals;
namespace tifa_libs {
using std::min;
template <class T>
CEXP T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <class W = u32, class C = i32>
class ssp {
  struct TIFA {
    u32 to, inv;
    W w;
    C c;
  };
  const u32 N, S, T;
  vec<W> flow;
  vecptu pre;
  template <class EW>
  bool sssp(EW inflow) {
    using SW = std::make_signed_t<EW>;
    vec<SW> dis(N, std::numeric_limits<SW>::max() / 2 - 1);
    vecb inq(N);
    std::queue<u32> q({S});
    dis[S] = 0, flow[S] = W(inflow), flow[T] = 0, inq[S] = 1;
    while (!q.empty()) {
      const u32 u = q.front();
      q.pop(), inq[u] = 0;
      flt_(u32, i, 0, (u32)e[u].size()) if (auto v = e[u][i];
                                            dis[u] + v.c < dis[v.to] && v.w) {
        if (dis[v.to] = dis[u] + v.c; !inq[v.to]) q.push(v.to), inq[v.to] = 1;
        flow[v.to] = min(flow[u], v.w), pre[v.to] = {u, i};
      }
    }
    return flow[T];
  }
  template <class EW, class EC>
  CEXP void update(EW &retflow, EC &retcost) {
    retflow += flow[T];
    for (u32 u = T; u != S; u = pre[u].first)
      e[pre[u].first][pre[u].second].w -= flow[T],
        e[u][e[pre[u].first][pre[u].second].inv].w += flow[T],
        retcost += EC(flow[T]) * e[pre[u].first][pre[u].second].c;
  }

public:
  vvec<TIFA> e;
  CEXP ssp(u32 n, u32 s, u32 t): N(n), S(s), T(t), flow(n), pre(n), e(n) {}
  CEXP void add(u32 u, u32 v, cT_(W) w, cT_(C) c) {
    const u32 lu = u32(e[u].size()), lv = u32(e[v].size());
    e[u].push_back({v, lv, w, c}), e[v].push_back({u, lu, 0, -c});
  }
  template <class EW = u64, class EC = i64>
  CEXP std::pair<EW, EC> get(EW inflow = std::numeric_limits<EW>::max()) {
    EW retflow = 0;
    EC retcost = 0;
    const bool flag = inflow == std::numeric_limits<W>::max();
    while (sssp(flag ? inflow : inflow - retflow)) update(retflow, retcost);
    return {retflow, retcost};
  }
};
}  // namespace tifa_libs::graph
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  const u32 S = n * m * 4, T = n * m * 4 + 1;
  tifa_libs::graph::ssp g(n * m * 4 + 2, S, T);
  auto f = [m](u32 i, u32 j, int d) { return (i * m + j) * 4 + (u32)d; };
  u64 cnt = 0;
  auto conn0 = [&](u32 i, u32 j, int d) {
    d %= 4;
    u32 _ = f(i, j, d);
    if ((i + j) & 1) g.add(_, T, 1, 0);
    else g.add(S, _, 1, 0);
  };
  auto conn = [&](u32 i, u32 j, int d1, int d2, int c) {
    if (c == 3) c = 1;
    d1 %= 4, d2 %= 4;
    if ((i + j) & 1) std::swap(d1, d2);
    g.add(f(i, j, d1), f(i, j, d2), 1, c);
  };
  auto valid = [&](i32 x, i32 y) {
    return x >= 0 && y >= 0 && x < (i32)n && y < (i32)m;
  };
  flt_(u32, i, 0, n, s) flt_(u32, j, 0, m) {
    std::cin >> s;
    if (~(i + j) & 1) {
      if (valid((i32)i - 1, (i32)j)) g.add(f(i, j, 0), f(i - 1, j, 2), 1, 0);
      if (valid((i32)i, (i32)j + 1)) g.add(f(i, j, 1), f(i, j + 1, 3), 1, 0);
      if (valid((i32)i + 1, (i32)j)) g.add(f(i, j, 2), f(i + 1, j, 0), 1, 0);
      if (valid((i32)i, (i32)j - 1)) g.add(f(i, j, 3), f(i, j - 1, 1), 1, 0);
    }
    cnt += (u32)std::popcount(s);
    switch (std::popcount(s)) {
      case 1: {
        int x = std::countr_zero(s);
        conn0(i, j, x);
        conn(i, j, x, x + 1, 1);
        conn(i, j, x, x + 2, 2);
        conn(i, j, x, x + 3, 1);
      } break;
      case 2: {
        int x = -1, y = -1;
        flt_(int, i, 0, 4) if (s & (1 << i))(!~x ? x : y) = i;
        conn0(i, j, x);
        conn0(i, j, y);
        if (std::abs(x - y) == 2) break;
        conn(i, j, x, x + 2, 1);
        conn(i, j, y, y + 2, 1);
      } break;
      case 3: {
        int x = std::countr_one(s);
        flt_(int, _, 0, 4) if (_ != x) {
          conn0(i, j, _);
          conn(i, j, _, x, std::abs(_ - x));
        }
      } break;
      case 4:
        conn0(i, j, 0);
        conn0(i, j, 1);
        conn0(i, j, 2);
        conn0(i, j, 3);
        break;
    }
  }
  auto [x, y] = g.get();
  if (x * 2 != cnt) std::cout << "-1\n";
  else std::cout << y << '\n';
  return 0;
}
