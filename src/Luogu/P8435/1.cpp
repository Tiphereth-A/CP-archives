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
template <class U, class T>
using vvecp = vvec<std::pair<U, T>>;
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
struct alist {
  using w_t = void;
  vvecu g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXPE alist(u32 n = 0) NE: g(n), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v) NE {
    g[u].push_back(v);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void build() CNE {}
  CEXP u32 size() CNE { return (u32)g.size(); }
  CEXP auto &operator[](u32 u) NE { return g[u]; }
  CEXP auto CR operator[](u32 u) CNE { return g[u]; }
};
template <class T, bool with_deg = false>
struct alistw {
  using w_t = T;
  vvecp<u32, T> g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  CEXPE alistw(u32 n = 0) NE: g(n), cnt_arc(0), deg_in(0), deg_out(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v, cT_(T) w) NE {
    g[u].emplace_back(v, w);
    if CEXP (++cnt_arc; with_deg) ++deg_in[v], ++deg_out[u];
  }
  CEXP void build() CNE {}
  CEXP u32 size() CNE { return (u32)g.size(); }
  CEXP auto &operator[](u32 u) NE { return g[u]; }
  CEXP auto CR operator[](u32 u) CNE { return g[u]; }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <bool with_deg = false>
class v_bcc {
  alist<with_deg> CR g;

public:
  vecu dfn, low;
  vecb cut;
  vvecu belongs;
  CEXP v_bcc(alist<with_deg> CR G) NE:
    g(G),
    dfn(G.size()),
    low(G.size()),
    cut(G.size()) {
    vecu stk;
    u32 cnt = 0;
    auto tarjan = [&](auto &&f, u32 u, u32 fa) -> void {
      u32 son = 0;
      low[u] = dfn[u] = ++cnt;
      stk.push_back(u);
      for (auto v : g[u])
        if (!dfn[v]) {
          if (++son, f(f, v, u), low[u] = min(low[u], low[v]);
              low[v] >= dfn[u]) {
            auto it = find(stk, v);
            const u32 n = u32(stk.end() - it);
            vecu now(n + 1);
            now[0] = u;
            if (n) {
              move(it, stk.end(), now.begin() + 1);
              stk.resize(u32(it - stk.begin()));
            }
            belongs.push_back(now);
          }
        } else if (v != fa) low[u] = min(low[u], dfn[v]);
      if (!~fa && !son) belongs.push_back({u});
    };
    flt_(u32, i, 0, g.size()) if (!dfn[i]) tarjan(tarjan, i, -1_u32);
  }
};
}  // namespace tifa_libs::graph
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v;
    --u, --v;
    g.add_arc(u, v), g.add_arc(v, u);
  }
  tifa_libs::graph::v_bcc bcc(g);
  std::cout << bcc.belongs.size() << '\n';
  flt_(u32, i, 0, (u32)bcc.belongs.size()) {
    std::cout << bcc.belongs[i].size();
    for (auto x : bcc.belongs[i]) std::cout << ' ' << x + 1;
    std::cout << '\n';
  }
}
