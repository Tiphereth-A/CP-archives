#include <bits/stdc++.h>
using namespace std;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u128 = __uint128_t;
#define OPERATOR_OVERRIED_PAIR_(oper)                                         \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator oper##=(                              \
    std::pair<Tp, Up> &lhs, const std::pair<Tp, Up> &rhs) {                   \
    lhs.first oper## = rhs.first;                                             \
    lhs.second oper## = rhs.second;                                           \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> operator oper(std::pair<Tp, Up> lhs,            \
                                            const std::pair<Tp, Up> &rhs) {   \
    return lhs oper## = rhs;                                                  \
  }                                                                           \
  template <class Tp, class Up, class Vp>                                     \
  constexpr std::tuple<Tp, Up, Vp> &operator oper##=(                         \
    std::tuple<Tp, Up, Vp> &lhs, const std::tuple<Tp, Up, Vp> &rhs) {         \
    std::get<0>(lhs) oper## = std::get<0>(rhs);                               \
    std::get<1>(lhs) oper## = std::get<1>(rhs);                               \
    std::get<2>(lhs) oper## = std::get<2>(rhs);                               \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up, class Vp>                                     \
  constexpr std::tuple<Tp, Up, Vp> operator oper(                             \
    std::tuple<Tp, Up, Vp> lhs, const std::tuple<Tp, Up, Vp> &rhs) {          \
    return lhs oper## = rhs;                                                  \
  }                                                                           \
  template <class Tp, class Up, class Vp, class Wp>                           \
  constexpr std::tuple<Tp, Up, Vp, Wp> &operator oper##=(                     \
    std::tuple<Tp, Up, Vp, Wp> &lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) { \
    std::get<0>(lhs) oper## = std::get<0>(rhs);                               \
    std::get<1>(lhs) oper## = std::get<1>(rhs);                               \
    std::get<2>(lhs) oper## = std::get<2>(rhs);                               \
    std::get<3>(lhs) oper## = std::get<3>(rhs);                               \
    return lhs;                                                               \
  }                                                                           \
  template <class Tp, class Up, class Vp, class Wp>                           \
  constexpr std::tuple<Tp, Up, Vp, Wp> operator oper(                         \
    std::tuple<Tp, Up, Vp, Wp> lhs, const std::tuple<Tp, Up, Vp, Wp> &rhs) {  \
    return lhs oper## = rhs;                                                  \
  }
OPERATOR_OVERRIED_PAIR_(+)
OPERATOR_OVERRIED_PAIR_(-)
OPERATOR_OVERRIED_PAIR_(*)
OPERATOR_OVERRIED_PAIR_(/)
OPERATOR_OVERRIED_PAIR_(%)
#undef OPERATOR_OVERRIED_PAIR_
template <class Ch, class Tr, class Tp, class Up>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Ch, class Tr, class Tp, class Up>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::tuple<Tp, Up, Vp> &p) {
  return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::tuple<Tp, Up, Vp> &p) {
  return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is,
                                       std::tuple<Tp, Up, Vp, Wp> &p) {
  return is >> std::get<0>(p) >> std::get<1>(p) >> std::get<2>(p) >>
         std::get<3>(p);
}
template <class Ch, class Tr, class Tp, class Up, class Vp, class Wp>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const std::tuple<Tp, Up, Vp, Wp> &p) {
  return os << std::get<0>(p) << ' ' << std::get<1>(p) << ' ' << std::get<2>(p)
            << ' ' << std::get<3>(p);
}
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
};
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
};
template <class Tp>
auto discretization(Tp &var) -> Tp {
  Tp d__(var);
  std::sort(d__.begin(), d__.end());
  d__.erase(std::unique(d__.begin(), d__.end()), d__.end());
  for (auto &i : var)
    i = std::distance(d__.begin(), std::lower_bound(d__.begin(), d__.end(), i));
  return d__;
};
template <class Tp>
constexpr auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Container &x) {
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
const u32 MOD = 1e9 + 7;
template <class Tp,
          bool USE_EUCLIDIAN = std::is_integral_v<Tp>,
          class Iszero_t = std::function<bool(Tp)>>
class matrix {
  using self = matrix<Tp, USE_EUCLIDIAN, Iszero_t>;

protected:
  size_t r_sz, c_sz;
  Iszero_t iszero;
  std::valarray<Tp> data;
  ptrdiff_t do_gauss_default_(bool clear_all) {
    size_t rk = 0;
    bool neg = false;
    for (size_t i = 0, now_row; i < std::min(row_size(), col_size()); ++i) {
      now_row = rk;
      for (size_t j = now_row + 1; j < row_size(); ++j)
        std::abs((*this)(j, i)) > std::abs((*this)(now_row, i)) ?
          (now_row = j) :
          0;
      if (iszero((*this)(now_row, i))) continue;
      if (now_row != rk) {
        std::valarray<Tp> tmp_ = row(now_row);
        row(now_row) = row(rk);
        row(rk) = tmp_;
        neg ^= true;
      }
      std::valarray<Tp> tmp_ =
        data[std::slice(rk * col_size() + i + 1, col_size() - i - 1, 1)];
      for (size_t j = clear_all ? 0 : rk + 1; j < row_size(); ++j) {
        if (j == rk) continue;
        Tp _ = (*this)(j, i) / (*this)(rk, i);
        (*this)(j, i) = 0;
        data[std::slice(j * col_size() + i + 1, col_size() - i - 1, 1)] -=
          tmp_ * _;
      }
      ++rk;
    }
    return neg ? -ptrdiff_t(rk) : ptrdiff_t(rk);
  }
  constexpr ptrdiff_t do_gauss_euclidian_(bool clear_all) {
    size_t rk = 0;
    bool neg = false;
    for (size_t i = 0, now_row; i < std::min(row_size(), col_size()); ++i) {
      now_row = rk;
      for (size_t j = now_row + 1; j < row_size(); ++j)
        std::abs((*this)(j, i)) > std::abs((*this)(now_row, i)) ?
          (now_row = j) :
          0;
      if (iszero((*this)(now_row, i))) continue;
      if (now_row != rk) {
        std::valarray<Tp> tmp_ = row(now_row);
        row(now_row) = row(rk);
        row(rk) = tmp_;
        neg ^= true;
      }
      for (size_t j = clear_all ? 0 : rk + 1; j < row_size(); ++j) {
        if ((*this)(j, i) > (*this)(i, i)) {
          std::valarray<Tp> tmp_ = row(j);
          row(j) = row(i);
          row(i) = tmp_;
          neg ^= true;
        }
        while (iszero(!(*this)(i, i))) {
          Tp _ = (*this)(j, i) / (*this)(i, i);
          std::valarray<Tp> tmp_ = row(i);
          row(j) -= tmp_ * _;
          row(i) = row(j);
          row(j) = tmp_;
          neg ^= true;
        }
      }
      ++rk;
    }
    return neg ? -ptrdiff_t(rk) : ptrdiff_t(rk);
  }

public:
  matrix(size_t row, size_t col, Iszero_t iszero_func, const Tp &val = Tp{})
    : r_sz(row), c_sz(col), iszero(iszero_func), data(val, row * col) {}
  matrix(size_t row,
         size_t col,
         Iszero_t iszero_func,
         const std::valarray<Tp> &data_)
    : r_sz(row), c_sz(col), iszero(iszero_func), data(data_) {}
  constexpr size_t row_size() const { return r_sz; }
  constexpr size_t col_size() const { return c_sz; }
  std::valarray<Tp> view() const { return data; }
  Tp &operator()(size_t r, size_t c) { return data[r * col_size() + c]; }
  Tp operator()(size_t r, size_t c) const { return data[r * col_size() + c]; }
  friend std::istream &operator>>(std::istream &is, self &mat) {
    for (auto &i : mat.data) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &mat) {
    for (size_t i = 0; i < mat.row_size(); ++i)
      for (size_t j = 0; j < mat.col_size(); ++j)
        os << mat(i, j) << " \n"[j == mat.col_size() - 1];
    return os;
  }
#define INVOKES_SLICE__(name, para1_t, para1, ...)                             \
  std::valarray<Tp> name(para1_t para1) const __VA_ARGS__ std::slice_array<Tp> \
    name(para1_t para1) __VA_ARGS__
  INVOKES_SLICE__(row, size_t, r, {
    return data[std::slice(r * col_size(), col_size(), 1)];
  })
  INVOKES_SLICE__(col, size_t, c, {
    return data[std::slice(c, row_size(), col_size())];
  })
  INVOKES_SLICE__(diag, ptrdiff_t, d, {
    assert(row_size() == col_size());
    return data[d >= 0 ?
                  std::slice(d, row_size() - d, row_size() + 1) :
                  std::slice(-d * row_size(), row_size() + d, row_size() + 1)];
  })
#undef INVOKES_SLICE__
  self submatrix(size_t row_l, size_t row_r, size_t col_l, size_t col_r) const {
    return self(row_r - row_l,
                col_r - col_l,
                iszero,
                data[std::gslice(row_l * col_size() + col_l,
                                 {row_r - row_l, col_r - col_l},
                                 {col_size(), 1})]);
  }
  std::gslice_array<Tp>
  submatrix_raw(size_t row_l, size_t row_r, size_t col_l, size_t col_r) {
    return data[std::gslice(row_l * col_size() + col_l,
                            {row_r - row_l, col_r - col_l},
                            {col_size(), 1})];
  }
#define OPER_SCALA__(op)                                                      \
  friend self operator op(self lhs, const Tp &val) { return lhs op## = val; } \
  self &operator op##=(const Tp & val) {                                      \
    data op## = val;                                                          \
    return *this;                                                             \
  }
#define OPER_MAT__(op)                                 \
  friend self operator op(self lhs, const self &rhs) { \
    return lhs op## = rhs;                             \
  }                                                    \
  self &operator op##=(const self & rhs) {             \
    data op## = rhs.data;                              \
    return *this;                                      \
  }
#define OPER_MAT_F__(op, ...)                               \
  friend self operator op(const self &lhs, const self &rhs) \
    __VA_ARGS__ self &operator op##=(const self &rhs) {     \
    return *this = *this op rhs;                            \
  }
  OPER_SCALA__(+)
  OPER_MAT__(+)
  OPER_SCALA__(-)
  OPER_MAT__(-)
  OPER_SCALA__(*)
  OPER_MAT_F__(*, {
    assert(lhs.col_size() == rhs.row_size());
    self ret(lhs.row_size(), rhs.col_size(), lhs.iszero);
    for (size_t i = 0; i < ret.row_size(); ++i) {
      auto &&r_ = lhs.row(i);
      for (size_t j = 0; j < ret.col_size(); ++j)
        ret(i, j) = (r_ * rhs.col(j)).sum();
    }
    return ret;
  })
  OPER_SCALA__(/)
  OPER_MAT_F__(/, { return lhs * rhs.inverse(); })
  OPER_SCALA__(%)
  OPER_MAT_F__(|, {
    assert(lhs.row_size() == lhs.col_size() &&
           rhs.row_size() == lhs.row_size());
    self tmp_ = merge_lr(lhs, rhs);
    assert(std::abs(tmp_.do_gauss()) != lhs.row_size());
    for (size_t i = 0; i < lhs.row_size(); ++i)
      tmp_
        .data[std::slice(i * (lhs.col_size() + rhs.col_size()) + lhs.col_size(),
                         rhs.col_size(),
                         1)] /= std::valarray<Tp>(tmp_(i, i), rhs.col_size());
    return tmp_.submatrix(
      0, rhs.row_size(), lhs.col_size(), lhs.col_size() + rhs.col_size());
  })
#undef OPER_MAT_F__
#undef OPER_MAT__
#undef OPER_SCALA__
  friend self merge_ud(const self &lhs, const self &rhs) {
    self ret(lhs.row_size() + rhs.row_size(), lhs.col_size(), lhs.iszero);
    ret.data[std::slice(0, lhs.row_size() * lhs.col_size(), 1)] = lhs.view();
    ret.data[std::slice(
      lhs.row_size() * lhs.col_size(), rhs.row_size() * rhs.col_size(), 1)] =
      rhs.view();
    return ret;
  }
  friend self merge_lr(const self &lhs, const self &rhs) {
    self ret(lhs.row_size(), lhs.col_size() + rhs.col_size(), lhs.iszero);
    ret.data[std::gslice(
      0, {lhs.row_size(), lhs.col_size()}, {ret.col_size(), 1})] = lhs.view();
    ret.data[std::gslice(
      lhs.col_size(), {rhs.row_size(), rhs.col_size()}, {ret.col_size(), 1})] =
      rhs.view();
    return ret;
  }
  ptrdiff_t do_gauss(bool clear_all = true) {
    return USE_EUCLIDIAN ? do_gauss_euclidian_(clear_all) :
                           do_gauss_default_(clear_all);
  }
  self transpose() const {
    self ret(col_size(), row_size(), iszero);
    for (size_t i = 0; i < row_size(); ++i) ret.col(i) = row(i);
    return ret;
  }
  self inverse() const {
    assert(row_size() == col_size());
    self ret(row_size(), col_size(), iszero);
    ret.diag(0) = 1;
    assert(std::abs((ret = merge_lr(*this, ret)).do_gauss()) != row_size());
    for (size_t i = 0; i < row_size(); ++i)
      ret.data[std::slice((i * 2 + 1) * col_size(), col_size(), 1)] /=
        std::valarray<Tp>(ret(i, i), col_size());
    ret = ret.submatrix(0, row_size(), col_size(), col_size() * 2);
    return ret;
  }
  Tp trace() const { return diag(0).sum(); }
  size_t rank() const { return std::abs(self(*this).do_gauss(false)); }
  Tp det() const {
    assert(row_size() == col_size());
    self tmp_(*this);
    ptrdiff_t rk_ = tmp_.do_gauss(false);
    if (std::abs(rk_) != row_size()) return Tp{};
    Tp ret = tmp_(0, 0);
    for (size_t i = 1; i < row_size(); ++i) ret *= tmp_(i, i);
    return rk_ < 0 ? -ret : ret;
  }
};
matrix<i64> qpow(matrix<i64> a, i64 b, const i64 &mod = MOD) {
  matrix<i64> res(2, 2, [](i64 x) { return x == 0; }, {1, 0, 0, 1});
  for (; b; b >>= 1, a = (a * a) % mod)
    if (b & 1) res = (res * a) % mod;
  return res;
};
constexpr uint64_t dec2uint_mod(const char * const num, const uint64_t mod) {
  size_t len = strlen(num);
  if (len == 0) return 0;
  u128 ans = 0;
  for (size_t i = 0; i + 8 <= len; i += 8) {
    uint64_t res = *((uint64_t *)(num + i));
    res = (res & 0x0F0F0F0F0F0F0F0F) * 2561 >> 8;
    res = (res & 0x00FF00FF00FF00FF) * 6553601 >> 16;
    res = (res & 0x0000FFFF0000FFFF) * 42949672960001 >> 32;
    ans = (ans * 100000000 + res) % mod;
  }
  for (auto pch = num + (len / 8 * 8); pch < num + len;)
    ans = (ans * 10 + (*(pch++) & '\x0f')) % mod;
  return ans;
}
auto solve([[maybe_unused]] int t_ = 0) -> void {
  string n_, m_;
  i64 n, m, a, b, c, d;
  cin >> n_ >> m_ >> a >> b >> c >> d;
  n = dec2uint_mod(n_.c_str(), MOD - (a != 1));
  m = dec2uint_mod(m_.c_str(), MOD - (a != 1));
  if (!n) n = MOD - (a != 1);
  if (!m) m = MOD - (a != 1);
  matrix<i64> x(2, 2, [](i64 x) { return x == 0; }, {a, 0, b, 1});
  matrix<i64> y(2, 2, [](i64 x) { return x == 0; }, {c, 0, d, 1});
  x = qpow(x, m - 1);
  auto __ = qpow(x * y % MOD, n - 1) * x % MOD;
  cout << (__(0, 0) + __(1, 0)) % MOD;
}
int main() {
  int i_ = 0;
  solve(i_);
  return 0;
}
