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
using strn = std::string;
using strnv = std::string_view;
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
namespace tifa_libs::str {
CEXP vecu z_func(strnv s) {
  const u32 n = (u32)s.size();
  vecu z(n);
  for (u32 i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r && z[i - l] < r - i + 1) z[i] = z[i - l];
    else {
      if (i <= r) z[i] = r - i + 1;
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    }
    if (i + z[i] - 1 > r) r = i + z[l = i] - 1;
  }
  return z[0] = n, z;
}
}  // namespace tifa_libs::str
namespace tifa_libs::str {
CEXP vec<pt3u> run_zfunc(strnv s) {
  vec<pt3u> rs;
  auto rec = [&](auto &&rec, u32 l, u32 r) -> void {
    if (r - l <= 1) return;
    u32 m = (l + r) / 2;
    rec(rec, l, m), rec(rec, m, r);
    auto f = [&](bool rev) {
      strn t(s.substr(l, r - l));
      if (rev) std::ranges::reverse(t), m = l + r - m;
      const u32 len = r - l, mid = m - l;
      strn tl = t.substr(0, mid), tr = t.substr(mid, len - mid) + t;
      std::ranges::reverse(tl);
      auto zl = z_func(tl), zr = z_func(tr);
      zl.push_back(0);
      fle_(u32, k, 1, mid) {
        u32 li = m - k - zl[k], ri = m + min(r - m, zr[len - k]);
        if (rev) swap(li = l + r - li, ri = l + r - ri);
        if (ri - li < 2 * k) continue;
        if (li > 0 && s[li - 1] == s[li - 1 + k]) continue;
        if (ri < s.size() && s[ri] == s[ri - k]) continue;
        rs.emplace_back(li, ri, k);
      }
    };
    f(0), f(1);
  };
  rec(rec, 0, (u32)s.size());
  std::ranges::sort(rs);
  vec<pt3u> runs;
  flt_(u32, i, 0, (u32)rs.size()) {
    auto [l, r, t] = rs[i];
    if (i && l == get<0>(rs[i - 1]) && r == get<1>(rs[i - 1])) continue;
    runs.emplace_back(t, l, r);
  }
  return std::ranges::sort(runs), runs;
}
}  // namespace tifa_libs::str
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  auto ans = tifa_libs::str::run_zfunc(s);
  std::ranges::stable_sort(ans, [](auto CR l, auto CR r) {
    return std::get<1>(l) == std::get<1>(r) ? std::get<2>(l) < std::get<2>(r) :
                                              std::get<1>(l) < std::get<1>(r);
  });
  std::cout << ans.size() << '\n';
  for (auto [p, l, r] : ans) std::cout << l + 1 << ' ' << r << ' ' << p << '\n';
  return 0;
}
