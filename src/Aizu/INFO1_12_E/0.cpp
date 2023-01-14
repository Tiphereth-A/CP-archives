#include <bits/stdc++.h>
using i32 = int32_t;
using u32 = uint32_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
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
  u32 x, y, z, n;
  std::cin >> x >> y >> z >> n;
  tifa_libs::ndvec<3, i32> nv(51, 51, 51);
  for (u32 i = 0, a, b, c; i < n; ++i) {
    std::cin >> a >> b >> c;
    nv[a][b][c] = 1;
  }
  u32 q;
  std::cin >> q;
  for (u32 i = 0, a, b, c; i < q; ++i) {
    std::cin >> a >> b >> c;
    std::cout << nv[a][b][c] << '\n';
  }
  return 0;
}
