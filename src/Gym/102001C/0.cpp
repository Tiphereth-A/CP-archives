#include <bits/stdc++.h>
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
#undef assert
#define assert(x) 42
using namespace std::literals;
constexpr i8 operator""_i8(unsigned long long x) { return (i8)x; }
constexpr i16 operator""_i16(unsigned long long x) { return (i16)x; }
constexpr i32 operator""_i32(unsigned long long x) { return (i32)x; }
constexpr i64 operator""_i64(unsigned long long x) { return (i64)x; }
constexpr isz operator""_iz(unsigned long long x) { return (isz)x; }
constexpr u8 operator""_u8(unsigned long long x) { return (u8)x; }
constexpr u16 operator""_u16(unsigned long long x) { return (u16)x; }
constexpr u32 operator""_u32(unsigned long long x) { return (u32)x; }
constexpr u64 operator""_u64(unsigned long long x) { return (u64)x; }
constexpr usz operator""_uz(unsigned long long x) { return (usz)x; }
namespace tifa_libs::util {
constexpr vec<u32> deBruijn(u32 n, u32 k, u32 maxsz = 0) {
  if (k == 1) return {0};
  if (!maxsz) {
    maxsz = 1;
    for (u32 i = 0; i < n; ++i) maxsz *= k;
  }
  vec<u32> ret, _(n + 1);
  auto f = [&](auto &&f, u32 t, u32 p) -> void {
    if (ret.size() >= maxsz) return;
    if (t > n) {
      if (!(n % p))
        for (u32 i = 1; i <= p; ++i) ret.push_back(_[i]);
      if (ret.size() >= maxsz) return;
    } else {
      _[t] = _[t - p];
      if (ret.size() >= maxsz) return;
      f(f, t + 1, p);
      while (++_[t] < k) {
        if (ret.size() >= maxsz) return;
        f(f, t + 1, t);
      }
    }
  };
  f(f, 1, 1);
  ret.resize(maxsz);
  return ret;
}
}  // namespace tifa_libs::util
namespace tifa_libs::rand {
template <class Distri>
class Gen {
  std::conditional_t<sizeof(typename Distri::result_type) <= 4,
                     std::mt19937,
                     std::mt19937_64>
    re;
  Distri dist;

public:
  using random_engine = decltype(re);
  using result_type = typename Distri::result_type;
  constexpr Gen(): re(std::random_device{}()), dist() {}
  constexpr Gen(result_type a, result_type b)
    : re(std::random_device{}()), dist(a, b) {}
  constexpr void set_range(result_type a, result_type b) {
    dist = Distri(a, b);
  }
  constexpr random_engine &rand_eng() { return re; }
  constexpr Distri &distrib() { return dist; }
  constexpr result_type operator()() { return dist(re); }
};
}  // namespace tifa_libs::rand
vec<u32> prandom(u32 m, u32 l) {
  tifa_libs::rand::Gen<std::uniform_int_distribution<u32>> gen(0, m - 1);
  vec<u32> ret(l);
  for (u32 i = 0; i < l; ++i) ret[i] = gen();
  return ret;
}
int main() {
  u32 n, m, k;
  std::cin >> n >> m >> k;
  vec<u32> a(m);
  for (auto &i : a) std::cin >> i;
  u32 l = n + k - 1;
  vec<u32> ans = n <= 20 ? tifa_libs::util::deBruijn(n, m, l) : prandom(m, l);
  for (u32 i = 0; i < l; ++i) std::cout << a[ans[i]];
  std::cout << '\n';
  return 0;
}
