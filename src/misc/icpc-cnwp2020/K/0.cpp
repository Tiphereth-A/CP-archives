#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const int INF = 0x3f3f3f3f;
const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
int _w, _t;
const int N = 1e5 + 5;
int n, a[N];
ll ans;
ll sum(int u) { return 1LL * u * (u + 1) / 2; }
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  a[n + 1] = INF;
  for (int i = 1, ls = 1; i <= n + 1; i++)
    if (a[i] != a[ls]) {
      ans += sum(i - ls);
      ls = i;
    }
  printf("%lld\n", ans);
  return 0;
}
