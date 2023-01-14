#include <bits/stdc++.h>
using i32 = int32_t;
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
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
std::istream &operator>>(std::istream &is, T &x) {
  for (auto &i : x) is >> i;
  return is;
}
template <class T,
          std::enable_if_t<tifa_libs::is_container<T>::value> * = nullptr>
std::ostream &operator<<(std::ostream &os, const T &x) {
  if (x.begin() == x.end()) return os;
  auto it = x.begin();
  os << *it++;
  for (; it != x.end(); ++it) os << ' ' << *it;
  return os;
}
namespace tifa_libs {
template <usz N, class Tp>
struct ndvec: public vec<ndvec<N - 1, Tp>> {
  static_assert(N, "N should be positive");
  using base_tp = ndvec<N - 1, Tp>;
  using base = vec<base_tp>;
  template <class T, typename... Ts>
  ndvec(T &&n, Ts &&...args): base(n, base_tp(args...)) {}
  constexpr usz dim() const { return N; }
  template <class T>
  void fill(T &&x) {
    for (auto &i : *this) i.fill(x);
  }
};
template <class Tp>
struct ndvec<1, Tp>: public vec<Tp> {
  using base = vec<Tp>;
  template <class T>
  ndvec(T &&n): base(n) {}
  constexpr usz dim() const { return 1; }
  template <class T>
  void fill(T &&x) {
    std::fill(this->begin(), this->end(), x);
  }
};
}  // namespace tifa_libs
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::ndvec<2, i32> nv(n, 0);
  i32 x;
  for (u32 i = 0, op, t; i < q; ++i) {
    std::cin >> op >> t;
    switch (op) {
      case 0:
        std::cin >> x;
        nv[t].push_back(x);
        break;
      case 1: std::cout << nv[t] << '\n'; break;
      case 2: nv[t].clear();
    }
  }
  return 0;
}
