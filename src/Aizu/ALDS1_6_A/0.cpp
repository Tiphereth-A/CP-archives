#include <bits/stdc++.h>
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
namespace tifa_libs {
template <class T>
void rsort32(vec<T> &a) {
  static_assert(sizeof(T) == 4);
  static u32 _0[256], _1[256], _2[256], _3[256];
  usz n = a.size();
  vec<u32> b(n);
  u32 *a_ = a.data(), *b_ = b.data();
  for (u32 *_ = a_ + n, *i = a_; i < _; ++i) {
    ++_0[*i & 255];
    ++_1[*i >> 8 & 255];
    ++_2[*i >> 16 & 255];
    ++_3[*i >> 24 & 255];
  }
  for (u32 i = 1; i < 256; ++i) {
    _0[i] += _0[i - 1];
    _1[i] += _1[i - 1];
    _2[i] += _2[i - 1];
    _3[i] += _3[i - 1];
  }
  for (u32 *i = a_ + n; --i >= a_;) b_[--_0[*i & 255]] = *i;
  for (u32 *i = b_ + n; --i >= b_;) a_[--_1[*i >> 8 & 255]] = *i;
  for (u32 *i = a_ + n; --i >= a_;) b_[--_2[*i >> 16 & 255]] = *i;
  for (u32 *i = b_ + n; --i >= b_;) a_[--_3[*i >> 24 & 255]] = *i;
  if constexpr (std::is_signed_v<T>) {
    usz i = n;
    while (i && a[i - 1] < 0) --i;
    std::rotate(a_, a_ + i, a_ + n);
  }
}
}  // namespace tifa_libs
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
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<u32> a(n);
  std::cin >> a;
  tifa_libs::rsort32(a);
  std::cout << a << '\n';
  return 0;
}
