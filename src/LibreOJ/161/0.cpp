#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int N = 5e6 + 5;
int n;
int a[N];
void exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return;
  }
  exgcd(b, a % b, x, y);
  ll z = x;
  x = y;
  y = z - a / b * y;
}
ll inv(int n) {
  ll x, y;
  exgcd(n, mod, x, y);
  return (x + mod) % mod;
}
ll pre[N], preinv[N];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  pre[0] = 1;
  for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] * a[i] % mod;
  preinv[n] = inv(pre[n]);
  for (int i = n - 1; i >= 0; i--) preinv[i] = preinv[i + 1] * a[i + 1] % mod;
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ll res = pre[i - 1] * preinv[i] % mod;
    ans = (ans * 998244353 % mod + res) % mod;
  }
  printf("%lld\n", ans);
  return 0;
}
