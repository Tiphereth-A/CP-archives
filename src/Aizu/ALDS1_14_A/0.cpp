#include <bits/stdc++.h>
using i32 = int32_t;
using u32 = uint32_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::str {
vec<i32> kmp_nxt(std::string_view pattern) {
  i32 n = (i32)pattern.size();
  vec<i32> nxt((u32)n);
  i32 i, j;
  for (nxt[0] = j = -1, i = 1; i < n; nxt[i++] = j) {
    while (~j && pattern[j + 1] != pattern[i]) j = nxt[j];
    if (pattern[j + 1] == pattern[i]) ++j;
  }
  return nxt;
}
vec<u32> kmp(std::string_view pattern, std::string_view text) {
  vec<i32> nxt = kmp_nxt(pattern);
  vec<u32> ret;
  i32 n = (i32)pattern.size(), m = (i32)text.size();
  i32 i, j;
  for (j = -1, i = 0; i < m; ++i) {
    while (~j && pattern[j + 1] != text[i]) j = nxt[j];
    if (pattern[j + 1] == text[i]) ++j;
    if (j == n - 1) {
      ret.push_back(i - n + 1);
      j = nxt[j];
    }
  }
  return ret;
}
}  // namespace tifa_libs::str
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s, p;
  std::cin >> s >> p;
  auto _ = tifa_libs::str::kmp(p, s);
  for (auto i : _) std::cout << i << '\n';
  return 0;
}
