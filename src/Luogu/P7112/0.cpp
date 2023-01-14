#include <bits/stdc++.h>
using namespace std;
namespace ModInteger {
#define _TRAITS(expression, __...) \
  std::enable_if_t<expression, ##__> * = nullptr
template <typename Tp>
class mod_integer {
public:
  using self = mod_integer<Tp>;
  using data_t = Tp;
  using mod_t = Tp;

protected:
  data_t num;
  mod_t mod;

public:
  mod_integer(const data_t &_num, const mod_t &_mod) noexcept
    : num(_num), mod(_mod) {}
  template <typename Up, _TRAITS(std::is_convertible<Up, self &>::value)>
  mod_integer(Up &&rhs) noexcept
    : num(std::forward<self>(rhs).data()),
      mod(std::forward<self>(rhs).get_mod()) {}
  self &operator=(const data_t &num) noexcept {
    this->data() = num;
    return *this;
  }
  template <typename Up, _TRAITS(std::is_convertible<Up, self &>::value)>
  self &operator=(Up &&rhs) noexcept {
    this->data() = std::forward<self>(rhs).data();
    this->mod = std::forward<self>(rhs).get_mod();
    return *this;
  }
  operator data_t() { return this->data(); }
  constexpr self &no_check_mod() {
    this->num %= this->get_mod();
    return *this;
  }
  constexpr self &safe_mod() {
    if (this->no_check_mod().data() < 0) this->num += this->get_mod();
    return *this;
  }
  constexpr data_t &data() noexcept { return this->num; }
  constexpr data_t &data() const noexcept {
    return const_cast<self * const>(this)->num;
  }
  constexpr mod_t get_mod() const noexcept { return mod; }
  template <typename Unary>
  constexpr self &transform_unary_raw(Unary &&op) {
    this->data() = op(this->data());
    return *this;
  }
  template <typename Unary>
  constexpr self &transform_unary(Unary &&op) {
    return this->transform_unary_raw(std::move(op)).safe_mod();
  }
  template <typename Binary>
  constexpr self &transform_binary_raw(const self &rhs, Binary &&op) {
    this->data() = op(this->data(), rhs.data());
    return *this;
  }
  template <typename Binary>
  constexpr self &transform_binary(const self &rhs, Binary &&op) {
    return this->transform_binary_raw(rhs, std::move(op)).safe_mod();
  }
  self operator-() {
    return self(this->get_mod() - this->data(), this->get_mod());
  }
  self &operator+=(const self &rhs) {
    return this->transform_binary(rhs, std::plus<data_t>());
  }
  self &operator-=(const self &rhs) {
    return this->transform_binary(rhs, std::minus<data_t>());
  }
  self &operator*=(const self &rhs) {
    return this->transform_binary(rhs, std::multiplies<data_t>());
  }
  friend self operator+(const self &lhs, const self &rhs) {
    return self(lhs) += rhs;
  }
  friend self operator-(const self &lhs, const self &rhs) {
    return self(lhs) -= rhs;
  }
  friend self operator*(const self &lhs, const self &rhs) {
    return self(lhs) *= rhs;
  }
  friend bool operator==(const self &lhs, const self &rhs) {
    return lhs.data() == rhs.data();
  }
  friend std::istream &operator>>(std::istream &is, self &x) {
    is >> x.data();
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &x) {
    os << x.data();
    return os;
  }
};
#undef _TRAITS
}  // namespace ModInteger
using ModInteger::mod_integer;
namespace Matrix {
#define _TRAITS(expression, __...) \
  std::enable_if_t<expression, ##__> * = nullptr
#define _CONVERTIBLE(Tp, Up) std::is_convertible<Tp, Up>::value
template <class Tp, class Equal = std::equal_to<Tp>>
class matrix {
#define _for(i, begin, end, vals...) \
  for (std::size_t i = (begin), ##vals; i < (end); ++i)
#define _for_row(i, vals...) _for(i, 0, this->get_row(), ##vals)
#define _for_col(i, vals...) _for(i, 0, this->get_col(), ##vals)
#define _for_each(i, j) \
  _for_row(i)           \
    _for_col(j)
public:
  using self = matrix<Tp, Equal>;
  using data_t = Tp;

protected:
  const std::size_t row, col;
  std::vector<std::vector<Tp>> mat;
  Equal equ;

public:
  matrix(const std::size_t &_row,
         const std::size_t &_col,
         const Equal &_equal = Equal())
    : row(_row), col(_col), mat(_row, std::vector<data_t>(_col)), equ(_equal) {}
  template <typename Up, _TRAITS(_CONVERTIBLE(Up, data_t))>
  matrix(const std::size_t &_row,
         const std::size_t &_col,
         Up &&scalar,
         const Equal &_equal = Equal())
    : row(_row), col(_col), mat(_row, std::vector<data_t>(_col, scalar)),
      equ(_equal) {}
  template <typename Up, _TRAITS(_CONVERTIBLE(Up, self &))>
  matrix(Up &&rhs)
    : row(std::forward<self>(rhs).get_row()),
      col(std::forward<self>(rhs).get_col()), mat(row),
      equ(std::forward<self>(rhs).equ) {
    _for_row(i) this->mat[i] = std::forward<self>(rhs).mat[i];
  }
  template <typename Up, _TRAITS(_CONVERTIBLE(Up, self))>
  self &operator=(Up &&rhs) {
    _for_row(i) this->mat[i] = std::forward<self>(rhs).mat[i];
    return *this;
  }
  constexpr const std::size_t &get_row() const { return this->row; }
  constexpr const std::size_t &get_col() const { return this->col; }
  constexpr data_t &data(const size_t &r, const size_t &c) const {
    return const_cast<self * const>(this)->mat[r][c];
  }
  constexpr data_t &data(const size_t &r, const size_t &c) {
    return this->mat[r][c];
  }
  constexpr friend std::ptrdiff_t gauss_half(self &now) {
    bool neg = false;
    _for(i, 0, now.get_row(), now_row = 0) {
      now_row = i;
      _for(j, i, now.get_row())
        if (now.data(j, i) > 0) {
          now_row = j;
          break;
        }
      if (now.equ(now.data(now_row, i), data_t(0, now.data(0, 0).get_mod())))
        return 0;
      _for(j, now_row + 1, now.get_row())
        if (now.data(j, i) > 0 && now.data(j, i) < now.data(now_row, i))
          now_row = j;
      if (now_row != i) {
        std::swap(now.mat[now_row], now.mat[i]);
        neg ^= true;
      }
      _for(j, i + 1, now.get_row()) {
        if (now.data(j, i) > now.data(i, i)) {
          std::swap(now.mat[j], now.mat[i]);
          neg ^= true;
        }
        while (now.data(j, i)) {
          i64 _ = now.data(i, i) / now.data(j, i);
          _for(k, i, now.get_col())
            now.data(i, k) -=
              now.data(j, k) * data_t(_, now.data(0, 0).get_mod());
          std::swap(now.mat[j], now.mat[i]);
          neg ^= true;
        }
      }
    }
    return neg ? -static_cast<std::ptrdiff_t>(now.get_row()) :
                 static_cast<std::ptrdiff_t>(now.get_row());
  }
  constexpr data_t det() {
    std::ptrdiff_t rk = gauss_half(*this);
    if (rk == 0) return data_t(0, this->data(0, 0).get_mod());
    data_t ans(rk < 0 ? this->data(0, 0).get_mod() - 1 : 1,
               this->data(0, 0).get_mod());
    _for_row(i) ans *= this->data(i, i);
    return ans;
  }
  friend std::istream &operator>>(std::istream &is, self &x) {
    _for(i, 0, x.get_row())
      _for(j, 0, x.get_col()) is >> x.data(i, j);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &x) {
    _for(i, 0, x.get_row())
      _for(j, 0, x.get_col()) {
        os << x.data(i, j);
        if (i + 1 < x.get_row() || j + 1 < x.get_col())
          os << (j + 1 == x.get_col() ? '\n' : ' ');
      }
    return os;
  }
#undef _for
#undef _for_row
#undef _for_col
#undef _for_each
#undef _square_matrix_needed
};
#undef _TRAITS
#undef _CONVERTIBLE
}  // namespace Matrix
using Matrix::matrix;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  i64 n, p;
  cin >> n >> p;
  matrix<mod_integer<i64>> a(n, n, mod_integer<i64>(0, p));
  cin >> a;
  cout << a.det();
  return 0;
}
