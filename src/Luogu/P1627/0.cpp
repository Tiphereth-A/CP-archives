#include <bits/stdc++.h>
#define MAXN 100005
typedef long long ll;
ll n, b, num[2][MAXN << 1], ans;
int main() {
  scanf("%lld%lld", &n, &b);
  num[0][n] = 1;
  for (ll i = 0, a, s = n, f = 0; i < n; i++) {
    scanf("%lld", &a);
    if (a != b) s += a > b ? 1 : -1;
    num[f |= a == b][s]++;
  }
  for (ll i = 0; i < (n << 1); i++, ans += num[0][i] * num[1][i]);
  printf("%lld\n", ans);
  return 0;
}
