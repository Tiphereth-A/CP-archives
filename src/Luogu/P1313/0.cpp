#include <bits/stdc++.h>
typedef long long ll;
const int MAXN = 5000 + 10;
const int mod = 10007;
int c[MAXN][MAXN];
using namespace std;
int power(ll x, int k) {
  long long ans = 1;
  while (k) {
    if (k & 1) ans = ans * x % mod;
    x = x * x % mod;
    k >>= 1;
  }
  return ans;
}
int main() {
  int a, b, k, m, n;
  cin >> a >> b >> k >> m >> n;
  for (int i = 0; i <= k; i++) c[i][0] = c[i][i] = 1;
  for (int i = 1; i <= k; i++)
    for (int j = 1; j < i; j++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
  ll ans;
  ans = power(a, m) * power(b, n) % mod * c[k][m] % mod;
  printf("%d", ans);
  return 0;
}
