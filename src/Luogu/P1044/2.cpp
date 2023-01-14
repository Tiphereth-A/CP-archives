#include <bits/stdc++.h>
typedef long long ll;
#define _for(i, l, r) for (ll i = (l); i <= (r); i++)
ll h[20];
int main() {
  ll n;
  scanf("%lld", &n);
  _for(i, 0, n) h[i] = 1;
  _for(i, 1, n)
    _for(j, i + 1, n) h[j] += h[j - 1];
  printf("%lld", h[n]);
  return 0;
}
