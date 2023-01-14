#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define CR const &
#define cT_(...)                                                \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t) * 2, \
                     __VA_ARGS__,                               \
                     __VA_ARGS__ CR>
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using f128 = long double;
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) {
  eps_v<FP> = v;
}
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) |
                ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) |
                ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);
template <class T>
struct chash {
  CEXP static u64 C = u64(pi_v<f128> * 2e18) | 71;
  CEXP u64 operator()(T x) const {
    return __builtin_bswap64(((u64)x ^ TIME) * C);
  }
};
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
using std::set, std::map;
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
namespace tifa_libs {
using std::min, std::max, std::swap;
template <class T>
CEXP T abs(T x) {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::ds {
template <class T, auto op, T (*e)()>
requires std::same_as<std::remove_cvref_t<decltype(op(T(), T()))>, T>
class st_array {
  vvec<T> st;

public:
  CEXPE st_array() {}
  CEXPE st_array(spn<T> a) { reset(a); }
  CEXP void reset(spn<T> a) {
    const u32 n = (u32)a.size(), lbn = (u32)std::bit_width(n);
    st = vvec<T>(lbn, vec<T>(n, e())), std::ranges::copy(a, st[0].begin());
    flt_(u32, j, 1, lbn) flt_(u32, i, 0, n) st[j][i] =
      op(st[j - 1][i], st[j - 1][(u32)max(0, i32(i - (1 << (j - 1))))]);
  }
  CEXP void push_back(cT_(T) x) {
    if (!height()) {
      st = vvec<T>{{x}};
      return;
    }
    const u32 n = size() + 1, lbn = (u32)std::bit_width(n);
    if (st[0].push_back(x); std::has_single_bit(n)) {
      st.emplace_back(n - 1, e());
      flt_(u32, i, 0, n - 1) st.back()[i] =
        op(st[lbn - 2][i], st[lbn - 2][(u32)max(0, i32(i - (1 << (lbn - 2))))]);
    }
    flt_(u32, j, 1, lbn) st[j].push_back(
      op(st[j - 1].back(), st[j - 1][n - 1 - (1 << (j - 1))]));
  }
  CEXP u32 height() const { return (u32)st.size(); }
  CEXP u32 size() const { return (u32)st[0].size(); }
  CEXP T query(u32 l = 0) const { return query(l, size()); }
  CEXP T query(u32 l, u32 r) const {
    if (r <= l) return e();
    const u32 k = (u32)(std::bit_width(r - l) - 1);
    return op(st[k][l + (1 << k) - 1], st[k][r - 1]);
  }
};
}  // namespace tifa_libs::ds
i64 f(i64 x, i64 y) { return tifa_libs::max(x, y); }
i64 e() { return 0; }
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 m, d;
  std::cin >> m >> d;
  tifa_libs::ds::st_array<i64, f, e> st;
  char op;
  i64 t = 0, u;
  for (u32 i = 1; i <= m; ++i) {
    std::cin >> op >> u;
    if (op == 'A') st.push_back((u % d + t + d) % d);
    else std::cout << (t = st.query(u32(st.size() - u))) << '\n';
  }
  return 0;
}
