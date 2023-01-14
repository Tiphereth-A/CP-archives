#include <bits/stdc++.h>
namespace ModInteger {
#define _TRAITS(expression, __...) \
  std::enable_if_t<expression, ##__> * = nullptr
#define _TO_CONST(value) (*(decltype(value) * const)(&(value)))
template <typename Tp,
          Tp mod,
          _TRAITS(std::is_integral<Tp>::value && (1 <= mod))>
class mod_integer {
public:
  using self = mod_integer<Tp, mod>;
  using data_t = Tp;
  using mod_t = Tp;
  using common_t = std::common_type_t<data_t, mod_t>;
  using signed_common_t = std::make_signed_t<common_t>;

protected:
  data_t num;

private:
  constexpr common_t gcd(common_t m, common_t n) const {
    while (n != 0) {
      common_t t = m % n;
      m = n;
      n = t;
    }
    return m;
  }

public:
  mod_integer() noexcept: mod_integer(0) {}
  template <typename Up,
            _TRAITS(std::is_integral<Up>::value
                      &&std::is_convertible<Up, data_t>::value)>
  mod_integer(const Up &_num) noexcept: num(static_cast<data_t>(_num)) {
    this->safe_mod();
  }
  template <typename Up, _TRAITS(std::is_convertible<Up, self &>::value)>
  mod_integer(Up &&rhs) noexcept: num(std::forward<self>(rhs).data()) {}
  template <typename Up,
            _TRAITS(std::is_integral<Up>::value
                      &&std::is_convertible<Up, data_t>::value)>
  self &operator=(const Up &_num) noexcept {
    this->data() = static_cast<data_t>(_num);
    return this->safe_mod();
  }
  template <typename Up, _TRAITS(std::is_convertible<Up, self &>::value)>
  self &operator=(Up &&rhs) noexcept {
    this->data() = std::forward<self>(rhs).data();
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
  constexpr self &
  transform_unary_raw(std::function<data_t(const data_t &)> &&op) {
    this->data() = op(this->data());
    return *this;
  }
  constexpr self &transform_unary(std::function<data_t(const data_t &)> &&op) {
    return this->transform_unary_raw(std::move(op)).safe_mod();
  }
  constexpr self &transform_binary_raw(
    const self &rhs,
    std::function<data_t(const data_t &, const data_t &)> &&op) {
    this->data() = op(this->data(), rhs.data());
    return *this;
  }
  constexpr self &
  transform_binary(const self &rhs,
                   std::function<data_t(const data_t &, const data_t &)> &&op) {
    return this->transform_binary_raw(rhs, std::move(op)).safe_mod();
  }
  friend constexpr self
  calc_unary_raw(const self &lhs, std::function<data_t(const data_t &)> &&op) {
    self ret(lhs);
    return ret.transform_unary_raw(op);
  }
  friend constexpr self calc_unary(const self &lhs,
                                   std::function<data_t(const data_t &)> &&op) {
    return calc_unary_raw(lhs, std::move(op)).safe_mod();
  }
  friend constexpr self
  calc_binary_raw(const self &lhs,
                  const self &rhs,
                  std::function<data_t(const data_t &, const data_t &)> &&op) {
    self ret(lhs);
    return ret.transform_binary_raw(rhs, op);
  }
  friend constexpr self
  calc_binary(const self &lhs,
              const self &rhs,
              std::function<data_t(const data_t &, const data_t &)> &&op) {
    return calc_binary_raw(lhs, rhs, std::move(op)).safe_mod();
  }
  constexpr self inverse() const {
    if (this->gcd(this->data(), this->get_mod()) != 1)
      throw std::runtime_error("inverse not exist");
    signed_common_t a = this->data(), b = this->get_mod();
    signed_common_t m0 = 0;
    for (signed_common_t q, _, m1 = 1; a;) {
      q = b / a;
      b -= a * q;
      m0 -= m1 * q;
      _ = b;
      b = a;
      a = _;
      _ = m0;
      m0 = m1;
      m1 = _;
    }
    self ret;
    ret.data() = m0 + (m0 < 0 ? this->get_mod() / b : 0);
    return ret;
  };
  self &operator++() {
    this->data()++;
    if (this->data() == this->get_mod()) this->data() = 0;
    return *this;
  }
  self &operator--() {
    if (this->data() == 0) this->data() = this->get_mod();
    this->data()--;
    return *this;
  }
  self operator++(int) {
    self ret = *this;
    ++*this;
    return ret;
  }
  self operator--(int) {
    self ret = *this;
    --*this;
    return ret;
  }
  self operator+() { return *this; }
  self operator-() {
    self ret;
    ret.data() = this->get_mod() - this->data();
    return ret;
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
  self &operator/=(const self &rhs) {
    return this->transform_binary(rhs.inverse(), std::multiplies<data_t>());
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
  friend self operator/(const self &lhs, const self &rhs) {
    return self(lhs) /= rhs;
  }
  friend bool operator==(const self &lhs, const self &rhs) {
    return lhs.data() == rhs.data();
  }
  friend bool operator!=(const self &lhs, const self &rhs) {
    return lhs.data() != rhs.data();
  }
  friend bool operator<(const self &lhs, const self &rhs) {
    return lhs.data() < rhs.data();
  }
  friend bool operator>(const self &lhs, const self &rhs) {
    return lhs.data() > rhs.data();
  }
  friend bool operator<=(const self &lhs, const self &rhs) {
    return lhs.data() <= rhs.data();
  }
  friend bool operator>=(const self &lhs, const self &rhs) {
    return lhs.data() >= rhs.data();
  }
  friend std::istream &operator>>(std::istream &is, self &x) {
    is >> x.data();
    x.safe_mod();
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &x) {
    os << x.data();
    return os;
  }
};
#undef _TRAITS
#undef _TO_CONST
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
#define _square_matrix_needed             \
  if (this->get_row() != this->get_col()) \
  throw std::runtime_error("The matrix is not square matrix")
public:
  using self = matrix<Tp, Equal>;

protected:
  const std::size_t row, col;
  std::vector<std::vector<Tp>> mat;
  Equal equ;

public:
  matrix(const std::size_t &_row,
         const std::size_t &_col,
         const Equal &_equal = Equal())
    : row(_row), col(_col), mat(_row, std::vector<Tp>(_col)), equ(_equal) {}
  template <typename Up, _TRAITS(_CONVERTIBLE(Up, Tp))>
  matrix(const std::size_t &_row,
         const std::size_t &_col,
         Up &&scalar,
         const Equal &_equal = Equal())
    : row(_row), col(_col), mat(_row, std::vector<Tp>(_col, scalar)),
      equ(_equal) {}
  template <typename Up, _TRAITS(_CONVERTIBLE(Up, self &))>
  matrix(Up &&rhs)
    : row(std::forward<self>(rhs).get_row()),
      col(std::forward<self>(rhs).get_col()), mat(std::forward<self>(rhs).mat),
      equ(std::forward<self>(rhs).equ) {}
  template <typename Up, _TRAITS(_CONVERTIBLE(Up, self))>
  self &operator=(Up &&rhs) {
    _for_row(i) this->mat[i] = std::forward<self>(rhs).mat[i];
    return *this;
  }
  void clear() {
    _for_each(i, j) this->data(i, j) = 0;
  }
  constexpr const std::size_t &get_row() const { return this->row; }
  constexpr const std::size_t &get_col() const { return this->col; }
  constexpr Tp &data(const size_t &r, const size_t &c) const {
    return const_cast<self * const>(this)->mat[r][c];
  }
  constexpr Tp &data(const size_t &r, const size_t &c) {
    return this->mat[r][c];
  }
  constexpr self trans() {
    self ret(this->get_col(), this->get_row(), this->equ);
    _for_each(i, j) ret.data(j, i) = this->data(i, j);
    return ret;
  }
  constexpr std::size_t rank() { return gauss(self(*this)); }
  constexpr Tp det() const {
    _square_matrix_needed;
    self _(*this);
    std::size_t rk = gauss(_);
    if (rk != row) return 0;
    Tp ans(1);
    _for_row(i) ans *= this->data(i, i);
    return ans;
  }
  constexpr self inverse() const {
    _square_matrix_needed;
    self _(this->get_row(), this->get_row() * 2, this->equ);
    _for_each(i, j) _.data(i, j) = this->data(i, j);
    _for_each(i, j) _.data(i, j + this->get_row()) = (i == j);
    std::size_t rk = gauss(_);
    if (rk != row) throw std::runtime_error("inverse not exist");
    _for_row(i) {
      const Tp &now = _.data(i, i);
      _for_col(j) _.data(i, j + this->get_row()) /= now;
    }
    self ret(this->get_row(), this->get_col(), this->equ);
    _for_each(i, j) ret.data(i, j) = _.data(i, j + this->get_row());
    return ret;
  }
  constexpr self &add(const self &rhs) {
    _for_each(i, j) this->data(i, j) += rhs.data(i, j);
    return *this;
  }
  constexpr self &minus(const self &rhs) {
    _for_each(i, j) this->data(i, j) -= rhs.data(i, j);
    return *this;
  }
  constexpr self &multiply(const self &rhs) {
    _for_each(i, j) this->data(i, j) *= rhs.data(i, j);
    return *this;
  }
  constexpr self &divide(const self &rhs) {
    _for_each(i, j) this->data(i, j) /= rhs.data(i, j);
    return *this;
  }
  constexpr self &add(const Tp &scalar) {
    _for_each(i, j) this->data(i, j) += scalar;
    return *this;
  }
  constexpr self &minus(const Tp &scalar) {
    _for_each(i, j) this->data(i, j) -= scalar;
    return *this;
  }
  constexpr self &multiply(const Tp &scalar) {
    _for_each(i, j) this->data(i, j) *= scalar;
    return *this;
  }
  constexpr self &divide(const Tp &scalar) {
    _for_each(i, j) this->data(i, j) /= scalar;
    return *this;
  }
  self operator*(const self &rhs) {
    if (this->get_col() != rhs.get_row())
      throw std::logic_error("you can not multiple (" +
                             std::to_string(this->get_row()) + "x" +
                             std::to_string(this->get_col()) +
                             ") matrix and (" + std::to_string(rhs.get_row()) +
                             "x" + std::to_string(rhs.get_col()) + ") matrix");
    self ret(this->get_row(), rhs.get_col(), 0, this->equ);
    _for_row(i)
      _for_col(k)
        _for(j, 0, rhs.get_col())
          ret.data(i, j) += this->data(i, k) * rhs.data(k, j);
    return ret;
  }
  Tp &operator()(const std::size_t &r, const std::size_t &c) {
    return this->data(r, c);
  }
  self operator+() { return *this; }
  self operator-() { return self(*this).multiply(-1); }
  self &operator+=(const self &rhs) { return this->add(rhs); }
  self &operator-=(const self &rhs) { return this->minus(rhs); }
  self &operator*=(const self &rhs) { return *this = *this * rhs; }
  self &operator/=(const self &rhs) { return *this *= rhs.inverse(); }
  self operator+(const self &rhs) { return self(*this) += rhs; }
  self operator-(const self &rhs) { return self(*this) -= rhs; }
  self operator/(const self &rhs) { return self(*this) /= rhs; }
  bool operator==(const self &rhs) const {
    _for_each(i, j)
      if (!this->equ(this->data(i, j), rhs.data(i, j))) return false;
    return true;
  }
  bool operator!=(const self &rhs) const { return !(*this == rhs); }
  constexpr friend std::size_t gauss(self &now) {
    std::size_t rk = 0;
    _for(i, 0, std::min(now.get_row(), now.get_col()), now_row = 0) {
      now_row = rk;
      _for(j, now_row + 1, now.get_row())
        if (std::abs(now.data(j, i)) > std::abs(now.data(now_row, i)))
          now_row = j;
      if (now.equ(now.data(now_row, i), 0)) continue;
      if (now_row != rk) std::swap(now.mat[now_row], now.mat[rk]);
      _for(j, 0, now.get_row()) {
        if (j == rk) continue;
        Tp _ = now.data(j, i) / now.data(rk, i);
        now.data(j, i) = 0;
        _for(k, i + 1, now.get_col()) now.data(j, k) -= now.data(rk, k) * _;
      }
      ++rk;
    }
    return rk;
  }
  friend std::istream &operator>>(std::istream &is, self &x) {
    _for(i, 0, x.get_row())
      _for(j, 0, x.get_col()) is >> x.data(i, j);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &x) {
    _for(i, 0, x.get_row())
      _for(j, 0, x.get_col())
        os << x.data(i, j) << (j == x.get_col() - 1 ? '\n' : ' ');
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
using namespace std;
const int MOD = 1e9 + 7;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  matrix<mod_integer<long long, MOD>> a(n, n);
  cin >> a;
  try {
    cout << a.inverse();
  } catch (...) { cout << "No Solution"; }
  return 0;
}
