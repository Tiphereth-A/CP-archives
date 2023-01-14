#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define CR const &
#define NE noexcept
#define CNE const noexcept
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
  CEXP w operator""_##w(unsigned long long x) NE { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using f128 = long double;
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) NE {
  eps_v<FP> = v;
}
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) |
                ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) |
                ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);
template <class T>
struct chash {
  CEXP static u64 C = u64(pi_v<f128> * 2e18) | 71;
  CEXP u64 operator()(T x) CNE {
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
using std::set, std::map;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                          \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)          \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T)       \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) \
        mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
using namespace std::ranges;
using namespace std::literals;
namespace tifa_libs {
using std::swap;
template <class T>
CEXP T abs(T x) NE {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <bool with_deg = false>
struct eog {
  vecu head;
  vecptu e;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXPE eog(u32 n = 0) NE:
    head(n, -1_u32),
    e(),
    cnt_arc{0},
    deg_in(0),
    deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP u32 v_cnt() CNE { return (u32)head.size(); }
  CEXP u32 arc_cnt() CNE { return (u32)e.size(); }
  CEXP void add_arc(u32 u, u32 v) NE {
    e.emplace_back(v, head[u]), head[u] = u32(e.size() - 1);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void add_edge(u32 u, u32 v) NE { add_arc(u, v), add_arc(v, u); }
  CEXP void pop_startwith(u32 now) NE {
    if CEXP (--cnt_arc; with_deg) --deg_in[e[head[now]].first], --deg_out[now];
    head[now] = e[head[now]].second;
  }
  template <class F>
  requires requires(F f, u32 eid, u32 to, u32 next) { f(eid, to, next); }
  CEXP void foreach(u32 u, F && f) CNE {
    for (u32 i = head[u]; ~i; i = e[i].second) f(i, e[i].first, e[i].second);
  }
};
template <class T, bool with_deg = false>
struct eogw {
  struct TIFA {
    u32 to;
    T w;
    u32 nxt;
  };
  vecu head;
  vec<TIFA> e;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXPE eogw(u32 n = 0) NE:
    head(n, -1_u32),
    e(),
    cnt_arc{0},
    deg_in(0),
    deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) NE {
    e.emplace_back(v, w, head[u]), head[u] = u32(e.size() - 1);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void pop_startwith(u32 now) NE {
    if CEXP (--cnt_arc; with_deg) --deg_in[e[head[now]].first], --deg_out[now];
    head[now] = e[head[now]].second;
  }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
struct e_bcc {
  vecu dfn, low;
  vvecu belongs;
  template <bool with_deg>
  CEXP e_bcc(eog<with_deg> CR g) NE: dfn(g.v_cnt()), low(g.v_cnt()) {
    vecu stk;
    u32 tot = 0;
    auto tarjan = [&](auto &&f, u32 u, u32 fa_eid) -> void {
      dfn[u] = low[u] = ++tot;
      stk.push_back(u);
      g.foreach(u, [&](u32 eid, u32 v, u32) {
        if (!dfn[v]) f(f, v, eid), low[u] = min(low[u], low[v]);
        else if (eid != fa_eid && eid != (fa_eid ^ 1))
          low[u] = min(low[u], dfn[v]);
      });
      if (low[u] == dfn[u]) {
        vecu res;
        u32 p;
        do res.push_back(p = stk.back()), stk.pop_back();
        while (u != p);
        belongs.emplace_back(std::move(res));
      }
    };
    flt_(u32, i, 0, g.v_cnt()) if (!dfn[i]) tarjan(tarjan, i, -1_u32);
  }
};
}  // namespace tifa_libs::graph
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::eog g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    --u, --v;
    g.add_edge(u, v);
  }
  tifa_libs::graph::e_bcc bcc(g);
  std::cout << bcc.belongs.size() << '\n';
  for (auto &&b : bcc.belongs) {
    for (std::cout << b.size() << ' '; auto x : b) std::cout << x + 1 << ' ';
    std::cout << '\n';
  }
  return 0;
}
