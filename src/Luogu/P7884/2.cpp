#include <bits/stdc++.h>
#define CEXP constexpr
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
namespace tifa_libs::math {
CEXP i64 div_i64d(i64 a, i64 b) { return i64(f64(a) / f64(b)); }
CEXP u64 div_u64d(u64 a, u64 b) { return u64(f64(a) / f64(b)); }
CEXP i64 div_i64(i64 a, i64 b) {
  return a <= 1'000'000'000'000 ? div_i64d(a, b) : a / b;
}
CEXP u64 div_u64(u64 a, u64 b) {
  return a <= 1'000'000'000'000 ? div_u64d(a, b) : a / b;
}
}  // namespace tifa_libs::math
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
  if (n <= 1) return 0;
  if (n == 2) return 1;
  const u32 lim = isqrt(n);
  u32 vn = (lim + 1) / 2;
  vecu s(vn), r(vn);
  flt_(u32, cx, 0, vn) s[cx] = cx;
  flt_(u32, cx, 0, vn) r[cx] = cx * 2 + 1;
  vecuu l(vn);
  flt_(u32, cx, 0, vn) l[cx] = (n / (cx * 2 + 1) - 1) / 2;
  vecb vis(lim + 1);
  u32 cnt_p = 0;
  for (u32 p = 3; p <= lim; p += 2) {
    if (vis[p]) continue;
    u32 p2 = p * p;
    if ((u64)p2 * p2 > n) break;
    vis[p] = true;
    for (u32 cx = p2; cx <= lim; cx += p * 2) vis[cx] = true;
    u32 ns = 0;
    flt_(u32, cx, 0, vn) {
      u32 cur = r[cx];
      if (vis[cur]) continue;
      u64 d = (u64)cur * p;
      l[ns] = l[cx] -
              (d <= lim ? l[s[d / 2] - cnt_p] : s[(div_u64d(n, d) - 1) / 2]) +
              cnt_p,
      r[ns++] = cur;
    }
    vn = ns;
    for (u32 cx = (lim - 1) / 2, cy = ((lim / p) - 1) | 1; cy >= p; cy -= 2)
      for (u32 cur = s[cy / 2] - cnt_p, cz = cy * p / 2; cz <= cx; --cx)
        s[cx] -= cur;
    ++cnt_p;
  }
  l[0] += u64(vn + (cnt_p - 1) * 2) * (vn - 1) / 2;
  flt_(u32, cx, 1, vn) l[0] -= l[cx];
  flt_(u32, cx, 1, vn) {
    u32 q = r[cx];
    u64 m = n / q;
    u32 e = s[(m / q - 1) / 2] - cnt_p;
    if (e < cx + 1) break;
    u64 t = 0;
    fle_(u32, cy, cx + 1, e) t += s[(div_u64d(m, r[cy]) - 1) / 2];
    l[0] += t - u64(e - cx) * (cnt_p + cx - 1);
  }
  return l[0] + 1;
}
}  // namespace tifa_libs::math
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::pi_min25(n) << '\n';
  return 0;
}
