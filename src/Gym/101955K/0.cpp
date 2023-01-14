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
namespace josephus_impl_ {
constexpr u64 j1(u64 n, u64 k, u64 m) {
  if (m == 1) return (k - 1) % n;
  else return (j1(n - 1, k, m - 1) + k) % n;
}
constexpr u64 j2(u64 n, u64 k, u64 m) {
  if (k == 1) return m - 1;
  u64 n2 = n - m + 1, ret = j1(n2, k, 1);
  --m;
  while (m > 0) {
    u64 _ = (n2 - ret) / (k - 1);
    if (m <= _) return (ret + m * k) % (n2 + m);
    else {
      ret = (((ret + _ * k) % (n2 + _)) + k) % (n2 + _ + 1);
      n2 += _ + 1, m -= _ + 1;
    }
  }
  return ret;
}
}  // namespace josephus_impl_
constexpr u64 Josephus(u64 n, u64 k, u64 m) {
  assert(m && k && m <= n);
  return m < k * (u32)std::bit_width(n) ? josephus_impl_::j1(n, k, m) :
                                          josephus_impl_::j2(n, k, m);
}
}  // namespace tifa_libs::util
int main() {
  u32 t_;
  std::cin >> t_;
  for (u32 kase = 1; kase <= t_; ++kase) {
    u64 n, m, k;
    std::cin >> n >> m >> k;
    std::cout << "Case #" << kase << ": "
              << tifa_libs::util::Josephus(n, k, m) + 1 << '\n';
  }
  return 0;
}
