#include <bits/stdc++.h>
struct CustomHash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM =
      std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
using i64 = int64_t;
#define for_(i, l, r, vars...)                                            \
  for (std::make_signed_t<decltype(l + r)> i = (l), i##end = (r), ##vars; \
       i <= i##end;                                                       \
       ++i)
#define read_var_(type, name) \
  type name;                  \
  std::cin >> name
template <class Tp>
constexpr auto chkmin(Tp &a, Tp b) -> bool {
  return b < a ? a = b, true : false;
}
template <class Tp>
constexpr auto chkmax(Tp &a, Tp b) -> bool {
  return a < b ? a = b, true : false;
}
template <class Tp>
constexpr auto ispow2(Tp i) -> bool {
  return i && (i & -i) == i;
}
#define TPL_SIZE_(Tuple) std::tuple_size_v<std::remove_reference_t<Tuple>>
namespace tuple_detail_ {
template <std::size_t Begin, class Tuple, std::size_t... Is>
constexpr auto subtuple_impl_(Tuple &&t, std::index_sequence<Is...>) {
  return std::make_tuple(std::get<Is + Begin>(t)...);
}
template <class Tuple, class BinOp, std::size_t... Is>
constexpr auto
apply2_impl_(BinOp &&f, Tuple &&lhs, Tuple &&rhs, std::index_sequence<Is...>) {
  return std::make_tuple(
    std::forward<BinOp>(f)(std::get<Is>(lhs), std::get<Is>(rhs))...);
}
}  // namespace tuple_detail_
template <std::size_t Begin, std::size_t Len, class Tuple>
constexpr auto subtuple(Tuple &&t) {
  static_assert(Begin <= TPL_SIZE_(Tuple) && Len <= TPL_SIZE_(Tuple) &&
                  Begin + Len <= TPL_SIZE_(Tuple),
                "Out of range");
  return tuple_detail_::subtuple_impl_<Begin>(t,
                                              std::make_index_sequence<Len>());
}
template <std::size_t Pos, class Tp, class Tuple>
constexpr auto tuple_push(Tp &&v, Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        std::make_tuple(v),
                        subtuple<Pos, TPL_SIZE_(Tuple) - Pos>(t));
}
template <class Tp, class Tuple>
constexpr auto tuple_push_front(Tp &&v, Tuple &&t) {
  return tuple_push<0>(v, t);
}
template <class Tp, class Tuple>
constexpr auto tuple_push_back(Tp &&v, Tuple &&t) {
  return tuple_push<TPL_SIZE_(Tuple)>(v, t);
}
template <std::size_t Pos, class Tuple>
constexpr auto tuple_pop(Tuple &&t) {
  static_assert(TPL_SIZE_(Tuple) > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, Pos>(t),
                        subtuple<Pos + 1, TPL_SIZE_(Tuple) - Pos - 1>(t));
}
template <class Tuple>
constexpr auto tuple_pop_front(Tuple &&t) {
  return tuple_pop<0>(t);
}
template <class Tuple>
constexpr auto tuple_pop_back(Tuple &&t) {
  return tuple_pop<TPL_SIZE_(Tuple) - 1>(t);
}
template <class Tuple, class BinOp>
constexpr auto apply2(BinOp &&f, Tuple &&lhs, Tuple &&rhs) {
  return tuple_detail_::apply2_impl_(
    f, lhs, rhs, std::make_index_sequence<TPL_SIZE_(Tuple)>());
}
#define OO_PTEQ_(op)                                                          \
  template <class Tp, class Up>                                               \
  constexpr auto operator op(std::pair<Tp, Up> lhs,                           \
                             const std::pair<Tp, Up> &rhs) {                  \
    return {lhs.first op rhs.first, lhs.second op rhs.second};                \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op(std::tuple<Ts...> const &lhs,                    \
                             std::tuple<Ts...> const &rhs) {                  \
    return apply2([](auto &&l, auto &&r) { return l op r; }, lhs, rhs);       \
  }                                                                           \
  template <class Tp, class Up>                                               \
  constexpr std::pair<Tp, Up> &operator op##=(std::pair<Tp, Up> &lhs,         \
                                              const std::pair<Tp, Up> &rhs) { \
    lhs.first op## = rhs.first;                                               \
    lhs.second op## = rhs.second;                                             \
    return lhs;                                                               \
  }                                                                           \
  template <class... Ts>                                                      \
  constexpr auto operator op##=(std::tuple<Ts...> &lhs,                       \
                                const std::tuple<Ts...> &rhs) {               \
    return lhs = lhs op rhs;                                                  \
  }
OO_PTEQ_(+)
OO_PTEQ_(-)
OO_PTEQ_(*)
OO_PTEQ_(/)
OO_PTEQ_(%)
OO_PTEQ_(&)
OO_PTEQ_(|)
OO_PTEQ_(^)
OO_PTEQ_(<<)
OO_PTEQ_(>>)
#undef OO_PTEQ_
#undef TPL_SIZE_
template <class Tp, class Up>
std::istream &operator>>(std::istream &is, std::pair<Tp, Up> &p) {
  return is >> p.first >> p.second;
}
template <class Tp, class Up>
std::ostream &operator<<(std::ostream &os, const std::pair<Tp, Up> &p) {
  return os << p.first << ' ' << p.second;
}
template <typename... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &p) {
  std::apply([&](Ts &...targs) { ((is >> targs), ...); }, p);
  return is;
}
template <typename... Ts>
std::ostream &operator<<(std::ostream &os, const std::tuple<Ts...> &p) {
  std::apply(
    [&](Ts const &...targs) {
      std::size_t n{0};
      ((os << targs << (++n != sizeof...(Ts) ? " " : "")), ...);
    },
    p);
  return os;
}
template <class Ch,
          class Tr,
          class Ct,
          std::enable_if_t<std::is_same_v<decltype(std::declval<Ct>().begin()),
                                          typename Ct::iterator> &&
                           std::is_same_v<decltype(std::declval<Ct>().end()),
                                          typename Ct::iterator>> * = nullptr>
std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os,
                                       const Ct &x) {
  if (x.begin() == x.end()) return os;
  for (auto it = x.begin(); it != x.end() - 1; ++it) os << *it << ' ';
  os << x.back();
  return os;
}
const i64 MOD = 1e9 + 7;
using namespace std;
namespace MODINT {
constexpr int64_t safe_mod(int64_t x, int64_t m) {
  return (x %= m) < 0 ? x + m : x;
}
constexpr std::pair<int64_t, int64_t> invgcd(int64_t a, int64_t b) {
  if ((a = safe_mod(a, b)) == 0) return {b, 0};
  int64_t s = b, m0 = 0;
  for (int64_t q = 0, _ = 0, m1 = 1; a;) {
    _ = s - a * (q = s / a);
    s = a;
    a = _;
    _ = m0 - m1 * q;
    m0 = m1;
    m1 = _;
  }
  return {s, m0 + (m0 < 0 ? b / s : 0)};
}
template <uint32_t MOD>
class Mint {
  static_assert(MOD >= 1);
  using self = Mint<MOD>;

protected:
  uint32_t v_;

public:
  static constexpr uint32_t mod() { return MOD; }
  static constexpr self raw(uint32_t v) {
    self x;
    x.v_ = v;
    return x;
  }
  constexpr Mint(): v_(0) {}
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_signed<T>::value> * = nullptr>
  constexpr Mint(T v): Mint() {
    int64_t x = (int64_t)(v % (int64_t)mod());
    v_ = (uint32_t)(x + (x < 0 ? mod() : 0));
  }
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_unsigned<T>::value> * = nullptr>
  constexpr Mint(T v): v_((uint32_t)(v % mod())) {}
  friend std::istream &operator>>(std::istream &is, self &x) {
    int64_t xx;
    is >> xx;
    xx %= mod();
    x.v_ = (uint32_t)(xx + (xx < 0 ? mod() : 0));
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &x) {
    return os << x.v_;
  }
  constexpr const uint32_t &val() const { return v_; }
  constexpr explicit operator uint32_t() const { return val(); }
  constexpr uint32_t &data() { return v_; }
  constexpr self &operator++() {
    if (++v_ == mod()) v_ = 0;
    return *this;
  }
  constexpr self &operator--() {
    if (!v_) v_ = mod();
    --v_;
    return *this;
  }
  constexpr self operator++(int) {
    self result = *this;
    ++*this;
    return result;
  }
  constexpr self operator--(int) {
    self result = *this;
    --*this;
    return result;
  }
  constexpr self &operator+=(const self &rhs) {
    v_ += rhs.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr self &operator-=(const self &rhs) {
    v_ -= rhs.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr self &operator*=(const self &rhs) {
    v_ = (uint32_t)((uint64_t)v_ * rhs.v_ % mod());
    return *this;
  }
  constexpr self &operator/=(const self &rhs) {
    return *this = *this * inverse(rhs);
  }
  constexpr self operator+() const { return *this; }
  constexpr self operator-() const { return self() - *this; }
  constexpr friend self pow(self x, uint64_t y) {
    self res(1);
    for (; y; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }
  constexpr friend self inverse(const self &x) {
    auto &&_ = invgcd(x.v_, self::mod());
    if (_.first != 1) throw std::runtime_error("Inverse not exist");
    return _.second;
  }
  constexpr friend self operator+(self lhs, const self &rhs) {
    return lhs += rhs;
  }
  constexpr friend self operator-(self lhs, const self &rhs) {
    return lhs -= rhs;
  }
  constexpr friend self operator*(self lhs, const self &rhs) {
    return lhs *= rhs;
  }
  constexpr friend self operator/(self lhs, const self &rhs) {
    return lhs /= rhs;
  }
  constexpr friend bool operator==(const self &lhs, const self &rhs) {
    return lhs.v_ == rhs.v_;
  }
  constexpr friend bool operator!=(const self &lhs, const self &rhs) {
    return lhs.v_ != rhs.v_;
  }
};
template <ptrdiff_t ID = -1>
class DyMint {
  using self = DyMint<ID>;
  struct Barrett_ {
    uint32_t m_;
    uint64_t im;
    constexpr explicit Barrett_(uint32_t m = 998244353)
      : m_(m), im((uint64_t)(-1) / m + 1) {}
    constexpr uint32_t umod() const { return m_; }
    constexpr uint32_t mul(uint32_t a, uint32_t b) const {
      uint64_t z = a;
      z *= b;
      uint64_t x = (uint64_t)(((__uint128_t)z * im) >> 64);
      uint32_t v = (uint32_t)(z - x * m_);
      return v + (m_ <= v ? m_ : 0);
    }
  };

protected:
  uint32_t v_;
  static Barrett_ bt_;

public:
  static constexpr uint32_t mod() { return bt_.umod(); }
  static constexpr void set_mod(uint32_t m) {
    assert(1 <= m);
    bt_ = Barrett_(m);
  }
  static constexpr self raw(uint32_t v) {
    self x;
    x.v_ = v;
    return x;
  }
  constexpr DyMint(): v_(0) {}
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_signed<T>::value> * = nullptr>
  constexpr DyMint(T v): DyMint() {
    int64_t x = (int64_t)(v % (int64_t)mod());
    v_ = (uint32_t)(x + (x < 0 ? mod() : 0));
  }
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_unsigned<T>::value> * = nullptr>
  constexpr DyMint(T v): v_((uint32_t)(v % mod())) {}
  friend std::istream &operator>>(std::istream &is, self &x) {
    int64_t xx;
    is >> xx;
    xx %= mod();
    x.v_ = (uint32_t)(xx + (xx < 0 ? mod() : 0));
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &x) {
    return os << x.v_;
  }
  constexpr const uint32_t &val() const { return v_; }
  constexpr explicit operator uint32_t() const { return val(); }
  constexpr uint32_t &data() { return v_; }
  constexpr self &operator++() {
    if (++v_ == mod()) v_ = 0;
    return *this;
  }
  constexpr self &operator--() {
    if (!v_) v_ = mod();
    --v_;
    return *this;
  }
  constexpr self operator++(int) {
    self result = *this;
    ++*this;
    return result;
  }
  constexpr self operator--(int) {
    self result = *this;
    --*this;
    return result;
  }
  constexpr self &operator+=(const self &rhs) {
    v_ += rhs.v_;
    if (v_ >= mod()) v_ -= mod();
    return *this;
  }
  constexpr self &operator-=(const self &rhs) {
    v_ -= rhs.v_;
    if (v_ >= mod()) v_ += mod();
    return *this;
  }
  constexpr self &operator*=(const self &rhs) {
    v_ = bt_.mul(v_, rhs.v_);
    return *this;
  }
  constexpr self &operator/=(const self &rhs) {
    return *this = *this * inverse(rhs);
  }
  constexpr self operator+() const { return *this; }
  constexpr self operator-() const { return self() - *this; }
  constexpr friend self pow(self x, uint64_t y) {
    self res(1);
    for (; y; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }
  constexpr friend self inverse(const self &x) {
    auto &&_ = invgcd(x.v_, self::mod());
    if (_.first != 1) throw std::runtime_error("Inverse not exist");
    return _.second;
  }
  constexpr friend self operator+(self lhs, const self &rhs) {
    return lhs += rhs;
  }
  constexpr friend self operator-(self lhs, const self &rhs) {
    return lhs -= rhs;
  }
  constexpr friend self operator*(self lhs, const self &rhs) {
    return lhs *= rhs;
  }
  constexpr friend self operator/(self lhs, const self &rhs) {
    return lhs /= rhs;
  }
  constexpr friend bool operator==(const self &lhs, const self &rhs) {
    return lhs.v_ == rhs.v_;
  }
  constexpr friend bool operator!=(const self &lhs, const self &rhs) {
    return lhs.v_ != rhs.v_;
  }
};
}  // namespace MODINT
using MODINT::DyMint;
using MODINT::Mint;
using mint1e9a7 = Mint<1000000007>;
namespace std {
template <uint32_t MOD>
uint32_t abs(Mint<MOD> x) {
  return x.data();
}
template <ptrdiff_t ID>
uint32_t abs(DyMint<ID> x) {
  return x.data();
}
}  // namespace std
template <class Tp, class Iszero_t = std::function<bool(Tp)>>
class matrix {
#define ASSERTT_(expr, text) \
  if (!(expr)) throw std::runtime_error(text);
#define ASSERT_(expr) ASSERTT_(expr, #expr)
  using self = matrix<Tp, Iszero_t>;

protected:
  constexpr bool
  gauss_swapr__(size_t &row_, size_t row_pre_, size_t col_, size_t row_end) {
    row_ = row_pre_;
    for (size_t j = row_ + 1; j < row_end; ++j)
      if (std::abs((*this)(j, col_)) > std::abs((*this)(row_, col_))) row_ = j;
    if (row_ != row_pre_) {
      swap_row(row_, row_pre_);
      return true;
    }
    return false;
  }

protected:
  size_t r_sz, c_sz;
  Iszero_t iszero;
  std::valarray<Tp> data;

public:
  matrix(size_t row, size_t col, Iszero_t iszero_func, const Tp &val = Tp{})
    : r_sz(row), c_sz(col), iszero(iszero_func), data(val, row * col) {
    ASSERT_(row > 0 && col > 0);
  }
  matrix(size_t row,
         size_t col,
         Iszero_t iszero_func,
         const std::valarray<Tp> &data_)
    : r_sz(row), c_sz(col), iszero(iszero_func), data(data_) {
    ASSERT_(row > 0 && col > 0);
  }
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
    name(para1_t para1) __VA_ARGS__ std::valarray<Tp> name##_varray(           \
      para1_t para1) const __VA_ARGS__
  INVOKES_SLICE__(row, size_t, r, {
    return data[std::slice(r * col_size(), col_size(), 1)];
  })
  INVOKES_SLICE__(col, size_t, c, {
    return data[std::slice(c, row_size(), col_size())];
  })
  INVOKES_SLICE__(diag_cycle, ptrdiff_t, d, {
    return data[d >= 0 ?
                  std::slice(d, row_size(), col_size() + 1) :
                  std::slice(-d * row_size(), row_size(), col_size() + 1)];
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
#define OPB__(op)                                                              \
  friend matrix<bool> operator op(const self & lhs, const Tp & val) {          \
    return matrix<bool>(lhs.row_size(), lhs.col_size(), lhs.data op val);      \
  }                                                                            \
  friend matrix<bool> operator op(const self & lhs, const self & rhs) {        \
    ASSERT_(lhs.row_size() == rhs.row_size() &&                                \
            lhs.col_size() == rhs.col_size());                                 \
    return matrix<bool>(lhs.row_size(), lhs.col_size(), lhs.data op rhs.data); \
  }
  OPB__(==)
  OPB__(!=)
  OPB__(<)
  OPB__(<=)
  OPB__(>)
  OPB__(>=)
#undef OPB__
#define OP__(op)                                                              \
  friend self operator op(self lhs, const Tp &val) { return lhs op## = val; } \
  self &operator op##=(const Tp & val) {                                      \
    data op## = val;                                                          \
    return *this;                                                             \
  }                                                                           \
  friend self operator op(self lhs, const self &rhs) {                        \
    return lhs op## = rhs;                                                    \
  }                                                                           \
  self &operator op##=(const self & rhs) {                                    \
    ASSERT_(row_size() == rhs.row_size() && col_size() == rhs.col_size());    \
    data op## = rhs.data;                                                     \
    return *this;                                                             \
  }
  OP__(+)
  OP__(-)
  OP__(%)
  OP__(&)
  OP__(^)
  OP__(<<)
  OP__(>>)
#undef OP__
#define OPF__(op, ...)                                                        \
  friend self operator op(self lhs, const Tp &val) { return lhs op## = val; } \
  self &operator op##=(const Tp & val) {                                      \
    data op## = val;                                                          \
    return *this;                                                             \
  }                                                                           \
  friend self operator op(const self &lhs, const self &rhs)                   \
    __VA_ARGS__ self &operator op##=(const self &rhs) {                       \
    return *this = *this op rhs;                                              \
  }
  OPF__(*, {
    ASSERT_(lhs.col_size() == rhs.row_size());
    self ret(lhs.row_size(), rhs.col_size(), lhs.iszero, Tp{});
    for (size_t i = 0; i < ret.row_size(); ++i) {
      auto &&r_ = lhs.row(i);
      for (size_t j = 0; j < ret.col_size(); ++j)
        ret(i, j) = (r_ * rhs.col(j)).sum();
    }
    return ret;
  })
  OPF__(/, { return lhs * rhs.inverse(); })
  OPF__(|, {
    ASSERT_(lhs.row_size() == lhs.col_size() &&
            rhs.row_size() == lhs.row_size());
    self tmp_ = merge_lr(lhs, rhs);
    ASSERTT_(std::abs(tmp_.do_gauss()) == lhs.row_size(), "Inverse not exist");
    for (size_t i = 0; i < lhs.row_size(); ++i)
      tmp_
        .data[std::slice(i * (lhs.col_size() + rhs.col_size()) + lhs.col_size(),
                         rhs.col_size(),
                         1)] /= std::valarray<Tp>(tmp_(i, i), rhs.col_size());
    return tmp_.submatrix(
      0, rhs.row_size(), lhs.col_size(), lhs.col_size() + rhs.col_size());
  })
#undef OPF__
  friend self merge_ud(const self &lhs, const self &rhs) {
    ASSERT_(lhs.col_size() == rhs.col_size());
    self ret(lhs.row_size() + rhs.row_size(), lhs.col_size(), Tp{}, lhs.iszero);
    ret.data[std::slice(0, lhs.row_size() * lhs.col_size(), 1)] = lhs.view();
    ret.data[std::slice(
      lhs.row_size() * lhs.col_size(), rhs.row_size() * rhs.col_size(), 1)] =
      rhs.view();
    return ret;
  }
  friend self merge_lr(const self &lhs, const self &rhs) {
    ASSERT_(lhs.row_size() == rhs.row_size());
    self ret(lhs.row_size(), lhs.col_size() + rhs.col_size(), Tp{}, lhs.iszero);
    ret.data[std::gslice(
      0, {lhs.row_size(), lhs.col_size()}, {ret.col_size(), 1})] = lhs.view();
    ret.data[std::gslice(
      lhs.col_size(), {rhs.row_size(), rhs.col_size()}, {ret.col_size(), 1})] =
      rhs.view();
    return ret;
  }
  constexpr void swap_row(size_t r1, size_t r2) {
    if (r1 == r2) return;
    std::valarray<Tp> __ = row(r1);
    row(r1) = row(r2);
    row(r2) = __;
  }
  constexpr void swap_col(size_t c1, size_t c2) {
    if (c1 == c2) return;
    std::valarray<Tp> __ = col(c1);
    col(c1) = col(c2);
    col(c2) = __;
  }
  constexpr void swap_diag_cycle(size_t d1, size_t d2) {
    if (d1 == d2) return;
    std::valarray<Tp> __ = diag_cycle(d1);
    diag_cycle(d1) = diag_cycle(d2);
    diag_cycle(d2) = __;
  }
  virtual int64_t
  do_gauss_range(size_t row_start, size_t row_end, bool clear_all = true) {
    ASSERT_(row_start < row_end && row_end <= row_size());
    int64_t rk = 0;
    bool neg = false;
    for (size_t i = row_start, now_row; i < std::min(row_end, col_size());
         ++i) {
      neg ^= gauss_swapr__(now_row, rk, i, row_end);
      if (iszero((*this)(rk, i))) continue;
      std::valarray<Tp> tmp_ =
        data[std::slice(rk * col_size() + i + 1, col_size() - i - 1, 1)];
      for (int64_t j = clear_all ? 0 : rk + 1; j < (int64_t)row_end; ++j) {
        if (j == rk || iszero((*this)(j, i))) continue;
        Tp &&_ = (*this)(j, i) / (*this)(rk, i);
        (*this)(j, i) = 0;
        data[std::slice(j * col_size() + i + 1, col_size() - i - 1, 1)] -=
          tmp_ * _;
      }
      ++rk;
    }
    return neg ? -rk : rk;
  }
  int64_t do_gauss(bool clear_all = true) {
    return do_gauss_range(0, std::min(row_size(), col_size()), clear_all);
  }
  self transpose() const {
    self ret(col_size(), row_size(), iszero, Tp{});
    for (size_t i = 0; i < row_size(); ++i) ret.col(i) = row(i);
    return ret;
  }
  self inverse() const {
    ASSERT_(row_size() == col_size());
    self ret(row_size(), col_size(), iszero, Tp{});
    ret.diag_cycle(0) = 1;
    ASSERTT_(std::abs((ret = merge_lr(*this, ret)).do_gauss()) == row_size(),
             "Inverse not exist");
    for (size_t i = 0; i < row_size(); ++i)
      ret.data[std::slice((i * 2 + 1) * col_size(), col_size(), 1)] /=
        std::valarray<Tp>(ret(i, i), col_size());
    ret = ret.submatrix(0, row_size(), col_size(), col_size() * 2);
    return ret;
  }
  Tp trace() const { return diag_cycle(0).sum(); }
  size_t rank() const { return std::abs(self(*this).do_gauss(false)); }
  Tp det() const {
    ASSERT_(row_size() == col_size());
    self tmp_(*this);
    ptrdiff_t rk_ = tmp_.do_gauss(false);
    if (std::abs(rk_) != row_size()) return Tp{};
    Tp ret = tmp_(0, 0);
    for (size_t i = 1; i < row_size(); ++i) ret *= tmp_(i, i);
    return rk_ < 0 ? -ret : ret;
  }
  friend self pow(self mat, size_t b) {
    self res(mat.row_size(), mat.col_size(), mat.iszero, Tp{});
    res.diag_cycle(0) = 1;
    for (; b; b >>= 1, mat *= mat)
      if (b & 1) res *= mat;
    return res;
  }
};
template <class Tp>
class matrix_int: public matrix<Tp> {
  static_assert(std::is_integral<Tp>::value);
  using self = matrix_int<Tp>;
  using base = matrix<Tp>;

private:
  static constexpr auto isz__ = [](Tp const &x) { return x == 0; };

public:
  matrix_int(size_t row, size_t col, const Tp &val = Tp{})
    : base(row, col, isz__, val) {}
  matrix_int(size_t row, size_t col, const std::valarray<Tp> &data_)
    : base(row, col, isz__, data_) {}
  int64_t do_gauss_range(size_t row_start,
                         size_t row_end,
                         bool clear_all = true) override {
    ASSERT_(row_start < row_end && row_end <= this->row_size());
    int64_t rk = 0;
    bool neg = false;
    for (size_t i = row_start, now_row; i < std::min(row_end, this->col_size());
         ++i) {
      neg ^= this->gauss_swapr__(now_row, rk, i, row_end);
      if (this->iszero((*this)(rk, i))) continue;
      for (int64_t j = clear_all ? 0 : rk; j < (int64_t)row_end; ++j) {
        if (j == rk || this->iszero((*this)(j, i))) continue;
        while (true) {
          Tp _ = (*this)(j, i) / (*this)(rk, i);
          this->row(j) -= _ * this->row_varray(rk);
          if (!this->iszero((*this)(j, i))) {
            this->swap_row(rk, j);
            neg ^= 1;
          } else break;
        }
      }
      ++rk;
    }
    return neg ? -rk : rk;
  }
};
class matrix_bool: public matrix<bool> {
  using self = matrix_bool;
  using base = matrix<bool>;

private:
  static constexpr auto isz__ = [](bool x) { return !x; };

public:
  matrix_bool(size_t row, size_t col, bool val = false)
    : base(row, col, isz__, val) {}
  matrix_bool(size_t row, size_t col, const std::valarray<bool> &data_)
    : base(row, col, isz__, data_) {}
  int64_t do_gauss_range(size_t row_start,
                         size_t row_end,
                         bool clear_all = true) override {
    ASSERT_(row_start < row_end && row_end <= this->row_size());
    int64_t rk = 0;
    bool neg = false;
    for (size_t i = row_start, now_row; i < std::min(row_end, this->col_size());
         ++i) {
      if (!(*this)(rk, i)) {
        for (size_t j = rk + 1; j < row_end; ++j)
          if ((*this)(j, i)) {
            this->swap_row(j, rk);
            neg ^= true;
            break;
          }
        if (!(*this)(rk, i)) continue;
      }
      std::valarray<bool> tmp_ = data[std::slice(
        rk * this->col_size() + i + 1, this->col_size() - i - 1, 1)];
      for (int64_t j = clear_all ? 0 : rk + 1; j < (int64_t)row_end; ++j) {
        if (j == rk || iszero((*this)(j, i))) continue;
        (*this)(j, i) = false;
        data[std::slice(
          j * this->col_size() + i + 1, this->col_size() - i - 1, 1)] ^= tmp_;
      }
      ++rk;
    }
    return neg ? -rk : rk;
  }
};
#undef ASSERT_
#undef ASSERTT_
using mint = mint1e9a7;
auto solve([[maybe_unused]] int t_ = 0) -> void {
  read_var_(int, n);
  read_var_(int, m);
  read_var_(int, t);
  matrix<mint> mat(n, n, [](mint const &x) { return x == 0; }, 0);
  for_(i, 1, m, u, v, w) {
    cin >> u >> v >> w;
    --u;
    --v;
    mat(u, v) -= w;
    mat(v, v) += w;
    if (t) continue;
    mat(v, u) -= w;
    mat(u, u) += w;
  }
  cout << mat.submatrix(1, n, 1, n).det();
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  solve(i_);
  return 0;
}
