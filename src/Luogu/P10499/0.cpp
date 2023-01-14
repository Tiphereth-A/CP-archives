#include <bits/extc++.h>
#define CEXP constexpr
#define CEXPE constexpr explicit
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
template <class T, usz N>
using arr = std::array<T, N>;
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
namespace tifa_libs::math {
#define FOR1_(i, l, r) for (u32 i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_(i, row_l, row_r)                        \
  FOR1_(j, col_l, col_r)
template <class T>
class matrix {
  vvec<T> d;

public:
  CEXP matrix(u32 row, u32 col, cT_(T) v = T{}): d(row, vec<T>(col, v)) {
    assert(row > 0 && col > 0);
  }
  CEXPE matrix(cT_(vvec<T>) data): d(data) {
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
    assert(row_l < row_r && row_r <= row() && col_l < col_r && col_r <= col());
    T val;
    FOR2_(i, row_l, row_r, j, col_l, col_r)
    f(i, j, val = (*this)(i, j)), (*this)(i, j) = val;
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
    assert(row_l < row_r && row_r <= row() && col_l < col_r && col_r <= col());
    matrix ret(row_r - row_l, col_r - col_l);
    return ret.apply_range(0,
                           ret.row(),
                           0,
                           ret.col(),
                           [this, row_l, col_l](u32 i, u32 j, T &v) {
                             v = (*this)(i + row_l, j + col_l);
                           }),
           ret;
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
      return ret.apply_range(
               0, row(), 0, col(), [](u32, u32, T &v) { v = -v; }),
             ret;
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
  CEXP vec<T> lproj(spn<T> x) const {
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
namespace tifa_libs::math {
#define FOR1_(i, l, r) for (usz i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_(i, row_l, row_r)                        \
  FOR1_(j, col_l, col_r)
template <usz R, usz C = R>
using bitmat = arr<std::bitset<C>, R>;
template <usz R, usz C>
CEXP matrix<bool> bitmat2mat(cT_(bitmat<R, C>) bmat) {
  matrix<bool> ret(R, C);
  ret.apply([&bmat](u32 i, u32 j, auto &b) { b = bmat[i][j]; });
  return ret;
}
template <usz R, usz C = R>
CEXP bitmat<R, C> mat2bitmat(cT_(matrix<bool>) mat) {
  const u32 r = mat.row(), c = mat.col();
  assert(r <= R && c <= C);
  bitmat<R, C> ret;
  FOR2_(i, 0, r, j, 0, c)
  ret[i][j] = mat(i, j);
  return ret;
}
template <usz R, usz C>
std::istream &read_bitmat(std::istream &is, bitmat<R, C> &bmat, u32 r, u32 c) {
  assert(r <= R && c <= C);
  char ch;
  FOR2_(i, 0, r, j, 0, c)
  is >> ch, bmat[i][j] = ch & 1;
  return is;
}
template <usz R, usz C>
std::istream &
read_bitmat_trans(std::istream &is, bitmat<R, C> &bmat, u32 r, u32 c) {
  assert(r <= R && c <= C);
  char ch;
  FOR2_(i, 0, r, j, 0, c)
  is >> ch, bmat[j][i] = ch & 1;
  return is;
}
template <usz R, usz C>
std::ostream &print_bitmat(std::ostream &os, bitmat<R, C> &bmat, u32 r, u32 c) {
  assert(r <= R && c <= C);
  FOR2_(i, 0, r, j, 0, c)
  if (os << bmat[i][j]; j == c - 1 && i != r - 1) os << '\n';
  return os;
}
template <usz R, usz C>
std::istream &operator>>(std::istream &is, bitmat<R, C> &bmat) {
  return read_bitmat(is, bmat, R, C);
}
template <usz R, usz C>
std::ostream &operator<<(std::ostream &os, bitmat<R, C> CR bmat) {
  return print_bitmat(os, bmat, R, C);
}
#undef FOR1_
#undef FOR2_
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <usz R, usz C>
u32 ge_bmat(bitmat<R, C> &bmat, bool clear_u = true) {
  CEXP usz rk_max = min(R, C);
  u32 rk = 0;
  for (u32 i = 0, now_r = 0, j_ = i; i < R; ++i) {
    if (j_ = max(j_, i); !bmat[rk][i]) {
      now_r = rk;
      for (u32 j = now_r + 1; j < R; ++j)
        if (bmat[j][i]) now_r = j;
      if (now_r != rk) swap(bmat[now_r], bmat[rk]);
      else
        std::stable_sort(
          bmat.begin() + rk, bmat.end(), [](auto const &l, auto const &r) {
            return l._Find_first() < r._Find_first();
          });
      while (j_ < C && !bmat[rk][j_]) ++j_;
      if (j_ == C) break;
    }
    for (u32 j = clear_u ? 0 : rk + 1; j < R; ++j) {
      if (j == rk || !bmat[j][j_]) continue;
      bmat[j] ^= bmat[rk];
    }
    if (++rk >= rk_max) break;
  }
  return rk;
}
}  // namespace tifa_libs::math
int main() {
  u32 t;
  std::cin >> t;
  while (t--) {
    u32 n;
    std::cin >> n;
    tifa_libs::math::bitmat<32> bmat;
    {
      vecu a(n), b(n);
      for (auto &i : a) std::cin >> i;
      for (auto &i : b) std::cin >> i;
      flt_(u32, i, 0, n) bmat[i][n] = a[i] != b[i];
      flt_(u32, i, 0, n) bmat[i][i] = 1;
      u32 i, j;
      while ((std::cin >> i >> j), i || j) bmat[j - 1][i - 1] = 1;
    }
    tifa_libs::math::ge_bmat(bmat);
    u32 ans = 1;
    flt_(u32, i, 0, n) {
      if (auto _ = bmat[i].to_ullong(); _ == (1ull << n)) {
        std::cout << "Oh,it's impossible~!!\n";
        goto l1;
      } else if (!_) ans *= 2;
    }
    std::cout << ans << '\n';
  l1:;
  }
  return 0;
}
