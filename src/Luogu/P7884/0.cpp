#include <bits/stdc++.h>
#define CEXP constexpr
#define CR const &
#define cT_(...)                                            \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t), \
                     __VA_ARGS__,                           \
                     __VA_ARGS__ CR>
#define fle_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; ++i)
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
using f64 = double;
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
namespace tifa_libs::bit {
template <class T>
CEXP T lowbit(T x) {
  return T(1) << std::countr_zero(x);
}
}  // namespace tifa_libs::bit
namespace tifa_libs::ds {
template <class T>
class fenwick {
  vec<T> a;

public:
  explicit CEXP fenwick(u32 sz): a(sz) { assert(sz > 1); }
  CEXP void add(u32 pos, cT_(T) x) {
    if (!pos) return;
    for (; pos < a.size(); pos += bit::lowbit(pos)) a[pos] += x;
  }
  CEXP void add(u32 l, u32 r, cT_(T) x) { add(l, x), add(r + 1, -x); }
  CEXP T sum(u32 pos) {
    T ret = 0;
    for (pos = min(pos, (u32)a.size() - 1); pos; pos -= bit::lowbit(pos))
      ret += a[pos];
    return ret;
  }
  CEXP T sum(u32 l, u32 r) { return sum(r) - sum(l - 1); }
  CEXP T kth_max(u32 k) {
    const u32 n = std::bit_ceil(a.size());
    u32 now = 0;
    T s{};
    while (n) {
      const u32 to = now | n;
      if (to >= a.size()) continue;
      if (T x = s + a[to]; x < k) now = to, s = x;
    }
    return now + 1;
  }
};
}  // namespace tifa_libs::ds
namespace tifa_libs::math {
CEXP u32 isqrt(u64 x) {
  if (!x) return 0;
  const int sh = 31 - i32(std::bit_width(x) - 1) / 2;
  u32 u = [](u64 x) {
    CEXP u8 TAB[192] = {
      128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
      143, 144, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155,
      156, 156, 157, 158, 159, 160, 160, 161, 162, 163, 164, 164, 165, 166, 167,
      167, 168, 169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178,
      179, 179, 180, 181, 181, 182, 183, 183, 184, 185, 186, 186, 187, 188, 188,
      189, 190, 190, 191, 192, 192, 193, 194, 194, 195, 196, 196, 197, 198, 198,
      199, 200, 200, 201, 201, 202, 203, 203, 204, 205, 205, 206, 206, 207, 208,
      208, 209, 210, 210, 211, 211, 212, 213, 213, 214, 214, 215, 216, 216, 217,
      217, 218, 219, 219, 220, 220, 221, 221, 222, 223, 223, 224, 224, 225, 225,
      226, 227, 227, 228, 228, 229, 229, 230, 230, 231, 232, 232, 233, 233, 234,
      234, 235, 235, 236, 237, 237, 238, 238, 239, 239, 240, 240, 241, 241, 242,
      242, 243, 243, 244, 244, 245, 246, 246, 247, 247, 248, 248, 249, 249, 250,
      250, 251, 251, 252, 252, 253, 253, 254, 254, 255, 255, 255};
    u32 u = TAB[(x >> 56) - 64];
    return u = (u << 7) + (u32)(x >> 41) / u, (u << 15) + (u32)((x >> 17) / u);
  }(x << 2 * sh);
  return u >>= sh, u -= (u64)u * u > x, u;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
CEXP u64 pi_min25(u64 n) {
  if (n < 2) return 0;
  u32 l2 = isqrt(n) + 1,
      lim = (u32)min(max<u64>({(u64)powl(n / log2l(n), .66), l2, 10000}), n);
  vecuu g(l2 + 1), w(l2 + 1);
  vec<f64> inv(l2 + 1);
  vecb e(lim + 1);
  ds::fenwick<u32> tr(lim + 1);
  auto add = [&](u32 x) { tr.add(x, e[x] = 1); };
  auto query = [&](u64 x) { return x - tr.sum((u32)x); };
  fle_(u32, i, 1, l2) w[i] = i - 1, inv[i] = 1. / i;
  u32 tot;
  for (tot = 1; 1_u64 * lim * tot < n; ++tot)
    g[tot] = u64((f64)n * inv[tot] + 1e-6 - 1);
  --tot, add(1);
  fle_(u32, i, 2, isqrt(n)) {
    if (e[i]) continue;
    u64 x0 = w[i - 1], t = n / i, r = 1_u64 * i * i;
    u32 tl = (u32)min(n / r, (u64)tot),
        tl2 = (u32)min((u64)tl, n / (1_u64 * l2 * i)), tl3 = min(tl2, tot / i);
    fle_(u32, j, 1, tl3) g[j] -= g[j * i] - x0;
    fle_(u32, j, tl3 + 1, tl2) g[j] -= query(u64((f64)t * inv[j] + 1e-6)) - x0;
    fle_(u32, j, tl2 + 1, tl) g[j] -= w[u32((f64)t * inv[j] + 1e-6)] - x0;
    for (u32 j = l2; j >= r; --j) w[j] -= w[u32(j * inv[i] + 1e-6)] - x0;
    if (1_u64 * i * i <= lim)
      for (u32 j = i * i; j <= lim; j += i)
        if (!e[j]) add(j);
  }
  return tot ? g[1] : query(n);
}
}  // namespace tifa_libs::math
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::pi_min25(n) << '\n';
  return 0;
}
