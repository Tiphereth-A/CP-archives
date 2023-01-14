#include <bits/stdc++.h>
using namespace std;
i64 qpow(i64 a, i64 b, i64 mod) {
  i64 res = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) res = res * a % mod;
  return res;
}
i64 phi(i64 n) {
  i64 ans = n;
  for (int i = 2; i <= sqrt(n); ++i)
    if (n % i == 0) {
      ans = ans / i * (i - 1);
      while (n % i == 0) n /= i;
    }
  if (n > 1) ans = ans / n * (n - 1);
  return ans;
}
int main() {
  i64 m, k;
  cin >> m >> k;
  if (__gcd(m, k) > 1) {
    cout << "Let's go Blue Jays!" << endl;
    return 0;
  }
  i64 phim = phi(m);
  i64 ans = INT64_MAX;
  for (i64 i = 1; i <= sqrt(phim); ++i)
    if (phim % i == 0) {
      if (qpow(k, i, m) == 1) {
        ans = min(ans, i);
        break;
      } else if (qpow(k, phim / i, m) == 1) ans = min(ans, phim / i);
    }
  cout << ans;
}
