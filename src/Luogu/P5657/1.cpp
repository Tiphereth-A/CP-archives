#include <bits/stdc++.h>
namespace tifa_libs {
using u32 = uint32_t;
using u64 = uint64_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
}  // namespace tifa_libs
namespace tifa_libs::util {
std::bitset<64> gray_code(u32 n, u64 k) {
  std::bitset<64> res;
  k ^= k >> 1;
  while (~--n) res.set(n, k >> n & 1);
  return res;
}
vec<u32> gray_code(u32 n) {
  vec<u32> ret(1 << n);
  for (u32 i = 0; i < ret.size(); ++i) ret[i] = i ^ (i >> 1);
  return ret;
}
}  // namespace tifa_libs::util
void solve() {
  tifa_libs::u32 n;
  tifa_libs::u64 k;
  std::cin >> n >> k;
  auto x = tifa_libs::util::gray_code(n, k).to_string().substr(64 - n);
  std::cout << x;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}
