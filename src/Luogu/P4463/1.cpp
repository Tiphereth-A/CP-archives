#include <bits/stdc++.h>
using ll = long long;
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
using vvc = std::vector<std::vector<Tp>>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
template <typename... Ts>
void dec(Ts &...x) {
  ((--x), ...);
}
template <typename... Ts>
void inc(Ts &...x) {
  ((++x), ...);
}
#define(std::cerr << __LINE__ << ' ' << __FUNCTION__ << std::endl)
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
  static inline Barrett_ bt_;

public:
  constexpr static uint32_t mod() { return bt_.umod(); }
  constexpr static void set_mod(uint32_t m) {
    assert(1 <= m);
    bt_ = Barrett_(m);
  }
  constexpr static self raw(uint32_t v) {
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
using mint = MODINT::DyMint<>;
template <class T>
class NewtonInterp {
  std::vector<std::pair<T, T>> points;
  std::vector<std::vector<T>> diffs;
  std::vector<T> base;
  std::vector<T> fit;

public:
  explicit NewtonInterp() = default;
  NewtonInterp &insert(T const &x, T const &y) {
    points.emplace_back(x, y);
    size_t n = points.size();
    if (n == 1) {
      base.push_back(1);
    } else {
      size_t m = base.size();
      base.push_back(0);
      for (size_t i = m; i; --i) base[i] = base[i - 1];
      base[0] = 0;
      for (size_t i = 0; i < m; ++i)
        base[i] = base[i] - points[n - 2].first * base[i + 1];
    }
    diffs.emplace_back(points.size());
    diffs[n - 1][n - 1] = y;
    if (n > 1)
      for (size_t i = n - 2; ~i; --i)
        diffs[n - 1][i] = (diffs[n - 2][i] - diffs[n - 1][i + 1]) /
                          (points[i].first - points[n - 1].first);
    fit.push_back(0);
    for (size_t i = 0; i < n; ++i) fit[i] = fit[i] + diffs[n - 1][0] * base[i];
    return *this;
  }
  std::vector<T> coeffs() const { return fit; }
  T evaluate(T const &x) {
    T ans{};
    for (auto it = fit.rbegin(); it != fit.rend(); ++it) ans = ans * x + *it;
    return ans;
  }
};
void solve(int t_ = 0) {
  int k, n, p;
  cin >> k >> n >> p;
  mint::set_mod(p);
  vvc<mint> dp(n + 1, vc<mint>(n * 2 + 2));
  fill(dp[0].begin(), dp[0].end(), 1);
  for_(i, 1, n)
    for_(j, i, n * 2 + 1) dp[i][j] = dp[i - 1][j - 1] * j + dp[i][j - 1];
  mint fact = 1;
  for_(i, 1, n) fact *= i;
  NewtonInterp<mint> ip;
  for_(i, 1, n * 2 + 1) ip.insert(i, dp[n][i]);
  cout << ip.evaluate(k) * fact;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
