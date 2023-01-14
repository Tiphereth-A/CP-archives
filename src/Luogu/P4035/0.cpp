#include <bits/stdc++.h>
using namespace std;
namespace Matrix {
#define _TRAITS(expression, __...) \
  std::enable_if_t<expression, ##__> * = nullptr
#define _CONVERTIBLE(Tp, Up) std::is_convertible<Tp, Up>::value
namespace Matrix_helper {
template <typename Tp>
struct Zero final {
  static constexpr Tp value = 0;
};
template <typename Tp>
struct One final {
  static constexpr Tp value = 1;
};
}  // namespace Matrix_helper
using namespace Matrix_helper;
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
  constexpr friend std::ptrdiff_t _gauss(self &now) {
    std::size_t rk = 0;
    bool neg = false;
    _for(i, 0, std::min(now.get_row(), now.get_col()), now_row = 0) {
      now_row = rk;
      _for(j, now_row + 1, now.get_row())
        if (std::abs(now.data(j, i)) > std::abs(now.data(now_row, i)))
          now_row = j;
      if (now.equ(now.data(now_row, i), now.get_zero())) continue;
      if (now_row != rk) {
        std::swap(now.mat[now_row], now.mat[rk]);
        neg ^= true;
      }
      _for(j, 0, now.get_row()) {
        if (j == rk) continue;
        data_t _ = now.data(j, i) / now.data(rk, i);
        now.data(j, i) = now.get_zero();
        _for(k, i + 1, now.get_col()) now.data(j, k) -= now.data(rk, k) * _;
      }
      ++rk;
    }
    return static_cast<std::ptrdiff_t>(neg ? -rk : rk);
  }

public:
  matrix(const std::size_t &_row,
         const std::size_t &_col,
         const Equal &_equal = Equal())
    : row(_row), col(_col), mat(_row, std::vector<data_t>(_col)), equ(_equal) {
    if (_row == 0 || _col == 0) throw std::logic_error("invalid parameters");
  }
  template <typename Up, _TRAITS(_CONVERTIBLE(Up, data_t))>
  matrix(const std::size_t &_row,
         const std::size_t &_col,
         Up &&scalar,
         const Equal &_equal = Equal())
    : row(_row), col(_col), mat(_row, std::vector<data_t>(_col, scalar)),
      equ(_equal) {
    if (_row == 0 || _col == 0) throw std::logic_error("invalid parameters");
  }
  template <typename Up, _TRAITS(_CONVERTIBLE(Up, self &))>
  matrix(Up &&rhs)
    : row(std::forward<self>(rhs).get_row()),
      col(std::forward<self>(rhs).get_col()), mat(row),
      equ(std::forward<self>(rhs).equ) {
    _for_row(i) this->mat[i] = std::forward<self>(rhs).mat[i];
  }
  constexpr const std::size_t &get_row() const { return this->row; }
  constexpr const std::size_t &get_col() const { return this->col; }
  constexpr const data_t &get_zero() const { return this->zero; }
  constexpr const data_t &get_one() const { return this->one; }
  constexpr data_t &data(const size_t &r, const size_t &c) const {
    return const_cast<self * const>(this)->mat[r][c];
  }
  constexpr data_t &data(const size_t &r, const size_t &c) {
    return this->mat[r][c];
  }
  data_t &operator()(const std::size_t &r, const std::size_t &c) {
    return this->data(r, c);
  }
  template <typename Unary>
  constexpr self &transform_unary(Unary &&op) {
    _for_each(i, j) this->data(i, j) = op(this->data(i, j));
    return *this;
  }
  constexpr friend std::ptrdiff_t gauss(self &now) { return _gauss(now); }
  constexpr self &multiply(const data_t &scalar) {
    return this->transform_unary(
      [&](const data_t &x) { return std::multiplies<data_t>()(x, scalar); });
  }

protected:
  const std::size_t row, col;
  std::vector<std::vector<Tp>> mat;
  Equal equ;
  static constexpr data_t zero = Zero<data_t>::value, one = One<data_t>::value;
#undef _for
#undef _for_row
#undef _for_col
#undef _for_each
};
#undef _TRAITS
#undef _CONVERTIBLE
}  // namespace Matrix
using Matrix::matrix;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
auto _ = [](const double &x, const double &y) {
  return std::abs(x - y) <= 1e-8;
};
double a[15];
int main() {
  int n;
  cin >> n;
  matrix<double, decltype(_)> m(n + 1, n + 2, _);
  double _;
  _for(i, 0, n)
    _for(j, 0, n - 1) {
      cin >> _;
      a[i] += _ * _;
      m(i, j) = _;
    }
  m.multiply(2);
  _for(i, 0, n) m(i, n) = -1;
  _for(i, 0, n) m(i, n + 1) = a[i];
  gauss(m);
  cout << fixed << setprecision(3);
  _for(i, 0, n - 1) cout << m(i, n + 1) / m(i, i) << ' ';
  return 0;
}
