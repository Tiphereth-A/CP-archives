#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
#undef assert
#define assert(x) 42
namespace tifa_libs::math {
constexpr std::tuple<u64, i64, i64> exgcd(i64 a, i64 b) {
  i64 x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b) {
    i64 c = a / b;
    std::tie(x1, x2, x3, x4, a, b) =
      std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
  }
  return {a, x1, x2};
}
}  // namespace tifa_libs::math
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i64 a, b;
  std::cin >> a >> b;
  auto [g, x, y] = tifa_libs::math::exgcd(a, b);
  std::cout << x << ' ' << y << '\n';
  return 0;
}
