#include <iostream>
#include <cstdint>
#include <complex>
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
const i32 MAXN = 1e7 + 10;
template <class T>
constexpr T qpow(T a, u64 b) {
  T x{1};
  for (; b; a *= a, b >>= 1)
    if (b & 1) x *= a;
  return x;
}
namespace MODINT {
template <u32 MOD>
struct Mint {
  static_assert(MOD >= 1);

private:
  using self = Mint<MOD>;
  u32 v_;

public:
  static constexpr u32 mod() { return MOD; }
  constexpr Mint(): v_(0) {}
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_signed<T>::value> * = nullptr>
  constexpr Mint(T v): Mint() {
    i64 x = (i64)(v % (i64)mod());
    v_ = (u32)(x + (x < 0 ? mod() : 0));
  }
  template <class T,
            std::enable_if_t<std::is_integral<T>::value &&
                             std::is_unsigned<T>::value> * = nullptr>
  constexpr Mint(T v): v_((u32)(v % mod())) {}
  constexpr u32 val() const { return v_; }
  constexpr u32 &data() { return v_; }
  constexpr explicit operator u32() const { return val(); }
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
  constexpr friend bool operator==(const self &lhs, const self &rhs) {
    return lhs.v_ == rhs.v_;
  }
  constexpr friend bool operator!=(const self &lhs, const self &rhs) {
    return lhs.v_ != rhs.v_;
  }
};
}  // namespace MODINT
namespace CNTT {
const u32 P = 999292927;
const std::complex<MODINT::Mint<P>> OMEGA{1, 8};
using Zp = MODINT::Mint<P>;
using Zpi = std::complex<Zp>;
i32 r[MAXN];
i32 limit = 1, lb_limit = 0;
template <i32 type>
void trans(Zpi *a) {
  static_assert(type == 1 || type == -1);
  for (i32 i = 0; i < limit; i++)
    if (i < r[i]) std::swap(a[i], a[r[i]]);
  for (i32 mid = 1; mid < limit; mid <<= 1) {
    Zpi Wn = qpow(OMEGA, ((u64)P * P - 1) / mid / 2);
    if constexpr (type == -1) Wn = qpow(Wn, (u64)P * P - 2);
    for (i32 R = mid << 1, j = 0; j < limit; j += R) {
      Zpi w{1};
      for (i32 k = 0; k < mid; k++, w *= Wn) {
        Zpi x = a[j + k], y = w * a[j + mid + k];
        a[j + k] = x + y;
        a[j + mid + k] = x - y;
      }
    }
  }
}
void init(i32 len) {
  while (limit <= len) {
    limit <<= 1;
    lb_limit++;
  }
  for (i32 i = 0; i < limit; i++)
    r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lb_limit - 1));
}
void conv(Zpi *a, Zpi *b, Zpi *result) {
  CNTT::trans<1>(a);
  CNTT::trans<1>(b);
  for (i32 i = 0; i <= CNTT::limit; i++) result[i] = a[i] * b[i];
  CNTT::trans<-1>(result);
  const auto inv = qpow(CNTT::Zp{CNTT::limit}, CNTT::P - 2);
  for (i32 i = 0; i <= CNTT::limit; i++) result[i].real(result[i].real() * inv);
}
}  // namespace CNTT
using CNTT::Zpi, CNTT::init, CNTT::conv;
Zpi a[MAXN], b[MAXN];
using std::cin, std::cout;
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  i32 N, M;
  cin >> N >> M;
  for (i32 i = 0, _; i <= N; i++) {
    cin >> _;
    a[i].real(_);
  }
  for (i32 i = 0, _; i <= M; i++) {
    cin >> _;
    b[i].real(_);
  }
  init(N + M);
  conv(a, b, a);
  for (i32 i = 0; i <= N + M; i++) cout << a[i].real() << " \n"[i == N + M];
  return 0;
}
