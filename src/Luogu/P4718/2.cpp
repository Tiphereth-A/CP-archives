#include <bits/stdc++.h>
using namespace std;
namespace Pollard_rho {
using data_type = uint64_t;
using signed_data_t = make_signed_t<data_type>;
using unsigned_data_t = make_unsigned_t<data_type>;
constexpr signed_data_t
mul_mod(signed_data_t a, signed_data_t b, unsigned_data_t mod) {
  signed_data_t d = floor(1.0l * a * b / mod + 0.5l), ret = a * b - d * mod;
  return ret < 0 ? ret + mod : ret;
}
constexpr data_type
pow_mod(unsigned_data_t a, unsigned_data_t b, const unsigned_data_t &mod) {
  data_type res(1);
  a %= mod;
  for (; b; b >>= 1, a = mul_mod(a, a, mod))
    if (b & 1) res = mul_mod(res, a, mod);
  return res;
}
namespace Primetest_miller_rabin {
constexpr unsigned_data_t bases[] = {
  2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
constexpr bool is_prime(unsigned_data_t n) {
  if (n <= 1) return false;
  for (unsigned_data_t a : bases)
    if (n == a) return true;
  if (n % 2 == 0) return false;
  unsigned_data_t d = n - 1;
  while (d % 2 == 0) d /= 2;
  for (unsigned_data_t a : bases) {
    unsigned_data_t t = d, y = pow_mod(a, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = mul_mod(y, y, n);
      t <<= 1;
    }
    if (y != n - 1 && t % 2 == 0) return false;
  }
  return true;
}
}  // namespace Primetest_miller_rabin
using Primetest_miller_rabin::is_prime;
default_random_engine e(time(nullptr));
uniform_int_distribution<data_type> u;
#define Rand(x) (u(e) % (x) + 1)
data_type pollard_rho(const data_type x, const data_type y) {
  data_type t = 0, k = 1;
  signed_data_t v0 = Rand(x - 1), v = v0;
  data_type d, s = 1;
  while (true) {
    v = (mul_mod(v, v, x) + y) % x;
    s = mul_mod(s, abs(v - v0), x);
    if (!(v ^ v0) || !s) return x;
    if (++t == k) {
      if ((d = gcd(s, x)) ^ 1) return d;
      v0 = v, k <<= 1;
    }
  }
}
void resolve(data_type x, data_type &ans) {
  if (!(x ^ 1) || x <= ans) return;
  if (is_prime(x)) {
    if (ans < x) ans = x;
    return;
  }
  data_type y = x;
  while ((y = pollard_rho(x, Rand(x))) == x);
  while (x % y == 0) x /= y;
  resolve(x, ans);
  resolve(y, ans);
}
data_type get_max_prime_divisor(data_type x) {
  data_type ans = 0;
  resolve(x, ans);
  return ans;
}
}  // namespace Pollard_rho
using Pollard_rho::get_max_prime_divisor;
using Pollard_rho::is_prime;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int kase;
  cin >> kase;
  while (kase--) {
    uint64_t n;
    cin >> n;
    if (is_prime(n)) cout << "Prime\n";
    else cout << get_max_prime_divisor(n) << '\n';
  }
  return 0;
}
