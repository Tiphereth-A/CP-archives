#include <bits/stdc++.h>
using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::ds {
class dsu_weighted {
  vec<i32> p;
  vec<i64> dep;

public:
  explicit dsu_weighted(usz n): p(n, -1), dep(n) {}
  i32 find(u32 x) {
    if (p[x] < 0) return (i32)x;
    auto _ = find((u32)p[x]);
    dep[x] += dep[(u32)p[x]];
    return p[x] = _;
  }
  u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  i64 depth(u32 x) { return find(x), dep[x]; }
  bool same(u32 x, u32 y) { return find(x) == find(y); }
  bool merge(u32 x, u32 y, i64 d = 1) {
    (d += depth(y) - depth(x)) *= -1;
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if (p[x] > p[y]) {
      std::swap(x, y);
      d *= -1;
    }
    p[x] += p[y];
    p[y] = (i32)x;
    dep[y] = d;
    return true;
  }
};
}  // namespace tifa_libs::ds
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n, q;
  std::cin >> n >> q;
  tifa_libs::ds::dsu_weighted dsu(n);
  for (usz i = 0; i < q; ++i) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) {
      if (!dsu.same(u, v)) std::cout << "?\n";
      else std::cout << dsu.depth(u) - dsu.depth(v) << '\n';
    } else {
      i64 k;
      std::cin >> k;
      dsu.merge(u, v, k);
    }
  }
  return 0;
}
