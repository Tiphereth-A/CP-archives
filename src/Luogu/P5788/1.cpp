#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define CR const &
#define NE noexcept
#define CNE const noexcept
#define cT_(...)                                                \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t) * 2, \
                     __VA_ARGS__,                               \
                     __VA_ARGS__ CR>
#undef assert
#define assert(x) 42
#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) NE { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using f128 = long double;
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) NE {
  eps_v<FP> = v;
}
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) |
                ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) |
                ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);
template <class T>
struct chash {
  CEXP static u64 C = u64(pi_v<f128> * 2e18) | 71;
  CEXP u64 operator()(T x) CNE {
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
using namespace std::ranges;
using namespace std::literals;
namespace tifa_libs {
template <class T>
CEXP T abs(T x) NE {
  return x < 0 ? -x : x;
}
}  // namespace tifa_libs
namespace tifa_libs::ds {
template <class T, class Comp = std::less<T>>
class mono_stack {
  static CEXP Comp compare{};
  vec<T> s;

public:
  CEXPE mono_stack() NE = default;
  CEXP void pop_greater(cT_(T) x) NE {
    s.erase(upper_bound(s, x, compare), s.end());
  }
  CEXP void push_nocheck(cT_(T) x) NE { s.push_back(x); }
  CEXP void push(cT_(T) x) NE { pop_greater(x), push_nocheck(x); }
  CEXP T CR top() CNE { return s.back(); }
  CEXP u32 size() CNE { return (u32)s.size(); }
};
}  // namespace tifa_libs::ds
vecu a;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu ans(n);
  a.resize(n);
  std::set<int> s;
  for (auto &i : a) std::cin >> i;
  auto f = [](u32 l, u32 r) { return a[l] >= a[r]; };
  tifa_libs::ds::mono_stack<u32, decltype(f)> stk;
  for (u32 i = n - 1; ~i; --i) {
    stk.pop_greater(i);
    ans[i] = stk.size() ? stk.top() + 1 : 0;
    stk.push_nocheck(i);
  }
  for (auto i : ans) std::cout << i << ' ';
}
