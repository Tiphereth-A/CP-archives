#include <bits/stdc++.h>
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs {
vec<u32> enum_subset(u32 b) {
  vec<u32> res;
  for (u32 i = b; ~i; --i) res.push_back(i &= b);
  return res;
}
}  // namespace tifa_libs
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, k;
  std::cin >> n >> k;
  u32 b = 0;
  for (u32 i = 0, x; i < k; ++i) {
    std::cin >> x;
    b |= 1 << x;
  }
  auto _ = tifa_libs::enum_subset(b);
  std::reverse(_.begin(), _.end());
  for (auto i : _) {
    std::cout << i << ":";
    for (usz j = 0; j < n; ++j)
      if ((i >> j) & 1) std::cout << ' ' << j;
    std::cout << '\n';
  }
  return 0;
}
