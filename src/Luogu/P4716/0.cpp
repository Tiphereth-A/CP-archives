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
using ptt = std::pair<T, T>;
template <class T>
using pt3 = std::tuple<T, T, T>;
template <class T>
using pt4 = std::tuple<T, T, T, T>;
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
#define mk(A, T)                                                              \
  mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T) mk_(vec, A, T) mk_(vvec, A, T) \
    mk_(v3ec, A, T) mk_(vecpt, A, T) mk_(vvecpt, A, T) mk_(ptvec, A, T)       \
      mk_(ptvvec, A, T) mk_(spn, A, T) mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
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
namespace tifa_libs::ds {
template <bool RANK_ = false>
class dsu_basic {
  veci p;

public:
  explicit CEXP dsu_basic(u32 sz): p(sz, -1) {}
  CEXP i32 find(u32 x) { return p[x] < 0 ? (i32)x : p[x] = find((u32)p[x]); }
  CEXP u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  CEXP bool same(u32 x, u32 y) { return find(x) == find(y); }
  CEXP bool merge(u32 x, u32 y) {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if CEXP (RANK_)
      if (p[x] > p[y]) swap(x, y);
    return p[x] += p[y], p[y] = (i32)x, true;
  }
};
}  // namespace tifa_libs::ds
namespace tifa_libs::ds {
template <class T, class C = std::less<T>>
class skew_heap {
  static CEXP C comp_{};
  struct TIFA {
    T k, lz;
    u32 l, r, idx;
    TIFA() {}
    TIFA(cT_(T) key, u32 i = -1_u32)
      : k(key), lz(0), l(-1_u32), r(-1_u32), idx(i) {}
  };
  CEXP bool comp(u32 idxl, u32 idxr) const {
    return comp_(weight(idxl), weight(idxr));
  }
  CEXP void pd(u32 idx) {
    if (d[idx].lz == 0) return;
    if (~d[idx].l) d[d[idx].l].lz += d[idx].lz;
    if (~d[idx].r) d[d[idx].r].lz += d[idx].lz;
    d[idx].k += d[idx].lz, d[idx].lz = 0;
  }

public:
  vec<TIFA> d;
  CEXP T weight(u32 idx) const { return d[idx].k + d[idx].lz; }
  CEXP u32 newheap(cT_(T) key, u32 idx = -1_u32) {
    return d.emplace_back(key, idx), u32(d.size() - 1);
  }
  CEXP u32 merge(u32 x, u32 y) {
    if (!~x || !~y) return ~(x ^ y);
    if (!comp(x, y)) swap(x, y);
    return pd(x), swap(d[x].l, d[x].r = merge(d[x].r, y)), x;
  }
  CEXP void apply(u32 x, cT_(T) lz) { d[x].lz += lz, pd(x); }
  CEXP u32 push(u32 x, cT_(T) key, u32 idx = -1_u32) {
    return merge(x, newheap(key, idx));
  }
  CEXP u32 pop(u32 x) { return pd(x), merge(d[x].l, d[x].r); }
};
}  // namespace tifa_libs::ds
namespace tifa_libs::graph {
template <class T>
CEXP vec<std::tuple<T, u32, u32>>
cle(u32 n, u32 root, vec<std::tuple<T, u32, u32>> CR arcs) {
  ds::skew_heap<T> heap;
  ds::dsu_basic<> uf(n);
  vecu used(n, -1_u32), from(n), come(n, -1_u32);
  vec<T> from_cost(n);
  used[root] = root;
  vecu par_e(arcs.size(), -1_u32), stem(n, -1_u32), idxs;
  flt_(u32, i, 0, (u32)arcs.size()) {
    auto [w, u, v] = arcs[i];
    come[v] = heap.push(come[v], w, i);
  }
  T costs = 0;
  flt_(u32, start, 0, n) {
    if (~used[start]) continue;
    u32 now = start;
    vecu chi_e;
    u32 cyc = 0;
    while (!~used[now] || used[now] == start) {
      used[now] = start;
      auto &node = heap.d[come[now]];
      if (!~come[now]) return {};
      u32 src = (u32)uf.find(std::get<1>(arcs[node.idx]));
      T cost = heap.weight(come[now]);
      u32 idx = node.idx;
      if (come[now] = heap.pop(come[now]); src == now) continue;
      if (from[now] = src, from_cost[now] = cost; !~stem[now]) stem[now] = idx;
      costs += cost, idxs.push_back(idx);
      while (cyc) par_e[chi_e.back()] = idx, chi_e.pop_back(), --cyc;
      if (chi_e.push_back(idx); used[src] == start) {
        u32 p = now;
        do {
          if (~come[p]) heap.apply(come[p], -from_cost[p]);
          if (p != now) {
            uf.merge(p, now);
            u32 newheap = heap.merge(come[now], come[p]);
            come[now = (u32)uf.find(now)] = newheap;
          }
          p = (u32)uf.find(from[p]), ++cyc;
        } while (p != now);
      } else now = src;
    }
  }
  vecu vis_e(arcs.size());
  vec<std::tuple<T, u32, u32>> res;
  for (u32 _ = (u32)idxs.size(); _--;) {
    const u32 i = idxs[_];
    if (vis_e[i]) continue;
    auto [w, u, v] = arcs[i];
    res.push_back(arcs[i]);
    u32 x = stem[v];
    while (x != i) vis_e[x] = true, x = par_e[x];
  }
  return res;
}
}  // namespace tifa_libs::graph
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, r;
  std::cin >> n >> m >> r;
  vec<pt3u> arcs(m);
  for (auto &[w, u, v] : arcs) {
    std::cin >> u >> v >> w;
    --u;
    --v;
  }
  auto es = tifa_libs::graph::cle(n, r - 1, arcs);
  if (es.empty()) {
    std::cout << "-1\n";
    return 0;
  }
  u64 ans = 0;
  for (auto [w, u, v] : es) ans += w;
  std::cout << ans << '\n';
  return 0;
}
