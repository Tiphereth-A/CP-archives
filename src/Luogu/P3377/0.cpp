#include <bits/stdc++.h>
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
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
#undef assert
#define assert(x) 42
using namespace std::literals;
constexpr i8 operator""_i8(unsigned long long x) { return (i8)x; }
constexpr i16 operator""_i16(unsigned long long x) { return (i16)x; }
constexpr i32 operator""_i32(unsigned long long x) { return (i32)x; }
constexpr i64 operator""_i64(unsigned long long x) { return (i64)x; }
constexpr isz operator""_iz(unsigned long long x) { return (isz)x; }
constexpr u8 operator""_u8(unsigned long long x) { return (u8)x; }
constexpr u16 operator""_u16(unsigned long long x) { return (u16)x; }
constexpr u32 operator""_u32(unsigned long long x) { return (u32)x; }
constexpr u64 operator""_u64(unsigned long long x) { return (u64)x; }
constexpr usz operator""_uz(unsigned long long x) { return (usz)x; }
namespace tifa_libs::ds {
template <class T>
class leftist_tree {
  u32 cnt;
  struct YYZ {
    u32 l, r;
    u32 dist, rt;
    T w;
    bool del;
    constexpr YYZ() {}
    constexpr YYZ(u32 l, u32 r, u32 dist_, u32 rt_, T w_, bool del_ = false)
      : l(l), r(r), dist(dist_), rt(rt_), w(w_), del(del_) {}
  };
  constexpr u32 merge_(u32 x, u32 y) {
    if (!~x || !~y) return x & y;
    if (t[y].w < t[x].w || (t[y].w == t[x].w && x > y)) std::swap(x, y);
    t[x].r = merge_(t[x].r, y);
    if (!~t[x].l || t[t[x].r].dist > t[t[x].l].dist) std::swap(t[x].l, t[x].r);
    t[x].dist = (!~t[x].r ? 0 : t[t[x].r].dist + 1);
    return x;
  }
  void del(u32 x) {
    t[x].del = true;
    t[x].rt = merge_(t[x].l, t[x].r);
    if (~t[x].l) t[t[x].l].rt = t[x].rt;
    if (~t[x].r) t[t[x].r].rt = t[x].rt;
  }

public:
  vec<YYZ> t;
  constexpr explicit leftist_tree(vec<T> const &a): t() {
    for (auto x : a) newheap(x);
  }
  constexpr explicit leftist_tree(u32 n = 0): t() {
    for (u32 i = 0; i < n; ++i) newheap();
  }
  void newheap(T w = T{}) {
    t.emplace_back(-1_u32, -1_u32, 0, t.size(), w, false);
  }
  u32 gf(u32 x) { return t[x].rt == x ? x : t[x].rt = gf(t[x].rt); }
  bool same(u32 x, u32 y) {
    if (t[x].del || t[y].del) return false;
    if ((x = gf(x)) == (y = gf(y))) return false;
    return true;
  }
  void merge(u32 x, u32 y) {
    if (t[x].del || t[y].del) return;
    if ((x = gf(x)) == (y = gf(y))) return;
    t[x].rt = t[y].rt = merge_(x, y);
  }
  T pop(u32 x) {
    if (t[x].del) return std::numeric_limits<T>::max();
    T ret = t[x = gf(x)].w;
    del(x);
    return ret;
  }
};
}  // namespace tifa_libs::ds
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  vec<i32> a(n);
  for (auto &x : a) std::cin >> x;
  tifa_libs::ds::leftist_tree<i32> tr(a);
  u32 opt, x, y;
  for (u32 i = 0; i < m; ++i) {
    std::cin >> opt >> x, --x;
    if (opt == 1) {
      std::cin >> y, --y;
      tr.merge(x, y);
    } else {
      i32 ret = tr.pop(x);
      if (ret == std::numeric_limits<i32>::max()) std::cout << "-1\n";
      else std::cout << ret << '\n';
    }
  }
  return 0;
}
