#include <bits/stdc++.h>
using namespace std;
template <typename Tp = int64_t,
          typename Up = uint64_t,
          std::enable_if_t<
            (std::is_same_v<typename std::remove_cv<Tp>::type, int64_t> ||
             std::is_same_v<typename std::remove_cv<Tp>::type, uint64_t>) &&
            std::is_unsigned_v<Up>> * = nullptr>
constexpr Tp mul_mod(Tp a, Tp b, const Up &mod) {
  Tp d = floorl(1.0l * a * b / mod + 0.5l), ret = a * b - d * mod;
  return ret < 0 ? ret + mod : ret;
}
template <typename Tp,
          typename Up,
          std::enable_if_t<
            std::is_integral_v<Tp> &&
            !(std::is_same_v<typename std::remove_cv<Tp>::type, int64_t> ||
              std::is_same_v<typename std::remove_cv<Tp>::type, uint64_t>) &&
            std::is_unsigned_v<Up>> * = nullptr>
constexpr Tp mul_mod(Tp a, Tp b, const Up &mod) {
  return ((int64_t)a * b) % mod;
}
template <typename Tp,
          typename Up,
          std::enable_if_t<!std::is_integral_v<Tp> && std::is_unsigned_v<Up>>
            * = nullptr>
constexpr Tp mul_mod(Tp a, Tp b, const Up &mod) {
  return a * b % mod;
}
namespace my_template {
constexpr int32_t legendre_symbol(uint64_t a, uint64_t p) noexcept {
  if (a == 0 || std::gcd(a, p) != 1) return 0;
  if (a == 1) return 1;
  int32_t s = 1, _ctz = 0;
  while (a > 1) {
    _ctz = __builtin_ctzll(a);
    if (((p - 1) & 7) && ((p + 1) & 7) && (_ctz & 1)) s = -s;
    if ((a >>= _ctz) == 1) break;
    if ((((p - 1) & 7) * (a - 1)) & 7) s = -s;
    a ^= p ^= a ^= p %= a;
  }
  return s;
}
namespace quad_r {
using data_type = int64_t;
using unsigned_data_t = std::make_unsigned_t<data_type>;
std::default_random_engine e(time(nullptr));
std::optional<data_type> quad_residue(const data_type &n,
                                      const unsigned_data_t &p) {
  if (n == 0 || n == 1 || n == p - 1) return n;
  if (legendre_symbol(n, p) != 1) return std::nullopt;
  std::uniform_int_distribution<unsigned_data_t> u(1, p - 1);
  data_type a = u(e);
  while (legendre_symbol((mul_mod(a, a, p) + (p - n)) % p, p) == 1) a = u(e);
  struct _gsint {
    using self = _gsint;
    data_type real, imag;
    const data_type i_sqr;
    const unsigned_data_t mod;
    explicit constexpr _gsint(const data_type &_r = data_type(),
                              const data_type &_i = data_type(),
                              const data_type &_ii = data_type(),
                              const unsigned_data_t &_p = unsigned_data_t(1))
      : real(_r), imag(_i), i_sqr(_ii), mod(_p) {}
    constexpr _gsint(const _gsint &) = default;
    constexpr self &operator*=(self rhs) {
      const data_type _r = real, _i = imag;
      real = (mul_mod(_r, rhs.real, mod) +
              mul_mod(mul_mod(i_sqr, _i, mod), rhs.imag, mod)) %
             mod;
      imag = (mul_mod(_i, rhs.real, mod) + mul_mod(_r, rhs.imag, mod)) % mod;
      return *this;
    }
  };
  return [](_gsint a, unsigned_data_t b) {
    _gsint res{1, 0, a.i_sqr, a.mod};
    for (; b; b >>= 1, a *= a)
      if (b & 1) res *= a;
    return res.real;
  }(_gsint{a, 1, (mul_mod(a, a, p) + (p - n)) % p, p}, (p + 1) / 2);
}
}  // namespace quad_r
using quad_r::quad_residue;
}  // namespace my_template
void solve() {
  int64_t n, p;
  cin >> n >> p;
  if (auto _ = my_template::quad_residue(n, p); !_) cout << "Hola!\n";
  else {
    int64_t a = _.value(), b = (p - _.value()) % p;
    if (b < a) swap(a, b);
    cout << a;
    if (a != b) cout << ' ' << b;
    cout << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
