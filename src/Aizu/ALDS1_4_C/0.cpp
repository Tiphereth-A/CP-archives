#include <bits/stdc++.h>
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;
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
}  // namespace tifa_libs
namespace tifa_libs {
class hash_splitmix64 {
  static inline u64 seed = 114514;
  static constexpr u64 splitmix64(u64 x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static constexpr usz append(usz x, usz y) {
    return x ^ (y >> 1) ^ ((y & 1) << (sizeof(usz) * 8 - 1));
  }

public:
  explicit hash_splitmix64() { set_seed(); }
  static void set_seed() {
    seed = (u64)std::chrono::steady_clock::now().time_since_epoch().count();
  }
  static constexpr void set_seed(u64 s) { seed = s; }
  usz operator()(u64 x) const { return splitmix64(x + seed); }
  template <class T, class U>
  usz operator()(std::pair<T, U> const &p) const {
    return append((*this)(p.first), (*this)(p.second));
  }
  template <class... Ts>
  usz operator()(std::tuple<Ts...> const &tp) const {
    usz ret = 0;
    std::apply(
      [&](Ts const &...targs) { ((ret = append(ret, (*this)(targs))), ...); },
      tp);
    return ret;
  }
  template <class T, std::enable_if_t<is_iterable<T>::value> * = nullptr>
  usz operator()(T const &tp) const {
    usz ret = 0;
    for (auto &&i : tp) ret = append(ret, (*this)(i));
    return ret;
  }
};
template <class T>
using hset = std::unordered_set<T, hash_splitmix64>;
}  // namespace tifa_libs
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  tifa_libs::hset<u64> dict;
  for (usz i = 0; i < n; ++i) {
    std::string s, t;
    std::cin >> s >> t;
    u64 x = 0;
    for (char c : t) switch (c) {
        case 'A': ++x;
        case 'C': ++x;
        case 'G': ++x;
        default: (++x) *= 5;
      }
    if (s[0] == 'i') dict.insert(x);
    else std::cout << (dict.count(x) ? "yes\n" : "no\n");
  }
  return 0;
}
