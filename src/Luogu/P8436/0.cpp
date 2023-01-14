#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define CR const &
#define NE noexcept
#define CNE const noexcept
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
class e_bcc {
  struct EW {
    u32 to, inv;
  };
  vvec<EW> g;

public:
  u32 id;
  vecu ebcc_id, dfn, low;
  vecb cut;
  vvecu belongs;
  CEXPE e_bcc(u32 n) NE: g(n) {}
  CEXP void add_edge(u32 u, u32 v) NE {
    if (u == v) return;
    u32 tem1 = u32(g[u].size()), tem2 = u32(g[v].size());
    g[u].push_back({v, tem2}), g[v].push_back({u, tem1});
  }
  CEXP void build() NE {
    u32 cnt = 0, n = u32(g.size());
    id = 0, dfn = low = ebcc_id = vecu(n, n), cut = vecb(n, 0);
    vecu s;
    auto f = [&](auto &&f, u32 u, u32 fa, u32 inv_from) NE -> void {
      dfn[u] = low[u] = cnt++, s.push_back(u);
      flt_(u32, i, 0, (u32)g[u].size()) {
        auto v = g[u][i];
        if (v.to == fa && i == inv_from) continue;
        if (dfn[v.to] == n)
          f(f, v.to, u, v.inv), low[u] = min(low[u], low[v.to]);
        else low[u] = min(low[u], dfn[v.to]);
      }
      if (low[u] == dfn[u]) {
        belongs.push_back(vecu());
        do {
          const u32 v = s.back();
          if (s.pop_back(), ebcc_id[v] = id, belongs[id].push_back(v); v == u)
            return void(++id);
        } while (1);
      }
    };
    flt_(u32, i, 0, n) if (dfn[i] == n) f(f, i, i, -1_u32);
  }
};
}  // namespace tifa_libs::graph
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  tifa_libs::graph::e_bcc bcc(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    std::cin >> u >> v, --u, --v;
    bcc.add_edge(u, v);
  }
  bcc.build();
  std::cout << bcc.id << '\n';
  for (u32 i = 0; i < bcc.id; ++i) {
    for (std::cout << bcc.belongs[i].size() << ' '; auto x : bcc.belongs[i])
      std::cout << x + 1 << ' ';
    std::cout << '\n';
  }
  return 0;
}
