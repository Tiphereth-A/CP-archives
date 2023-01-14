#include <bits/stdc++.h>
#define CEXP constexpr
#define CR const &
#define fle_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; ++i)
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
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
using ptt = std::pair<T, T>;
template <class T>
using pt3 = std::tuple<T, T, T>;
template <class T>
using pt4 = std::tuple<T, T, T, T>;
template <class E>
using itl = std::initializer_list<E>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using v3ec = vec<vvec<T>>;
template <class T>
using vecpt = vec<ptt<T>>;
template <class T>
using vvecpt = vvec<ptt<T>>;
template <class T>
using ptvec = ptt<vec<T>>;
template <class T>
using ptvvec = ptt<vvec<T>>;
template <class T, usz ext = std::dynamic_extent>
using spn = std::span<T const, ext>;
#define mk_(V, A, T) using V##A = V<T>;
#define mk(A, T)                                                              \
  mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T) mk_(vec, A, T) mk_(vvec, A, T) \
    mk_(v3ec, A, T) mk_(vecpt, A, T) mk_(vvecpt, A, T) mk_(ptvec, A, T)       \
      mk_(ptvvec, A, T) mk_(spn, A, T) mk_(itl, A, T)
mk(b, bool) mk(i, i32) mk(u, u32) mk(ii, i64) mk(uu, u64);
#undef mk
#undef mk_
using namespace std::literals;
CEXP i8 operator""_i8(unsigned long long x) { return (i8)x; }
CEXP i16 operator""_i16(unsigned long long x) { return (i16)x; }
CEXP i32 operator""_i32(unsigned long long x) { return (i32)x; }
CEXP i64 operator""_i64(unsigned long long x) { return (i64)x; }
CEXP isz operator""_iz(unsigned long long x) { return (isz)x; }
CEXP u8 operator""_u8(unsigned long long x) { return (u8)x; }
CEXP u16 operator""_u16(unsigned long long x) { return (u16)x; }
CEXP u32 operator""_u32(unsigned long long x) { return (u32)x; }
CEXP u64 operator""_u64(unsigned long long x) { return (u64)x; }
CEXP usz operator""_uz(unsigned long long x) { return (usz)x; }
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
using std::numbers::pi_v;
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::opt {
template <class T>
class knapsack_mixed {
  vec<T> f;

public:
  CEXP explicit knapsack_mixed(u32 max_weight): f(max_weight + 1) {}
  CEXP void add(u32 weight, T value, u32 count = 1) {
    if (const u32 M = (u32)f.size() - 1; !count)
      fle_(u32, i, weight, M) f[i] = max(f[i], f[i - weight] + value);
    else flt_(u32, w, 0, weight) {
        vec<T> q1, q2;
        u32 l = 0;
        fle_(u32, i, 0, (M - w) / weight) {
          T &x = f[w + weight * i];
          while (l < q1.size() && (T)x - value * (T)i >= q2.back())
            q1.pop_back(), q2.pop_back();
          q1.push_back((T)i), q2.push_back((T)x - value * (T)i);
          while (l < q1.size() && q1[l] < T(i - count)) ++l;
          x = max(x, q2[l] + value * (T)i);
        }
      }
  }
  vec<T> CR result() const { return f; }
};
}  // namespace tifa_libs::opt
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 a0, b0, a1, b1, n;
  std::cin >> a0, std::cin.get(), std::cin >> b0 >> a1, std::cin.get(),
    std::cin >> b1 >> n;
  tifa_libs::opt::knapsack_mixed<i32> kn(u32(i32(a1 - a0) * 60 + i32(b1 - b0)));
  for (u32 i = 0; i < n; ++i) {
    u32 t, p;
    i32 c;
    std::cin >> t >> c >> p;
    kn.add(t, c, p);
  }
  std::cout << kn.result().back() << '\n';
}
