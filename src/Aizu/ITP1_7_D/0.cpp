#include <bits/stdc++.h>
using u32 = uint32_t;
using u64 = uint64_t;
using usz = size_t;
template <class T>
using vec = std::vector<T>;
template <class T>
using vvec = vec<vec<T>>;
#undef assert
#define assert(x) 42
namespace tifa_libs::math {
#define FOR1_(i, l, r) for (usz i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_(i, row_l, row_r)                        \
  FOR1_(j, col_l, col_r)
template <class T>
class matrix {
  vvec<T> d;

public:
  matrix(usz row, usz col, T const &v = T{}): d(row, vec<T>(col, v)) {
    assert(row > 0 && col > 0);
  }
  explicit matrix(vvec<T> const &data): d(data) {
    assert(data.size() > 0 && data[0].size > 0);
  }
  constexpr usz row() const { return d.size(); }
  constexpr usz col() const { return d[0].size(); }
  constexpr vvec<T> data() const { return d; }
  constexpr vvec<T> &data() { return d; }
  constexpr typename vec<T>::reference operator()(usz r, usz c) {
    return d[r][c];
  }
  constexpr typename vec<T>::const_reference operator()(usz r, usz c) const {
    return d[r][c];
  }
  template <class F>
  void apply(F f) {
    apply_range(0, row(), 0, col(), f);
  }
  template <class F>
  void apply_range(usz row_l, usz row_r, usz col_l, usz col_r, F f) {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    FOR2_(i, row_l, row_r, j, col_l, col_r)
    f(i, j, (*this)(i, j));
  }
  friend std::istream &operator>>(std::istream &is, matrix &mat) {
    usz r_ = mat.row(), c_ = mat.col();
    FOR2_(i, 0, r_, j, 0, c_)
    is >> mat(i, j);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, matrix const &mat) {
    usz r_ = mat.row(), c_ = mat.col();
    FOR2_(i, 0, r_ - 1, j, 0, c_)
    os << mat(i, j) << " \n"[j + 1 == c_];
    os << mat(r_ - 1, 0);
    FOR1_(j, 1, c_)
    os << ' ' << mat(r_ - 1, j);
    return os;
  }
  matrix submat(usz row_l, usz row_r, usz col_l, usz col_r) const {
    assert(row_l < row_r && row_r <= row());
    assert(col_l < col_r && col_r <= col());
    matrix ret(row_r - row_l, col_r - col_l);
    ret.apply_range(
      0, ret.row(), 0, ret.col(), [this, row_l, row_r](usz i, usz j, T &v) {
        v = (*this)(i + row_l, j + row_r);
      });
    return ret;
  }
  constexpr void swap_row(usz r1, usz r2) {
    assert(r1 < row() && r2 < row());
    if (r1 == r2) return;
    std::swap(d[r1], d[r2]);
  }
  constexpr void swap_col(usz c1, usz c2) {
    assert(c1 < col() && c2 < col());
    if (c1 == c2) return;
    FOR1_(i, 0, row())
    std::swap((*this)(i, c1), (*this)(i, c2));
  }
  constexpr matrix operator-() const {
    matrix ret = *this;
    ret.apply_range(0, row(), 0, col(), [](usz, usz, T &v) { v = -v; });
    return ret;
  }
  constexpr friend matrix operator+(matrix l, const T &v) { return l += v; }
  constexpr friend matrix operator+(const T &v, matrix l) { return l += v; }
  constexpr matrix &operator+=(const T &v) {
    apply_range(0, row(), 0, col(), [&v](usz, usz, T &val) { val += v; });
    return *this;
  }
  constexpr friend matrix operator-(matrix l, const T &v) { return l -= v; }
  constexpr friend matrix operator-(const T &v, matrix l) { return l -= v; }
  constexpr matrix &operator-=(const T &v) {
    apply_range(0, row(), 0, col(), [&v](usz, usz, T &val) { val -= v; });
    return *this;
  }
  constexpr friend matrix operator*(matrix l, const T &v) { return l *= v; }
  constexpr friend matrix operator*(const T &v, matrix l) { return l *= v; }
  constexpr matrix &operator*=(const T &v) {
    apply_range(0, row(), 0, col(), [&v](usz, usz, T &val) { val *= v; });
    return *this;
  }
  constexpr friend matrix operator+(matrix l, const matrix &r) {
    return l += r;
  }
  constexpr matrix &operator+=(const matrix &r) {
    assert(row() == r.row() && col() == r.col());
    apply_range(
      0, row(), 0, col(), [&r](usz i, usz j, T &val) { val += r(i, j); });
    return *this;
  }
  constexpr friend matrix operator-(matrix l, const matrix &r) {
    return l -= r;
  }
  constexpr matrix &operator-=(const matrix &r) {
    assert(row() == r.row() && col() == r.col());
    apply_range(
      0, row(), 0, col(), [&r](usz i, usz j, T &val) { val -= r(i, j); });
    return *this;
  }
  constexpr friend matrix operator*(const matrix &l, const matrix &r) {
    usz i_ = l.row(), j_ = l.col(), k_ = r.col();
    assert(j_ == r.row());
    matrix ret(i_, k_);
    FOR1_(i, 0, i_)
    FOR1_(j, 0, j_)
    FOR1_(k, 0, k_)
    ret(i, k) += l(i, j) * r(j, k);
    return ret;
  }
  constexpr matrix &operator*=(const matrix &r) { return *this = *this * r; }
  vec<T> lproj(vec<T> const &x) const {
    usz r_ = row(), c_ = col();
    assert(r_ == x.size());
    vec<T> ret(c_);
    for (usz i = 0; i < c_; ++i)
      ret[i] = std::transform_reduce(d[i].begin(), d[i].end(), x.begin(), T{});
    return ret;
  }
};
#undef FOR1_
#undef FOR2_
}  // namespace tifa_libs::math
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, l;
  std::cin >> n >> m >> l;
  tifa_libs::math::matrix<u64> a(n, m), b(m, l);
  std::cin >> a >> b;
  std::cout << a * b << '\n';
  return 0;
}
