#include <bits/stdc++.h>
typedef long long ll;
const int MAXN = 40000 + 10;
using namespace std;
ll e[MAXN];
int main() {
  int n;
  scanf("%d", &n);
  e[1] = 1;
  for (int i = 2; i < n; i++) e[i] = i;
  for (int i = 2; i < n; i++)
    if (e[i] == i)
      for (int j = i; j < n; j += i) e[j] = e[j] / i * (i - 1);
  ll ans = 0;
  for (int i = 2; i <= n - 1; i++) ans += e[i];
  ans <<= 1;
  ans += 3;
  if (n == 1) ans = 0;
  printf("%lld", ans);
  return 0;
}
