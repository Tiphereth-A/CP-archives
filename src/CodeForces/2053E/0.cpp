#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
#define TPN typename
#define CR const &
#undef assert
#define assert(x) 42
#define mk_(w, t) \
  using w = t;    \
  CEXP w operator""_##w(unsigned long long x) { return (w)x; }
mk_(i8, int8_t) mk_(u8, uint8_t) mk_(i16, int16_t) mk_(u16, uint16_t)
  mk_(i32, int32_t) mk_(u32, uint32_t) mk_(i64, int64_t) mk_(u64, uint64_t)
    mk_(isz, ptrdiff_t) mk_(usz, size_t);
#undef mk_
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = long double;
using strn = std::string;
using strnv = std::string_view;
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
template <class T>
concept iterable_c = requires(T v) {
  { v.begin() } -> std::same_as<TPN T::iterator>;
  { v.end() } -> std::same_as<TPN T::iterator>;
};
template <class T>
concept container_c =
  iterable_c<T> && !std::same_as<std::remove_cvref_t<T>, strn> &&
  !std::same_as<std::remove_cvref_t<T>, strnv>;
template <class, template <class...> class>
CEXP bool specialized_from_v = false;
template <template <class...> class T, class... Args>
CEXP bool specialized_from_v<T<Args...>, T> = true;
static_assert(specialized_from_v<vecu, std::vector>);
template <class T>
CEXP bool is_char_v =
  std::is_same_v<T, char> || std::is_same_v<T, signed char> ||
  std::is_same_v<T, unsigned char>;
template <class T>
concept char_c = is_char_v<T>;
template <class T>
CEXP bool is_s128_v =
  std::is_same_v<T, __int128_t> || std::is_same_v<T, __int128>;
template <class T>
concept s128_c = is_s128_v<T>;
template <class T>
CEXP bool is_u128_v =
  std::is_same_v<T, __uint128_t> || std::is_same_v<T, unsigned __int128>;
template <class T>
concept u128_c = is_u128_v<T>;
template <class T>
CEXP bool is_i128_v = is_s128_v<T> || is_u128_v<T>;
template <class T>
concept i128_c = is_u128_v<T>;
template <class T>
CEXP bool is_int_v = std::is_integral_v<T> || is_i128_v<T>;
template <class T>
concept int_c = is_int_v<T>;
template <class T>
CEXP bool is_sint_v = is_s128_v<T> || (is_int_v<T> && std::is_signed_v<T>);
template <class T>
concept sint_c = is_sint_v<T>;
template <class T>
CEXP bool is_uint_v = is_u128_v<T> || (is_int_v<T> && std::is_unsigned_v<T>);
template <class T>
concept uint_c = is_uint_v<T>;
template <class T>
CEXP bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
template <class T>
concept arithm_c = is_arithm_v<T>;
template <class T>
concept mint_c = requires(T x) {
  { x.mod() } -> uint_c;
  { x.val() } -> uint_c;
};
template <class T>
concept dft_c = requires(T x, vec<TPN T::data_t> v, u32 n) {
  { x.size() } -> std::same_as<u32>;
  x.bzr(n);
  x.dif(v, n);
  x.dit(v, n);
};
template <class T>
concept ntt_c = dft_c<T> && requires(T x) {
  T::max_size;
  T::G;
};
template <class T>
concept adjlist_c = requires(T g) {
  g[0].begin();
  g[0].end();
  g.build();
  g.size();
  g.cnt_arc;
  g.deg_in;
  g.deg_out;
};
template <class T> concept adjlistw_c = adjlist_c<T> && !std::is_void_v<TPN T::w_t> && (requires(T g) { g[0].begin()->first; g[0].begin()->second; } || requires(T g) { g[0].begin()->to; g[0].begin()->cost; });
template <class T>
concept tree_c = adjlist_c<T> && requires(T g) { g.root; };
template <class T>
concept treew_c = adjlistw_c<T> && requires(T g) { g.root; };
template <class P>
concept tp_ds_c = requires(P p) {
  p->ch;
  std::is_array_v<decltype(p->ch)>;
  std::rank_v<decltype(p->ch)> == 1;
};
template <class P>
concept tp2_ds_c =
  tp_ds_c<P> && std::extent_v<decltype(std::declval<P>()->ch)> == 2;
template <class T>
struct to_sint: std::make_signed<T> {};
template <>
struct to_sint<u128> {
  using type = u128;
};
template <>
struct to_sint<i128> {
  using type = u128;
};
template <class T>
using to_sint_t = TPN to_sint<T>::type;
template <class T>
struct to_uint: std::make_unsigned<T> {};
template <>
struct to_uint<u128> {
  using type = u128;
};
template <>
struct to_uint<i128> {
  using type = u128;
};
template <class T>
using to_uint_t = TPN to_uint<T>::type;
}  // namespace tifa_libs
namespace tifa_libs::math {
template <sint_c T>
CEXP T safe_mod(T x, to_uint_t<T> mod) {
  return ((x %= (T)mod) < 0 ? x + (T)mod : x);
}
template <uint_c U, bool only_x = false>
CEXP auto exgcd_b(U a, U b) {
  using T = to_sint_t<U>;
  if CEXP (only_x) {
    if (!a) return std::make_tuple(b, (T)0);
    if (!b) return std::make_tuple(a, (T)1);
  } else {
    if (!a) return std::make_tuple(b, (T)0, (T) !!b);
    if (!b) return std::make_tuple(a, (T)1, (T)0);
  }
  auto r = std::__countr_zero(a | b);
  a >>= r, b >>= r;
  T x = (T)a, y = (T)b, s = 1, t = 0, u = 0, v = 1;
  while (x) {
    while (!(x & 1))
      if (x /= 2; !((s | t) & 1)) s /= 2, t /= 2;
      else s = (s + (T)b) / 2, t = (t - (T)a) / 2;
    while (!(y & 1))
      if (y /= 2; !((u | v) & 1)) u /= 2, v /= 2;
      else u = (u + (T)b) / 2, v = (v - (T)a) / 2;
    if (x >= y) x -= y, s -= u, t -= v;
    else y -= x, u -= s, v -= t;
  }
  if (y > 1) a /= (U)y, b /= (U)y;
  if (a && (U)abs(v) >= a) {
    const T _ = v / (T)a;
    v -= _ * (T)a, u += _ * (T)b;
  }
  if (b && (U)abs(u) >= b) {
    const T _ = u / (T)b;
    u -= _ * (T)b, v += _ * (T)a;
  }
  if (T u_ = u + (T)b, v_ = v - (T)a; abs(u_) + abs(v_) <= abs(u) + abs(v))
    u = u_, v = v_;
  if (T u_ = u - (T)b, v_ = v + (T)a; abs(u_) + abs(v_) <= abs(u) + abs(v))
    u = u_, v = v_;
  if CEXP (only_x) return std::make_tuple(U(y << r), u);
  else return std::make_tuple(U(y << r), u, v);
}
template <sint_c T, bool only_x = false>
CEXP auto exgcd(T a, T b) {
  using U = to_uint_t<T>;
  if (auto [x, y] = std::minmax(a, b); x >= 0 && y <= T(U(-1) >> sizeof(U)))
    return exgcd_b<U, only_x>((U)a, (U)b);
  if CEXP (only_x) {
    T s = 1, u = 0;
    while (b) {
      T c = a / b;
      std::tie(s, u, a, b) = std::make_tuple(u, s - u * c, b, a - b * c);
    }
    return std::make_tuple((U)a, s);
  } else {
    T s = 1, t = 0, u = 0, v = 1;
    while (b) {
      T c = a / b;
      std::tie(s, t, u, v, a, b) =
        std::make_tuple(u, v, s - u * c, t - v * c, b, a - b * c);
    }
    return std::make_tuple((U)a, s, t);
  }
}
template <uint_c T>
CEXP ptt<T> inv_gcd(T n, T mod) {
  using U = to_sint_t<T>;
  auto [g, x] = exgcd<U, true>(U(n % mod), (U)mod);
  return {g, safe_mod(x, mod)};
}
template <uint_c T, uint_c U>
CEXP U inverse(T n, U mod) {
  auto [g, x] = inv_gcd(U(n % mod), mod);
  assert(g == 1);
  return x;
}
template <template <u64 Arg> class D, u64 Arg = 998244353>
struct mint: D<Arg> {
  using base_t = D<Arg>;
  CEXP mint(): base_t() {}
  CEXP mint(int_c auto v): base_t(v) {}
  using raw_t = base_t::raw_t;
  using sraw_t = to_sint_t<raw_t>;
  static CEXP raw_t mod() { return base_t::mod(); }
  static CEXP sraw_t smod() { return (sraw_t)base_t::mod(); }
  CEXP raw_t val() const { return base_t::val(); }
  CEXP sraw_t sval() const { return (sraw_t)base_t::val(); }
  CEXP raw_t &data() { return base_t::data(); }
  template <int_c T>
  CEXPE operator T() const {
    return (T)val();
  }
  CEXP mint &operator+=(mint CR r) { return mint::add(r), *this; }
  CEXP mint &operator-=(mint CR r) { return mint::sub(r), *this; }
  CEXP mint &operator*=(mint CR r) { return mint::mul(r), *this; }
  CEXP mint &operator/=(mint CR r) { return *this = *this * r.inv(); }
  CEXP mint CR operator+() const { return *this; }
  CEXP mint operator-() const { return base_t::template neg<mint>(); }
  CEXP mint inv() const { return inverse(val(), mod()); }
  friend CEXP mint operator+(mint l, mint CR r) { return l += r; }
  friend CEXP mint operator-(mint l, mint CR r) { return l -= r; }
  friend CEXP mint operator*(mint l, mint CR r) { return l *= r; }
  friend CEXP mint operator/(mint l, mint CR r) { return l /= r; }
  friend CEXP bool operator==(mint CR l, mint CR r) {
    return l.val() == r.val();
  }
  friend CEXP auto operator<=>(mint CR l, mint CR r) {
    return l.sval() - r.sval();
  }
  friend std::istream &operator>>(std::istream &is, mint &x) {
    i64 _;
    return is >> _, x = mint(_), is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint CR x) {
    return os << x.val();
  }
  friend CEXP auto abs(mint CR x) { return x.val(); }
};
template <u64 MOD_>
class mint_s30 {
  static_assert(MOD_ <= UINT32_MAX);
  static CEXP u32 MOD = (u32)MOD_;
  static CEXP u32 MOD2 = MOD << 1;
  static CEXP u32 R = []() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    return iv *= t - MOD * iv, iv *= t - MOD * iv, iv * (MOD * iv - t);
  }();
  static CEXP u32 R2 = -(u64)(MOD) % MOD;
  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);
  static CEXP u32 reduce(u64 x) {
    return u32((x + u64((u32)x * R) * MOD) >> 32);
  }
  static CEXP u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }

public:
  static CEXP bool FIXED_MOD = true;

protected:
  using raw_t = u32;
  raw_t v_;
  CEXP mint_s30(): v_{} {}
  CEXP mint_s30(int_c auto v): v_{mod(v)} {}
  static CEXP raw_t mod(sint_c auto v) {
    return reduce(u64(v % (i32)mod() + (i32)mod()) * R2);
  }
  static CEXP raw_t mod(uint_c auto v) { return reduce(u64(v % mod()) * R2); }
  static CEXP raw_t mod() { return MOD; }
  CEXP raw_t val() const { return norm(reduce(v_)); }
  CEXP raw_t &data() { return v_; }
  template <class mint>
  CEXP auto neg() const {
    mint res;
    return res.v_ = (MOD2 & -(v_ != 0)) - v_, res;
  }
  CEXP void add(mint_s30 CR r) { v_ += r.v_ - MOD2, v_ += MOD2 & -(v_ >> 31); }
  CEXP void sub(mint_s30 CR r) { v_ -= r.v_, v_ += MOD2 & -(v_ >> 31); }
  CEXP void mul(mint_s30 CR r) { v_ = reduce(u64(v_) * r.v_); }
};
}  // namespace tifa_libs::math
template <class T>
concept iterable = requires(T v) {
  { v.begin() } -> std::same_as<typename T::iterator>;
  { v.end() } -> std::same_as<typename T::iterator>;
};
template <class T>
concept container =
  iterable<T> &&
  !std::derived_from<T, std::basic_string<typename T::value_type>>;
#define fors_(i, l, r, s, ...) \
  for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
  return is >> p.first >> p.second;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, std::pair<T, U> const &p) {
  return os << p.first << ' ' << p.second;
}
template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  return std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p), is;
}
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &p) {
  return std::apply(
           [&, n = 0](Ts const &...targs) mutable {
             ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
           },
           p),
         os;
}
template <container T>
std::istream &operator>>(std::istream &is, T &x) {
  for (auto &i : x) is >> i;
  return is;
}
template <container T>
std::ostream &operator<<(std::ostream &os, T const &x) {
  if (x.begin() == x.end()) return os;
  for (auto nxt = x.begin(), it = nxt++; nxt != x.end(); ++it, ++nxt)
    os << *it << ' ';
  os << *x.rbegin();
  return os;
}
#define dbg(...) 42
constexpr std::pair<int, int> DIR4[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
constexpr std::pair<int, int> DIR8[8] = {
  {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
using namespace std;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  vector<vector<int>> g(n + 1);
  for_(i, 2, n, x, y) {
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  if (n <= 2) {
    cout << "0\n";
    return;
  }
  i64 ans = 0;
  vector<int> d(n + 1);
  auto f = [&](auto &&f, int now, int fa) -> int {
    int mn = INT_MAX;
    for (auto &&to : g[now])
      if (to != fa) mn = min(mn, f(f, to, now));
    if (mn == INT_MAX) mn = -1;
    return d[now] = mn + 1;
  };
  int r = 1;
  for_(i, 2, n)
    if (g[i].size() > 1) {
      r = i;
      break;
    }
  f(f, r, 0);
  ans = count(d.begin() + 1, d.end(), 0);
  ans *= (n - ans);
  vector<int> d_1(n + 1), d_g2(n + 1);
  auto f2 = [&](auto &&f, int now, int fa) -> void {
    d_g2[now] = d[now] > 1;
    for (auto &&to : g[now])
      if (to != fa) {
        f(f, to, now);
        d_g2[now] += d_g2[to];
      }
  };
  for_(now, 1, n)
    for (auto &&to : g[now]) d_1[now] += !!d[to];
  f2(f2, r, 0);
  if (!all_of(d_g2.begin(), d_g2.end(), [](int x) { return !x; })) {
    auto mov = [&](int now, int fa) -> void {
      d_g2[fa] -= d_g2[now];
      d_g2[now] += d_g2[fa];
    };
    auto f3 = [&](auto &&f, int now, int fa) -> void {
      if (g[now].size() > 2 && d_1[now] < g[now].size()) {
        i64 c1 = d_1[now], c2 = d_g2[now] - (d[now] > 1);
        ans += max<i64>(0, c1 - 1) * c2;
      }
      for (auto &&to : g[now])
        if (to != fa) {
          mov(to, now);
          f(f, to, now);
          mov(now, to);
        }
    };
    f3(f3, r, 0);
  }
  cout << ans << '\n';
}
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) dbg(i_), solve(i_);
  return 0;
}
