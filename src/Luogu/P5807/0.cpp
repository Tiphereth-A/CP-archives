#include <bits/stdc++.h>
#define CEXP constexpr
#define TPN typename
#define CR const &
#define cT_(...)                                            \
  std::conditional_t<sizeof(__VA_ARGS__) <= sizeof(size_t), \
                     __VA_ARGS__,                           \
                     __VA_ARGS__ CR>
#define flt_(T, i, l, r, ...) \
  for (T i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i < i##e; ++i)
#undef assert
#define assert(x) 42
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using isz = ptrdiff_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using usz = size_t;
template <class T>
using ptt = std::pair<T, T>;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
template <class T>
using vecpt = vec<ptt<T>>;
template <class T>
using vvecpt = vvec<ptt<T>>;
using vecu = vec<u32>;
using vvecu = vvec<u32>;
using vecb = vec<bool>;
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
template <class Mat, class Ge>
requires requires(Ge ge, Mat A, bool clear_u) {
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP auto det(Mat mat, Ge &&ge) {
  using T = TPN Mat::value_type;
  const u32 n = mat.row();
  assert(n == mat.col());
  const i64 rk_ = ge(mat, false);
  if CEXP (std::is_same_v<T, bool>) return abs(rk_) == n;
  else {
    if ((u32)abs(rk_) != n) return T{};
    T ret = mat(0, 0);
    flt_(u32, i, 1, n) ret *= mat(i, i);
    return T(rk_ < 0 ? -ret : ret);
  }
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
#define FOR1_(i, l, r) for (u32 i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_(i, row_l, row_r)                        \
  FOR1_(j, col_l, col_r)
template <class T>
class matrix {
  vvec<T> d;

public:
  using value_type = T;
  CEXP matrix(u32 row, u32 col, cT_(T) v = T{}): d(row, vec<T>(col, v)) {
    assert(row > 0 && col > 0);
  }
  explicit CEXP matrix(cT_(vvec<T>) data): d(data) {
    assert(data.size() > 0 && data[0].size() > 0);
  }
  CEXP u32 row() const { return (u32)d.size(); }
  CEXP u32 col() const { return (u32)d[0].size(); }
  CEXP vvec<T> CR data() const { return d; }
  CEXP vvec<T> &data() { return d; }
  CEXP TPN vec<T>::reference operator()(u32 r, u32 c) { return d[r][c]; }
  CEXP TPN vec<T>::const_reference operator()(u32 r, u32 c) const {
    return d[r][c];
  }
  template <class F>
  CEXP void apply(F &&f) {
    apply_range(0, row(), 0, col(), std::forward<F>(f));
  }
  template <class F>
  requires requires(F f, u32 i, u32 j, T &val) { f(i, j, val); }
  CEXP void apply_range(u32 row_l, u32 row_r, u32 col_l, u32 col_r, F &&f) {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    FOR2_(i, row_l, row_r, j, col_l, col_r)
    f(i, j, (*this)(i, j));
  }
  friend std::istream &operator>>(std::istream &is, matrix &mat) {
    const u32 r_ = mat.row(), c_ = mat.col();
    FOR2_(i, 0, r_, j, 0, c_)
    is >> mat(i, j);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, matrix CR mat) {
    const u32 r_ = mat.row(), c_ = mat.col();
    FOR2_(i, 0, r_ - 1, j, 0, c_)
    os << mat(i, j) << " \n"[j + 1 == c_];
    os << mat(r_ - 1, 0);
    FOR1_(j, 1, c_)
    os << ' ' << mat(r_ - 1, j);
    return os;
  }
  CEXP matrix submat(u32 row_l, u32 row_r, u32 col_l, u32 col_r) const {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    matrix ret(row_r - row_l, col_r - col_l);
    ret.apply_range(
      0, ret.row(), 0, ret.col(), [this, row_l, col_l](u32 i, u32 j, T &v) {
        v = (*this)(i + row_l, j + col_l);
      });
    return ret;
  }
  CEXP void swap_row(u32 r1, u32 r2) {
    assert(r1 < row() && r2 < row());
    if (r1 == r2) return;
    swap(d[r1], d[r2]);
  }
  CEXP void swap_col(u32 c1, u32 c2) {
    assert(c1 < col() && c2 < col());
    if (c1 == c2) return;
    FOR1_(i, 0, row())
    swap((*this)(i, c1), (*this)(i, c2));
  }
  CEXP matrix operator-() const {
    if CEXP (std::is_same_v<T, bool>) return *this;
    else {
      matrix ret = *this;
      ret.apply_range(0, row(), 0, col(), [](u32, u32, T &v) { v = -v; });
      return ret;
    }
  }
  friend CEXP matrix operator+(matrix l, cT_(T) v) { return l += v; }
  friend CEXP matrix operator+(cT_(T) v, matrix l) { return l += v; }
  CEXP matrix &operator+=(cT_(T) v) {
    if CEXP (std::is_same_v<T, bool>)
      apply_range(
        0, row(), 0, col(), [&v](u32, u32, auto &val) { val = val ^ v; });
    else apply_range(0, row(), 0, col(), [&v](u32, u32, T &val) { val += v; });
    return *this;
  }
  friend CEXP matrix operator-(matrix l, cT_(T) v) { return l -= v; }
  CEXP matrix &operator-=(cT_(T) v) {
    if CEXP (std::is_same_v<T, bool>)
      apply_range(
        0, row(), 0, col(), [&v](u32, u32, auto &val) { val = val ^ v; });
    else apply_range(0, row(), 0, col(), [&v](u32, u32, T &val) { val -= v; });
    return *this;
  }
  friend CEXP matrix operator*(matrix l, cT_(T) v) { return l *= v; }
  friend CEXP matrix operator*(cT_(T) v, matrix l) { return l *= v; }
  CEXP matrix &operator*=(cT_(T) v) {
    if CEXP (std::is_same_v<T, bool>) {
      if (!v)
        for (auto &i : d) i.clear(), i.resize(col());
      return *this;
    } else
      apply_range(0, row(), 0, col(), [&v](u32, u32, T &val) { val *= v; });
    return *this;
  }
  friend CEXP matrix operator+(matrix l, matrix CR r) { return l += r; }
  CEXP matrix &operator+=(matrix CR r) {
    assert(row() == r.row() && col() == r.col());
    if CEXP (std::is_same_v<T, bool>)
      apply_range(0, row(), 0, col(), [&r](u32 i, u32 j, auto &val) {
        val = val ^ r(i, j);
      });
    else
      apply_range(
        0, row(), 0, col(), [&r](u32 i, u32 j, T &val) { val += r(i, j); });
    return *this;
  }
  friend CEXP matrix operator-(matrix l, matrix CR r) { return l -= r; }
  CEXP matrix &operator-=(matrix CR r) {
    assert(row() == r.row() && col() == r.col());
    if CEXP (std::is_same_v<T, bool>)
      apply_range(0, row(), 0, col(), [&r](u32 i, u32 j, auto &val) {
        val = val ^ r(i, j);
      });
    else
      apply_range(
        0, row(), 0, col(), [&r](u32 i, u32 j, T &val) { val -= r(i, j); });
    return *this;
  }
  friend CEXP matrix operator*(matrix CR l, matrix CR r) {
    const u32 i_ = l.row(), j_ = l.col(), k_ = r.col();
    assert(j_ == r.row());
    matrix ret(i_, k_);
    FOR1_(i, 0, i_)
    FOR1_(j, 0, j_)
    FOR1_(k, 0, k_)
    if CEXP (std::is_same_v<T, bool>)
      ret(i, k) = ret(i, k) ^ (l(i, j) && r(j, k));
    else ret(i, k) += l(i, j) * r(j, k);
    return ret;
  }
  CEXP matrix &operator*=(matrix CR r) { return *this = *this * r; }
  CEXP vec<T> lproj(vec<T> CR x) const {
    const u32 r_ = row(), c_ = col();
    assert(r_ == x.size());
    vec<T> ret(c_);
    flt_(u32, i, 0, c_) if CEXP (std::is_same_v<T, bool>) ret[i] =
      std::transform_reduce(d[i].begin(),
                            d[i].end(),
                            x.begin(),
                            false,
                            std::bit_xor<bool>{},
                            std::bit_and<bool>{});
    else ret[i] =
      std::transform_reduce(d[i].begin(), d[i].end(), x.begin(), T{});
    return ret;
  }
  CEXP bool operator==(matrix CR r) const {
    if (row() != r.row() || col() != r.col()) return 0;
    FOR1_(i, 0, row())
    if (d[i] != r.d[i]) return 0;
    return 1;
  }
};
#undef FOR1_
#undef FOR2_
}  // namespace tifa_libs::math
namespace tifa_libs::graph {
template <class T, bool with_deg = false>
struct amat {
  using weight_type = T;
  using value_type = vvec<T>;
  value_type g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  explicit CEXP amat(u32 n, T const v = T{}): g(n, vec<T>(n, v)), cnt_arc(0) {
    flt_(u32, i, 0, n) g[i][i] = 0;
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void set_arc(u32 u, u32 v, cT_(T) w) {
    if (g[u][v] == w) return;
    if CEXP (with_deg)
      deg_in[v] += g[u][v] ? -!w : !!w, deg_out[u] += g[u][v] ? -!w : !!w;
    cnt_arc += (g[u][v] ? -!w : !!w), g[u][v] = w;
  }
};
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <bool inner, class T, bool with_deg, class Ge>
requires requires(Ge ge, math::matrix<T> A, bool clear_u) {
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP T kirchhoff(amat<T, with_deg> CR g, u32 r, Ge &&ge) {
  const u32 n = (u32)g.g.size();
  if (n <= 1) return n;
  math::matrix<T> mat(n - 1, n - 1);
  flt_(u32, i, 0, n) flt_(u32, j, 0, n) if (i != j) {
    auto _ = g.g[i][j];
    if (i != r && j != r) mat(i - (i > r), j - (j > r)) -= _;
    if CEXP (inner) {
      if (j != r) mat(j - (j > r), j - (j > r)) += _;
    } else if (i != r) mat(i - (i > r), i - (i > r)) += _;
  }
  return math::det(mat, ge);
}
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
template <bool with_deg = false>
struct alist {
  using weight_type = u32;
  using value_type = vvecu;
  value_type g;
  u32 cnt_arc;
  vecu deg_in, deg_out;
  explicit CEXP alist(u32 n = 0): g(n), cnt_arc(0) {
    if CEXP (with_deg) deg_in.resize(n), deg_out.resize(n);
  }
  CEXP void add_arc(u32 u, u32 v) {
    g[u].push_back(v), ++cnt_arc;
    if CEXP (with_deg) ++deg_in[v], ++deg_out[u];
  }
};
template <class G>
concept is_alist =
  (std::is_base_of_v<alist<true>, G> || std::is_base_of_v<alist<false>, G>);
}  // namespace tifa_libs::graph
namespace tifa_libs::graph {
namespace euler_trail_impl_ {
template <bool cyc>
CEXP std::optional<vecpt<u32>> run_(u32 n, u32 m, cT_(vvecpt<u32>) g, u32 s) {
  vec<vecpt<u32>::const_iterator> its(n);
  flt_(u32, i, 0, n) its[i] = g[i].begin();
  vec<i32> f(n);
  if CEXP (!cyc) ++f[s];
  vecb vis(m);
  vecpt<u32> ret, stk = {{s, -1_u32}};
  while (!stk.empty()) {
    auto [i, p] = stk.back();
    auto &it = its[i];
    if (it == g[i].end()) {
      ret.emplace_back(i, p), stk.pop_back();
      continue;
    }
    auto [j, e] = *(it++);
    if (!vis[e]) --f[i], ++f[j], stk.emplace_back(j, e), vis[e] = true;
  }
  if (ret.size() != m + 1) return {};
  for (i32 i : f)
    if (i < 0) return {};
  std::ranges::reverse(ret);
  return ret;
}
}  // namespace euler_trail_impl_
template <bool directed, bool cycle = false>
CEXP std::optional<vecpt<u32>> euler_trail(u32 n, cT_(vecpt<u32>) edges) {
  vvecpt<u32> g(n);
  vecu deg_in(0);
  if CEXP (directed) deg_in.resize(n);
  u32 e = 0;
  for (auto [u, v] : edges) {
    g[u].emplace_back(v, e);
    if CEXP (directed) ++deg_in[v];
    else g[v].emplace_back(u, e);
    ++e;
  }
  u32 s = 0;
  flt_(u32, i, 1, (u32)g.size()) if (!g[i].empty()) s = i;
  flt_(u32, i, 0, (u32)g.size()) if CEXP (directed) {
    if (deg_in[i] < g[i].size()) s = i;
  }
  else if (g[i].size() & 1) s = i;
  return euler_trail_impl_::run_<cycle>(n, (u32)edges.size(), g, s);
}
template <class G>
CEXP bool is_eulerian(G CR g) {
  const u32 n = (u32)g.g.size();
  assert(n == g.deg_in.size());
  vecb vis(n);
  u32 cnt = 0;
  auto f = [&](auto &&f, u32 x) -> void {
    for (auto v : g.g[x]) {
      ++cnt;
      if CEXP (is_alist<G>) {
        if (!vis[v]) vis[v] = 1, f(f, v);
      } else if (!vis[v.first]) vis[v.first] = 1, f(f, v.first);
    }
  };
  vis[0] = 1, f(f, 0);
  if (g.cnt_arc != cnt) return 0;
  flt_(u32, i, 0, n) if (g.deg_in[i] != g.deg_out[i]) return 0;
  return 1;
}
}  // namespace tifa_libs::graph
namespace tifa_libs::math::ge_impl_ {
template <class Mat>
CEXP bool swapr__(Mat &mat, u32 &r_, u32 r_pre_, u32 r_end) {
  r_ = r_pre_;
  for (u32 j = r_ + 1; j < r_end; ++j)
    if (mat.data()[r_] < mat.data()[j]) r_ = j;
  if (r_ != r_pre_) {
    mat.swap_row(r_, r_pre_);
    return true;
  }
  return false;
}
}  // namespace tifa_libs::math::ge_impl_
namespace tifa_libs::math {
template <class Mat, class Is0, class Div>
requires requires(Is0 is0, Div div, TPN Mat::value_type t) {
  { is0(t) } -> std::same_as<bool>;
  { div(t, t) } -> std::same_as<TPN Mat::value_type>;
}
CEXP i32 ge_euclid(Mat &mat, Is0 &&is0, Div &&div, bool clear_u = true) {
  using T = TPN Mat::value_type;
  const u32 r_ = mat.row(), c_ = mat.col(), rk_max = min(r_, c_);
  u32 rk = 0;
  bool neg = false;
  for (u32 i = 0, now_r = 0, j_ = i; i < mat.row(); ++i) {
    neg ^= ge_impl_::swapr__(mat, now_r, rk, mat.row());
    j_ = max(j_, i);
    while (j_ < c_ && is0(mat(rk, j_))) ++j_;
    if (j_ == c_) break;
    for (u32 j = rk + 1; j < mat.row(); ++j) {
      if (is0(mat(j, j_))) continue;
      while (true) {
        if (is0(mat(j, j_))) break;
        T _ = div(mat(rk, j_), mat(j, j_));
        flt_(u32, k, j_, c_) mat(rk, k) -= _ * mat(j, k);
        mat.swap_row(rk, j);
        neg ^= 1;
      }
    }
    if (clear_u && !is0(mat(rk, j_))) flt_(u32, j, 0, rk) {
        if (is0(mat(j, j_))) continue;
        if (T _ = div(mat(j, j_), mat(rk, j_)); !is0(_))
          flt_(u32, k, j_, c_) mat(j, k) -= _ * mat(rk, k);
      }
    if (++rk >= rk_max) break;
  }
  return neg ? -((i32)rk) : (i32)rk;
}
}  // namespace tifa_libs::math
namespace tifa_libs {
template <class T>
concept iterable_c = requires(T v) {
  { v.begin() } -> std::same_as<TPN T::iterator>;
  { v.end() } -> std::same_as<TPN T::iterator>;
};
template <class T>
concept container_c =
  iterable_c<T> &&
  !std::derived_from<T, std::basic_string<TPN T::value_type>> &&
  !std::derived_from<T, std::basic_string_view<TPN T::value_type>>;
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
CEXP bool is_arithm_v = std::is_arithmetic_v<T> || is_int_v<T>;
template <class T>
concept arithm_c = is_arithm_v<T>;
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
}  // namespace tifa_libs::math
namespace tifa_libs::math {
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
    while (!(x & 1)) {
      x /= 2;
      if (!((s | t) & 1)) s /= 2, t /= 2;
      else s = (s + (T)b) / 2, t = (t - (T)a) / 2;
    }
    while (!(y & 1)) {
      y /= 2;
      if (!((u | v) & 1)) u /= 2, v /= 2;
      else u = (u + (T)b) / 2, v = (v - (T)a) / 2;
    }
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
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <uint_c T>
CEXP ptt<T> inv_gcd(T n, T mod) {
  using U = to_sint_t<T>;
  auto [g, x] = exgcd<U, true>(U(n % mod), (U)mod);
  return {g, safe_mod(x, mod)};
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <uint_c T, uint_c U>
CEXP U inverse(T n, U mod) {
  auto [g, x] = inv_gcd(U(n % mod), mod);
  assert(g == 1);
  return x;
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class D, uint_c Rt>
class mint {
  CEXP D CR d() const { return static_cast<D CR>(*this); }
  CEXP D &d() { return static_cast<D &>(*this); }

protected:
  Rt v_{};

public:
  CEXP mint() {}
  template <int_c T>
  CEXP mint(T v): v_(D::mod_(v)) {}
  CEXP operator D() { return d(); }
  using raw_type = Rt;
  using sraw_type = to_sint_t<Rt>;
  static CEXP raw_type mod() { return D::mod_(); }
  static CEXP sraw_type smod() { return (sraw_type)D::mod_(); }
  CEXP raw_type val() const { return d().val_(); }
  CEXP sraw_type sval() const { return (sraw_type)d().val_(); }
  CEXP raw_type &data() { return d().data_(); }
  template <int_c T>
  explicit CEXP operator T() const {
    return (T)val();
  }
  CEXP mint &operator+=(mint CR r) { return d().adde_(r.d()); }
  CEXP mint &operator-=(mint CR r) { return d().sube_(r.d()); }
  CEXP mint &operator*=(mint CR r) { return d().mule_(r.d()); }
  CEXP mint &operator/=(mint CR r) { return *this = *this * r.inv(); }
  CEXP mint CR operator+() const { return *this; }
  CEXP mint operator-() const { return d().neg_(); }
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
    is >> _;
    x = mint(_);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, mint CR x) {
    return os << x.val();
  }
  friend CEXP mint abs(mint CR x) { return x.val(); }
};
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <u32 MOD>
class mint_s30: public mint<mint_s30<MOD>, u32> {
  using base = mint<mint_s30<MOD>, u32>;
  friend base;
  static CEXP u32 MOD2 = MOD << 1;
  static CEXP u32 R = []() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
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
  CEXP mint_s30() {}
  template <int_c T>
  CEXP mint_s30(T v) {
    this->v_ = mod_(v);
  }

private:
  using raw_t = TPN base::raw_type;
  template <sint_c T>
  static CEXP raw_t mod_(T v) {
    return reduce(u64(v % (i32)mod_() + (i32)mod_()) * R2);
  }
  template <uint_c T>
  static CEXP raw_t mod_(T v) {
    return reduce(u64(v % mod_()) * R2);
  }
  static CEXP raw_t mod_() { return MOD; }
  CEXP raw_t val_() const { return norm(reduce(this->v_)); }
  CEXP raw_t &data_() { return this->v_; }
  CEXP mint_s30 neg_() const {
    mint_s30 res;
    res.v_ = (MOD2 & -(this->v_ != 0)) - this->v_;
    return res;
  }
  CEXP mint_s30 &adde_(mint_s30 CR r) {
    this->v_ += r.v_ - MOD2, this->v_ += MOD2 & -(this->v_ >> 31);
    return *this;
  }
  CEXP mint_s30 &sube_(mint_s30 CR r) {
    this->v_ -= r.v_, this->v_ += MOD2 & -(this->v_ >> 31);
    return *this;
  }
  CEXP mint_s30 &mule_(mint_s30 CR r) {
    this->v_ = reduce(u64(this->v_) * r.v_);
    return *this;
  }
};
}  // namespace tifa_libs::math
using mint = tifa_libs::math::mint_s30<1'000'003>;
int main() {
  vec<mint> fact(200'005);
  fact[0] = 1;
  flt_(u32, i, 1, (u32)fact.size()) fact[i] = fact[i - 1] * i;
  u32 T;
  std::cin >> T;
  while (T--) {
    u32 n;
    std::cin >> n;
    tifa_libs::graph::alist<true> g(n);
    for (u32 i = 0, s; i < n; ++i) {
      std::cin >> s;
      for (u32 j = 0, x; j < s; ++j) (std::cin >> x), g.add_arc(i, x - 1);
    }
    if (!tifa_libs::graph::is_eulerian(g)) {
      std::cout << "0\n";
      continue;
    }
    vecb vis(n);
    auto f = [&](auto &&f, u32 x) -> void {
      for (auto v : g.g[x])
        if (!vis[v]) vis[v] = 1, f(f, v);
    };
    vis[0] = 1, f(f, 0);
    vecu ids(n, -1_u32), inv_ids;
    u32 cnt_ids = 0;
    flt_(u32, i, 0, n) if (vis[i]) ids[i] = cnt_ids++, inv_ids.push_back(i);
    tifa_libs::graph::amat<mint> mat(cnt_ids);
    flt_(u32, id, 0, cnt_ids) {
      auto &tos = g.g[inv_ids[id]];
      std::ranges::sort(tos);
      u32 cnt = 1, pre = tos[0];
      if (tos.empty()) continue;
      flt_(u32, j, 1, (u32)tos.size()) if (tos[j] != pre) {
        mat.set_arc(id, ids[pre], cnt), pre = tos[j], cnt = 1;
      }
      else ++cnt; mat.set_arc(id, ids[pre], cnt);
    }
    auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
    auto div = [](cT_(mint) x, cT_(mint) y) -> mint {
      return x.val() / y.val();
    };
    auto ge = [&](tifa_libs::math::matrix<mint> &A, bool clear_u) {
      return tifa_libs::math::ge_euclid(A, is_0, div, clear_u);
    };
    mint ans = tifa_libs::graph::kirchhoff<true>(mat, ids[0], ge) *
               fact[g.deg_out[inv_ids[0]]];
    flt_(u32, i, 1, cnt_ids) ans *= fact[g.deg_out[inv_ids[i]] - 1];
    std::cout << ans << '\n';
  }
  return 0;
}
