#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e8;
template <class Tp, std::size_t row, std::size_t col>
class matrix {
#define _for_row(i) for (std::size_t i = 0; i < row; ++i)
#define _for_col(i) for (std::size_t i = 0; i < col; ++i)
#define _for_each(i, j) \
  _for_row(i)           \
    _for_col(j)
#define _perfect(Tp)     \
  template <typename Tp, \
            std::enable_if_t<std::is_convertible_v<self, Tp>> * = nullptr>
#define _forward_self std::forward<self>
public:
  using self = matrix<Tp, row, col>;

protected:
  Tp mat[row][col];

public:
  matrix() = default;
  matrix(const self &rhs) {
    _for_each(i, j) this->mat[i][j] = rhs.data(i, j);
  }
  self &operator=(const self &rhs) {
    _for_each(i, j) this->mat[i][j] = rhs.data(i, j);
    return *this;
  }
  Tp &data(const size_t &r, const size_t &c) const {
    return *(Tp * const)&(this->mat[r][c]);
  }
  Tp &data(const size_t &r, const size_t &c) { return this->mat[r][c]; }
  matrix<Tp, col, row> trans() {
    matrix<Tp, col, row> ret;
    _for_each(i, j) ret.data(j, i) = this->mat[i][j];
    return ret;
  }
  template <std::size_t row2>
  matrix<Tp, row, row2> operator*(const matrix<Tp, col, row2> &rhs) {
    matrix<Tp, row, row2> ret;
    _for_row(i)
      _for_col(k)
        for (std::size_t j = 0; j < row2; ++j)
          ret.data(i, j) = ret.data(i, j) + this->mat[i][k] * rhs.data(k, j);
    return ret;
  }
#undef _for_row
#undef _for_col
#undef _for_each
#undef _perfect
#undef _forward_self
};
template <std::size_t mod = MOD>
class mod_i64 {
public:
  using self = mod_i64<mod>;

protected:
  i64 num;

public:
  mod_i64(const i64 &_num = 0): num(_num % mod) {}
  mod_i64(const self &rhs): num(rhs.num) {}
  self &operator=(const i64 &_num) {
    this->num = _num % mod;
    return *this;
  }
  self &operator=(const self &rhs) {
    this->num = rhs.num;
    return *this;
  }
  self calc(const self &rhs, std::function<i64(i64, i64)> &&op) {
    return self(op(this->num, rhs.num) % mod);
  }
  self calc_raw(const self &rhs, std::function<i64(i64, i64)> &&op) {
    return self(op(this->num, rhs.num));
  }
  i64 &data() const { return *(i64 * const)&(this->num); }
  i64 &data() { return this->num; }
  self operator+(const self &rhs) { return this->calc(rhs, std::plus<i64>()); }
  self operator-(const self &rhs) { return this->calc(rhs, std::minus<i64>()); }
  self operator*(const self &rhs) {
    return this->calc(rhs, std::multiplies<i64>());
  }
  self operator/(const self &rhs) {
    return this->calc(rhs, std::divides<i64>());
  }
};
matrix<mod_i64<>, 2ull, 2ull> fib_trans, e;
matrix<mod_i64<>, 2ull, 1ull> fib;
auto __STATIC__ = []() {
  e.data(0, 0) = e.data(1, 1) = fib_trans.data(0, 0) = fib_trans.data(1, 0) =
    fib_trans.data(0, 1) = 1;
  fib_trans.data(1, 1) = fib.data(0, 1) = 0;
  fib.data(0, 0) = 1;
  return 0.0;
}();
template <class Tp, std::size_t row>
matrix<Tp, row, row> qpow(matrix<Tp, row, row> a, i64 b) {
  matrix<Tp, row, row> res(e);
  for (; b; b >>= 1, a = a * a)
    if (b & 1) res = res * a;
  return res;
}
template <std::size_t mod>
ostream &operator<<(ostream &os, const mod_i64<mod> &x) {
  os << x.data();
  return os;
}
void solve() {
  i64 n, m;
  cin >> n >> m;
  cout << (qpow(fib_trans, __gcd(n, m)) * fib).data(1, 0);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
