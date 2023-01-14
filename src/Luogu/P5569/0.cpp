#include <bits/extc++.h>
#define CEXP constexpr
#define CR const &
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
template <class T>
using ptt = std::pair<T, T>;
template <class T>
struct edge_t {
  T w;
  u32 u, v;
  CEXP auto operator<=>(edge_t CR) const = default;
};
template <class T>
struct pt3 {
  T _0, _1, _2;
  CEXP auto operator<=>(pt3 CR) const = default;
};
template <class T>
struct pt4 {
  T _0, _1, _2, _3;
  CEXP auto operator<=>(pt4 CR) const = default;
};
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
#define mk(A, T)                                                          \
  mk_(edge_t, A, T) mk_(ptt, A, T) mk_(pt3, A, T) mk_(pt4, A, T)          \
    mk_(vec, A, T) mk_(vvec, A, T) mk_(v3ec, A, T) mk_(vecpt, A, T)       \
      mk_(vvecpt, A, T) mk_(ptvec, A, T) mk_(ptvvec, A, T) mk_(spn, A, T) \
        mk_(itl, A, T)
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
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
constexpr T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs {
template <class T, class F>
requires requires(F f, u32 m0, u32 m1, u32 r, u32 j, T a) {
  f(m0, m1, r, j, a);
}
void garsia_wachs(vec<T> &v, F &&f) {
  u32 n = (u32)v.size() - 2, cnt = n + 1, k, j;
  vecu idx(n);
  std::iota(idx.begin(), idx.end(), 0);
  while (n-- > 1) {
    for (k = 1; k <= n; ++k)
      if (v[k - 1] < v[k + 1]) break;
    T a = v[k] + v[k - 1];
    for (j = k - 1; ~j; --j)
      if (v[j] > v[k] + v[k - 1]) break;
    v.erase(v.begin() + k - 1), v.erase(v.begin() + k - 1),
      v.insert(v.begin() + j + 1, a);
    f(idx[k - 1], idx[k], ++cnt, j + 1, a);
    idx.erase(idx.begin() + k - 1), idx.erase(idx.begin() + k - 1),
      idx.insert(idx.begin() + j + 1, cnt);
  }
}
}  // namespace tifa_libs
void solve() {
  u32 n;
  std::cin >> n;
  vecu v(n + 2);
  fle_(u32, i, 1, n) std::cin >> v[i];
  v[0] = v[n + 1] = 0x3f3f3f3f;
  u32 ans = 0;
  tifa_libs::garsia_wachs(v, [&](u32, u32, u32, u32, u32 a) { ans += a; });
  std::cout << ans << '\n';
}
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  solve();
}
