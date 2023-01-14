#include <bits/extc++.h>
#define TPN typename
#define CR const &
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#define mk_(w, t) \
  using w = t;    \
  w operator""_##w(unsigned long long x) { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using f128 = long double;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
struct edge_t {
  T w;
  u32 u, v;
};
template <class T>
struct pt3 {
  T _0, _1, _2;
};
template <class T>
struct pt4 {
  T _0, _1, _2, _3;
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
template <class U, class T>
using vvecp = vvec<std::pair<U, T>>;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                    \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)    \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T) \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
namespace tifa_libs {
using std::swap;
template <class T>
T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::graph {
template <class T>
struct alistw {
  using w_t = T;
  vvecp<u32, T> g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  explicit alistw(u32 n = 0): g(n), cnt_arc(0), deg_in(0), deg_out(0) {}
  void add_arc(u32 u, u32 v, T w) {
    g[u].emplace_back(v, w);
    ++cnt_arc;
  }
  void build() const {}
  u32 size() const { return (u32)g.size(); }
  vec<std::pair<u32, T>> &operator[](u32 u) { return g[u]; }
  vec<std::pair<u32, T>> CR operator[](u32 u) const { return g[u]; }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <class G>
bool bellman_ford(G CR g, u32 s, vec<TPN G::w_t> &dis) {
  const u32 n = g.size(), sn = (u32)std::sqrt(n);
  vecb vis(n);
  vecu dep(n);
  std::deque<u32> q({s});
  auto upd_q = [&] {
    if (q.size() >= 2 && dis[q.front()] > dis[q.back()])
      swap(q.front(), q.back());
  };
  dis[s] = 0, vis[s] = true, dep[s] = 1;
  while (!q.empty()) {
    const u32 u = q.front();
    q.pop_front(), upd_q(), vis[u] = false;
    for (auto [v, w] : g[u])
      if (dis[u] + w < dis[v]) {
        dis[v] = dis[u] + w;
        if (vis[v]) continue;
        if (++dep[v] > n) return false;
        vis[v] = true,
        ((1 < dep[v] && dep[v] < sn) ||
             dis[v] < TPN G::w_t(q.size() ? dis[q.front()] : 0) ?
           q.push_front(v) :
           q.push_back(v)),
        upd_q();
      }
  }
  return true;
}
template <class G>
bool bellman_ford(G CR g,
                  u32 s,
                  TPN G::w_t INF = std::numeric_limits<TPN G::w_t>::max() / 2 -
                                   1) {
  vec<TPN G::w_t> dis(g.size(), INF);
  return bellman_ford(g, s, dis);
}
}  // namespace tifa_libs::graph
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(2);
  u32 T;
  std::cin >> T;
  flt_(u32, t, 0, T) {
    u32 n, m;
    std::cin >> n >> m;
    tifa_libs::graph::alistw<f128> g(n + 1);
    flt_(u32, i, 0, m, u, v) {
      f128 w;
      std::cin >> u >> v >> w;
      g.add_arc(u, v, w);
    }
    f128 l = -1e7, r = 1e7, mid;
    auto chk = [&g](f128 x) {
      vec<f128> dis(g.size());
      flt_(u32, i, 1, g.size()) for (auto &[v, w] : g[i]) w -= x;
      flt_(
        u32, i, 1, g.size()) if (!tifa_libs::graph::bellman_ford(g, i, dis)) {
        flt_(u32, i, 1, g.size()) for (auto &[v, w] : g[i]) w += x;
        return true;
      }
      flt_(u32, i, 1, g.size()) for (auto &[v, w] : g[i]) w += x;
      return false;
    };
    while (r - l > 1e-10) {
      mid = (l + r) / 2;
      (chk(mid) ? r : l) = mid;
    }
    std::cout << "Case #" << t + 1 << ": ";
    if (abs(l - 1e7) < 1e-10) std::cout << "No cycle found.";
    else std::cout << l;
    std::cout << '\n';
  }
  return 0;
}
