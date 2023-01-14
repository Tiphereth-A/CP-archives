#include <bits/stdc++.h>
using namespace std;
namespace miller_rabin {
constexpr int64_t mul_mod(int64_t a, int64_t b, const int64_t &mod) {
  int64_t d = floor(1.0l * a * b / mod + 0.5l), ret = a * b - d * mod;
  return ret < 0 ? ret + mod : ret;
}
constexpr int64_t pow_mod(int64_t a, int64_t b, const int64_t &mod) {
  int64_t res(1);
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
const int N = 2e6 + 5, P = 1.5e5 + 5;
bool vis[N], isp[N];
int prime[P], cnt_prime;
int mp[N];
void init_prime(const int &n = N - 1) {
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) isp[prime[++cnt_prime] = i] = 1;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
  for (int i = 3, j = 1; i <= n; ++i) {
    mp[i] = prime[j];
    if (isp[i]) ++j;
  }
}
uint64_t minp(uint64_t n) {
  if (n < N) return mp[n];
  for (uint64_t n_ = n - 1;; --n_)
    if (is_prime(n_)) return n_;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  init_prime();
  int n;
  cin >> n;
  for (uint64_t x; n; --n) {
    cin >> x;
    cout << minp(x) << '\n';
  }
  return 0;
}
