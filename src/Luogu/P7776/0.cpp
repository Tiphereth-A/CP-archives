#include <bits/stdc++.h>
namespace tifa_libs {
using i32 = int32_t;
using u32 = uint32_t;
using u64 = uint64_t;
template <class T>
using vec = std::vector<T>;
}  // namespace tifa_libs
namespace tifa_libs::math {
#define FOR1_(i, l, r) for (size_t i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_(i, row_l, row_r)                        \
  FOR1_(j, col_l, col_r)
template <class T>
class matrix {
  vec<vec<T>> d;

public:
  matrix(size_t row, size_t col, T const &v = T{}): d(row, vec<T>(col, v)) {
    assert(row > 0 && col > 0);
  }
  constexpr size_t row() const { return d.size(); }
  constexpr size_t col() const { return d[0].size(); }
  constexpr vec<vec<T>> data() const { return d; }
  constexpr vec<vec<T>> &data() { return d; }
  constexpr typename vec<T>::reference operator()(size_t r, size_t c) {
    return d[r][c];
  }
  constexpr typename vec<T>::const_reference operator()(size_t r,
                                                        size_t c) const {
    return d[r][c];
  }
  template <class F>
  void apply(size_t row_l, size_t row_r, size_t col_l, size_t col_r, F f) {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    FOR2_(i, row_l, row_r, j, col_l, col_r)
    f(i, j, (*this)(i, j));
  }
  friend std::istream &operator>>(std::istream &is, matrix &mat) {
    size_t r_ = mat.row(), c_ = mat.col();
    FOR2_(i, 0, r_, j, 0, c_)
    is >> mat(i, j);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, matrix const &mat) {
    size_t r_ = mat.row(), c_ = mat.col();
    FOR2_(i, 0, r_ - 1, j, 0, c_)
    os << mat(i, j) << " \n"[j + 1 == c_];
    os << mat(r_ - 1, 0);
    FOR1_(j, 1, c_)
    os << ' ' << mat(r_ - 1, j);
    return os;
  }
  matrix submat(size_t row_l, size_t row_r, size_t col_l, size_t col_r) const {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    matrix ret(row_r - row_l, col_r - col_l);
    ret.apply(0,
              ret.row(),
              0,
              ret.col(),
              [this, row_l, row_r](size_t i, size_t j, T &v) {
                v = (*this)(i + row_l, j + row_r);
              });
    return ret;
  }
  constexpr void swap_row(size_t r1, size_t r2) {
    assert(r1 < row() && r2 < row());
    if (r1 == r2) return;
    std::swap(d[r1], d[r2]);
  }
  constexpr void swap_col(size_t c1, size_t c2) {
    assert(c1 < col() && c2 < col());
    if (c1 == c2) return;
    FOR1_(i, 0, row())
    std::swap((*this)(i, c1), (*this)(i, c2));
  }
  constexpr friend matrix operator+(matrix l, const T &v) { return l += v; }
  constexpr friend matrix operator+(const T &v, matrix l) { return l += v; }
  constexpr matrix &operator+=(const T &v) {
    apply(0,
          row(),
          0,
          col(),
          [&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) {
            val += v;
          });
    return *this;
  }
  constexpr friend matrix operator-(matrix l, const T &v) { return l -= v; }
  constexpr friend matrix operator-(const T &v, matrix l) { return l -= v; }
  constexpr matrix &operator-=(const T &v) {
    apply(0,
          row(),
          0,
          col(),
          [&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) {
            val -= v;
          });
    return *this;
  }
  constexpr friend matrix operator*(matrix l, const T &v) { return l *= v; }
  constexpr friend matrix operator*(const T &v, matrix l) { return l *= v; }
  constexpr matrix &operator*=(const T &v) {
    apply(0,
          row(),
          0,
          col(),
          [&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) {
            val *= v;
          });
    return *this;
  }
  constexpr friend matrix operator+(matrix l, const matrix &r) {
    return l += r;
  }
  constexpr matrix &operator+=(const matrix &r) {
    assert(row() == r.row() && col() == r.col());
    apply(
      0, row(), 0, col(), [&r](size_t i, size_t j, T &val) { val += r(i, j); });
    return *this;
  }
  constexpr friend matrix operator-(matrix l, const matrix &r) {
    return l -= r;
  }
  constexpr matrix &operator-=(const matrix &r) {
    assert(row() == r.row() && col() == r.col());
    apply(
      0, row(), 0, col(), [&r](size_t i, size_t j, T &val) { val -= r(i, j); });
    return *this;
  }
  constexpr friend matrix operator*(const matrix &l, const matrix &r) {
    assert(l.col() == r.row());
    matrix ret(l.row(), r.col());
    size_t i_ = l.row(), j_ = l.col(), k_ = r.col();
    FOR1_(i, 0, i_)
    FOR1_(j, 0, j_)
    FOR1_(k, 0, k_)
    ret(i, k) += l(i, j) * r(j, k);
    return ret;
  }
  constexpr matrix &operator*=(const matrix &r) { return *this = *this * r; }
};
#undef FOR1_
#undef FOR2_
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T, class Is0>
void uhb(matrix<T> &mat, Is0 is0) {
  size_t n = mat.row();
  assert(n == mat.col());
  if (n <= 2) return;
  for (size_t i = 0, p; i < n - 2; ++i) {
    p = i + 1;
    for (; p != n; ++p)
      if (!is0(mat(p, i))) break;
    if (p == n) continue;
    if (p != i + 1) {
      mat.swap_row(p, i + 1);
      mat.swap_col(p, i + 1);
    }
    for (size_t j = i + 2; j < n; ++j) {
      if (is0(mat(j, i))) continue;
      T _ = mat(j, i) / mat(i + 1, i);
      for (size_t k = i; k < n; ++k) mat(j, k) -= _ * mat(i + 1, k);
      for (size_t k = 0; k < n; ++k) mat(k, i + 1) += _ * mat(k, j);
    }
  }
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <class T, class Is0>
vec<T> charpoly(matrix<T> mat, Is0 is0) {
  size_t n = mat.row();
  assert(n == mat.col());
  uhb(mat, is0);
  vec<vec<T>> p(n + 1);
  p[0].resize(1);
  p[0][0] = 1;
  p[1].resize(2);
  p[1][0] = -mat(0, 0);
  p[1][1] = 1;
  for (size_t i = 2; i <= n; ++i) {
    vec<T> const &pc = p[i - 1];
    vec<T> &pi = p[i];
    pi.resize(p[i - 1].size() + 1);
    for (size_t j = 0, _ = pc.size(); j < _; ++j)
      pi[j] += pc[j] * -mat(i - 1, i - 1);
    for (size_t j = 0, _ = pc.size(); j < _; ++j) pi[j + 1] += pc[j];
    T t = 1;
    for (size_t j = 1; j < i; ++j) {
      T _ = (t *= mat(i - j, i - j - 1)) * mat(i - j - 1, i - 1);
      if (is0(_)) continue;
      for (size_t k = 0; k <= i - j - 1; ++k) pi[k] -= _ * p[i - j - 1][k];
    }
  }
  return p[n];
}
}  // namespace tifa_libs::math
namespace tifa_libs::math {
template <u32 MOD>
class mint_s30 {
  u32 v_{};
  static constexpr u32 get_r() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
  }
  static constexpr u32 redc(u64 x) {
    return (u32)((x + (u64)((u32)(x)*R) * MOD) >> 32);
  }
  static constexpr u32 norm(u32 x) {
    return x - (MOD & -((MOD - 1 - x) >> 31));
  }
  static constexpr u32 MOD2 = MOD << 1;
  static constexpr u32 R = get_r();
  static constexpr u32 R2 = -(u64)(MOD) % MOD;
  static constexpr i32 SMOD = (i32)(MOD);
  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);

public:
  static constexpr u32 mod() { return MOD; }
  static constexpr i32 smod() { return SMOD; }
  constexpr mint_s30() {}
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  constexpr mint_s30(T v): v_(redc((u64)(v % SMOD + SMOD) * R2)) {}
  constexpr u32 val() const { return norm(redc(v_)); }
  constexpr i32 sval() const { return (i32)norm(redc(v_)); }
  constexpr bool is_zero() const { return v_ == 0 || v_ == MOD; }
  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit constexpr operator T() const {
    return (T)(val());
  }
  constexpr mint_s30 operator-() const {
    mint_s30 res;
    res.v_ = (MOD2 & -(v_ != 0)) - v_;
    return res;
  }
  constexpr mint_s30 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return mint_s30(x1);
  }
  constexpr mint_s30 &operator+=(const mint_s30 &rhs) {
    v_ += rhs.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &operator-=(const mint_s30 &rhs) {
    v_ -= rhs.v_, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr mint_s30 &operator*=(const mint_s30 &rhs) {
    v_ = redc((u64)(v_)*rhs.v_);
    return *this;
  }
  constexpr mint_s30 &operator/=(const mint_s30 &rhs) {
    return operator*=(rhs.inv());
  }
  constexpr mint_s30 pow(u64 e) const {
    for (mint_s30 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  constexpr void swap(mint_s30 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend constexpr mint_s30 operator+(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) += rhs;
  }
  friend constexpr mint_s30 operator-(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) -= rhs;
  }
  friend constexpr mint_s30 operator*(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) *= rhs;
  }
  friend constexpr mint_s30 operator/(const mint_s30 &lhs,
                                      const mint_s30 &rhs) {
    return mint_s30(lhs) /= rhs;
  }
  friend constexpr bool operator==(const mint_s30 &lhs, const mint_s30 &rhs) {
    return norm(lhs.v_) == norm(rhs.v_);
  }
  friend constexpr bool operator!=(const mint_s30 &lhs, const mint_s30 &rhs) {
    return norm(lhs.v_) != norm(rhs.v_);
  }
  friend constexpr bool operator<(const mint_s30 &lhs, const mint_s30 &rhs) {
    return lhs.val() < rhs.val();
  }
  friend std::istream &operator>>(std::istream &is, mint_s30 &rhs) {
    i32 x;
    is >> x;
    rhs = mint_s30(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint_s30 &rhs) {
    return os << rhs.val();
  }
  friend constexpr u32 abs(mint_s30 const &x) { return x.val(); }
};
}  // namespace tifa_libs::math
using mint = tifa_libs::math::mint_s30<998244353>;
using mat = tifa_libs::math::matrix<mint>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  if (n == 0) {
    std::cout << "1\n";
    return 0;
  }
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x.val() == 0; };
  auto ans = tifa_libs::math::charpoly(a, is_0);
  for (size_t i = 0; i <= n; ++i) std::cout << ans[i] << " \n"[i == n];
  return 0;
}
