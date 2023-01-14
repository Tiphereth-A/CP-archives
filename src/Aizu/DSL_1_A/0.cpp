#include <bits/stdc++.h>
using i32 = int32_t;
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::ds {
template <bool RANK_ = false>
class dsu_basic {
  vec<i32> p;

public:
  explicit dsu_basic(usz sz): p(sz, -1) {}
  i32 find(u32 x) { return p[x] < 0 ? (i32)x : p[x] = find((u32)p[x]); }
  u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  bool same(u32 x, u32 y) { return find(x) == find(y); }
  bool merge(u32 x, u32 y) {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if constexpr (RANK_)
      if (p[x] > p[y]) std::swap(x, y);
    p[x] += p[y];
    p[y] = (i32)x;
    return true;
  }
};
}  // namespace tifa_libs::ds
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n, q;
  std::cin >> n >> q;
  tifa_libs::ds::dsu_basic dsu(n);
  for (usz i = 0; i < q; ++i) {
    u32 op, u, v;
    std::cin >> op >> u >> v;
    if (op) std::cout << dsu.same(u, v) << '\n';
    else dsu.merge(u, v);
  }
  return 0;
}
