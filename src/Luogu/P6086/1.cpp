#include <bits/stdc++.h>
using u32 = uint32_t;
using u64 = uint64_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs::graph {
inline vec<u32> prufer(vec<u32> const &fa) {
  u32 n = (u32)fa.size();
  vec<u32> deg(n + 1);
  for (u32 i = 1; i < n; ++i) ++deg[fa[i]];
  vec<u32> code(n);
  for (u32 i = 1, j = 1; i <= n - 2; ++i, ++j) {
    while (deg[j]) ++j;
    code[i] = fa[j];
    while (i <= n - 2 && !--deg[code[i]] && code[i] < j)
      code[i + 1] = fa[code[i]], ++i;
  }
  code.pop_back();
  return code;
}
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
inline vec<u32> prufer_inv(vec<u32> const &code) {
  u32 n = u32(code.size() + 1);
  vec<u32> deg(n + 1);
  for (u32 i = 1; i < n - 1; ++i) ++deg[code[i]];
  vec<u32> fa(n);
  for (u32 i = 1, j = 1; i < n; ++i, ++j) {
    while (deg[j]) ++j;
    fa[j] = code[i];
    while (i < n - 1 && !--deg[code[i]] && code[i] < j)
      fa[code[i]] = (i + 1 == n - 1 ? n : code[i + 1]), ++i;
  }
  return fa;
}
}  // namespace tifa_libs::graph
namespace tifa_libs {
template <class T>
using remove_cvref_t =
  typename std::remove_cv_t<typename std::remove_reference_t<T>>;
template <class T>
using is_iterable = typename std::conditional_t<
  std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().begin()),
                 typename remove_cvref_t<T>::iterator> &&
    std::is_same_v<decltype(std::declval<remove_cvref_t<T>>().end()),
                   typename remove_cvref_t<T>::iterator>,
  std::true_type,
  std::false_type>;
template <class T>
using is_container = typename std::conditional_t<
  is_iterable<T>::value &&
    !std::is_base_of_v<T, std::basic_string<typename T::value_type>>,
  std::true_type,
  std::false_type>;
}  // namespace tifa_libs
template <class T,
          std::enable_if_t<tifa_libs::is_container<T>::value> * = nullptr>
inline std::istream &operator>>(std::istream &is, T &x) {
  for (auto &i : x) is >> i;
  return is;
}
template <class T,
          std::enable_if_t<tifa_libs::is_container<T>::value> * = nullptr>
inline std::ostream &operator<<(std::ostream &os, const T &x) {
  if (x.begin() == x.end()) return os;
  auto it = x.begin();
  os << *it++;
  for (; it != x.end(); ++it) os << ' ' << *it;
  return os;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  u64 ans = 0;
  if (m == 1) {
    vec<u32> a(n);
    for (u32 i = 1; i < n; ++i) std::cin >> a[i];
    auto f = tifa_libs::graph::prufer(a);
    for (u64 i = 1; i < n - 1; ++i) ans ^= i * f[i];
  } else {
    vec<u32> a(n - 1);
    for (u32 i = 1; i < n - 1; ++i) std::cin >> a[i];
    auto f = tifa_libs::graph::prufer_inv(a);
    for (u64 i = 1; i < n; ++i) ans ^= i * f[i];
  }
  std::cout << ans << '\n';
  return 0;
}
