#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _rfor(i, r, l, vals...) \
  for (decltype(r - l) i = (r), ##vals; i >= (l); --i)
const int N = 2e6 + 5, P = 1.5e5 + 5;
int prime[P], factor_prime;
int min_prime_factor[N];
void init_prime(const int &n = N - 1) {
  for (int i = 2; i <= n; ++i) {
    if (!min_prime_factor[i]) min_prime_factor[prime[++factor_prime] = i] = i;
    for (int j = 1; j <= factor_prime && i * prime[j] <= n; ++j) {
      min_prime_factor[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) break;
    }
  }
}
i64 qpow(i64 a, i64 b, const i64 &mod) {
  i64 res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int factor[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  i64 n, p;
  cin >> n >> p;
  _for(i, 2, n) factor[i] = -1;
  _for(i, n + 2, 2 * n) factor[i] = 1;
  _rfor(i, 2 * n, 2)
    if (min_prime_factor[i] < i) {
      factor[min_prime_factor[i]] += factor[i];
      factor[i / min_prime_factor[i]] += factor[i];
    }
  i64 ans = 1;
  _rfor(i, 2 * n, 2)
    if (min_prime_factor[i] == i) (ans *= qpow(i, factor[i], p)) %= p;
  cout << ans;
  return 0;
}
