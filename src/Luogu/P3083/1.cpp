#include <cmath>
#include <cstdint>
#include <iostream>
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
const i32 MAXN = (1 << 21) + 5;
template <class T>
constexpr T qpow(T a, u64 b) {
  T x{1};
  for (; b; a *= a, b >>= 1)
    if (b & 1) x *= a;
  return x;
}
template <class Tp, i64 K = -1>
struct gint {
  using self = gint<Tp, K>;

private:
  Tp r_, i_;

public:
  constexpr gint(Tp const &real = Tp(), Tp const &imag = Tp())
    : r_(real), i_(imag) {}
  constexpr gint(gint const &) = default;
  constexpr gint &operator=(Tp x) {
    r_ = x;
    i_ = Tp();
    return *this;
  }
  constexpr gint &operator=(gint const &) = default;
  constexpr Tp real() const { return r_; }
  constexpr Tp imag() const { return i_; }
  constexpr void real(Tp x) { r_ = x; }
  constexpr void imag(Tp x) { i_ = x; }
  constexpr self conj() const { return self{r_, -i_}; }
  constexpr Tp norm() const { return r_ * r_ + i_ * i_ * K; }
  constexpr self &operator+=(Tp const &x) {
    r_ += x;
    return *this;
  }
  constexpr self &operator-=(Tp const &x) {
    r_ -= x;
    return *this;
  }
  constexpr self &operator*=(Tp const &x) {
    r_ *= x;
    i_ *= x;
    return *this;
  }
  constexpr self &operator/=(Tp const &x) {
    r_ /= x;
    i_ /= x;
    return *this;
  }
  constexpr self &operator+=(self const &x) {
    r_ += x.real();
    i_ += x.imag();
    return *this;
  }
  constexpr self &operator-=(self const &x) {
    r_ -= x.real();
    i_ -= x.imag();
    return *this;
  }
  constexpr self &operator*=(self const &x) {
    const Tp _ = r_ * x.real() + i_ * x.imag() * K;
    i_ = r_ * x.imag() + i_ * x.real();
    r_ = _;
    return *this;
  }
  constexpr self &operator/=(self const &x) {
    const Tp _ = r_ * x.real() - i_ * x.imag() * K;
    const Tp n_ = x.norm();
    i_ = (i_ * x.real() - r_ * x.imag()) / n_;
    r_ = _ / n_;
    return *this;
  }
  constexpr friend self operator+(self x, Tp const &y) { return x += y; }
  constexpr friend self operator-(self x, Tp const &y) { return x -= y; }
  constexpr friend self operator*(self x, Tp const &y) { return x *= y; }
  constexpr friend self operator/(self x, Tp const &y) { return x /= y; }
  constexpr friend self operator+(self x, self const &y) { return x += y; }
  constexpr friend self operator-(self x, self const &y) { return x -= y; }
  constexpr friend self operator*(self x, self const &y) { return x *= y; }
  constexpr friend self operator/(self x, self const &y) { return x /= y; }
};
template <u32 P>
struct modint {
  static_assert(P >= 1);

private:
  using self = modint<P>;
  u32 v_;

public:
  static constexpr u32 mod() { return P; }
  constexpr modint(): v_(0) {}
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_signed<T>::value> * = nullptr>
  constexpr modint(T v): modint() {
    i64 x = (i64)(v % (i64)mod());
    v_ = (u32)(x + (x < 0 ? mod() : 0));
  }
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_unsigned<T>::value> * = nullptr>
  constexpr modint(T v): v_((u32)(v % mod())) {}
  friend std::istream &operator>>(std::istream &is, self &x) {
    i64 xx;
    is >> xx;
    xx %= mod();
    x.v_ = (u32)(xx + (xx < 0 ? mod() : 0));
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const self &x) {
    return os << x.v_;
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
    v_ = (u32)((u64)v_ * rhs.v_ % mod());
    return *this;
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
};
namespace CNTT {
const u32 P = 999292927;
const gint<modint<P>> OMEGA{1, 8};
using Zp = modint<P>;
using Zpi = gint<Zp>;
u32 limit = 1;
template <i32 type>
void trans(Zpi *a) {
  static_assert(type == 1 || type == -1);
  for (u32 i = 0, j = 0;;) {
    if (i < j) std::swap(a[i], a[j]);
    if (++i == limit) break;
    for (u32 k = limit >> 1; ((j ^= k) & k) == 0; k >>= 1);
  }
  for (u32 mid = 1; mid < limit; mid <<= 1) {
    Zpi Wn = qpow(OMEGA, ((u64)P * P - 1) / 2 / mid);
    if constexpr (type == -1) Wn = qpow(Wn, (u64)P * P - 2);
    for (u32 R = mid << 1, j = 0; j < limit; j += R) {
      Zpi w{1};
      for (u32 k = 0; k < mid; k++, w *= Wn) {
        Zpi x = a[j + k], y = w * a[j + mid + k];
        a[j + k] = x + y;
        a[j + mid + k] = x - y;
      }
    }
  }
}
void init(u32 len) {
  if (len + 1 > limit) limit = (u32)1 << (u32)ceil(log2(len + 1));
}
void conv(Zpi *a, Zpi *result) {
  trans<1>(a);
  for (u32 i = 0; i <= limit; i++) result[i] = a[i] * a[i];
  trans<-1>(result);
  const Zp inv = qpow(Zp{limit} * 2, P - 2);
  for (u32 i = 0; i <= limit; i++) result[i].imag(result[i].imag() * inv);
}
}  // namespace CNTT
using CNTT::Zpi, CNTT::init, CNTT::conv;
Zpi a[MAXN];
using std::cin, std::cout;
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  u32 N, M;
  cin >> N >> M;
  for (u32 i = 0, _; i <= N; i++) {
    cin >> _;
    a[i].real(_);
  }
  for (u32 i = 0, _; i <= M; i++) {
    cin >> _;
    a[i].imag(_);
  }
  init(N + M);
  conv(a, a);
  for (u32 i = 0; i <= N + M; i++) cout << a[i].imag() << " \n"[i == N + M];
  return 0;
}
