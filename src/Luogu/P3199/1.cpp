#include <bits/extc++.h>
#define CEXP constexpr
#define CR const &
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
using f64 = double;
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
using std::swap;
template <class T>
CEXP T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <class T>
CEXP T min_cycle_mean(vec<edge_t<T>> CR edges,
                      u32 n,
                      T INF = std::numeric_limits<T>::max() / 2 - 1) {
  vec<T> F(n + 1), G(n + 1);
  for (u32 i = 0; i < n; ++i, std::swap(F, G)) {
    std::fill_n(F.begin(), n, INF);
    for (auto [w, u, v] : edges) F[v] = std::min(F[v], G[u] + w);
  }
  vec<T> Fn = G, maxv(n + 1);
  T ans = INF;
  std::ranges::transform(Fn, maxv.begin(), [&](auto x) { return x / n; });
  std::ranges::fill(G, 0);
  for (u32 i = 1; i < n; ++i, std::swap(F, G)) {
    std::fill_n(F.begin(), n, INF);
    for (auto [w, u, v] : edges) F[v] = std::min(F[v], G[u] + w);
    flt_(u32, j, 0, n) maxv[j] = std::max(maxv[j], (Fn[j] - F[j]) / (n - i));
  }
  flt_(u32, i, 0, n) if (Fn[i] < INF) ans = std::min(ans, maxv[i]);
  return ans;
}
}  // namespace tifa_libs::graph
int main() {
  u32 n, m;
  std::cin >> n >> m;
  vec<edge_t<f64>> e(m);
  for (auto &[w, u, v] : e) std::cin >> u >> v >> w;
  std::cout << std::fixed << std::setprecision(8)
            << tifa_libs::graph::min_cycle_mean(e, n + 1) << '\n';
}
