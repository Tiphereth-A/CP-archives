#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
namespace miller_rabin {
constexpr int64_t mul_mod(int64_t a, int64_t b, const int64_t &mod) {
  i64 d = floor(1.0l * a * b / mod + 0.5l), ret = a * b - d * mod;
  return ret < 0 ? ret + mod : ret;
}
constexpr int64_t pow_mod(int64_t a, int64_t b, const int64_t &mod) {
  i64 res(1);
  for (; b; b >>= 1, a = mul_mod(a, a, mod))
    if (b & 1) res = mul_mod(res, a, mod);
  return res;
}
using data_t = uint64_t;
using udata_t = std::make_unsigned_t<data_t>;
constexpr udata_t bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
constexpr bool is_prime(udata_t n) {
  if (n <= 1) return false;
  for (udata_t a : bases)
    if (n == a) return true;
  if (n % 2 == 0) return false;
  udata_t d = n - 1;
  while (d % 2 == 0) d /= 2;
  for (udata_t a : bases) {
    udata_t t = d, y = pow_mod(a, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = mul_mod(y, y, n);
      t <<= 1;
    }
    if (y != n - 1 && t % 2 == 0) return false;
  }
  return true;
}
}  // namespace miller_rabin
using miller_rabin::is_prime;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  for (uint64_t x; n; --n) {
    cin >> x;
    cout << (is_prime(x) ? "YES" : "NO") << '\n';
  }
  return 0;
}
