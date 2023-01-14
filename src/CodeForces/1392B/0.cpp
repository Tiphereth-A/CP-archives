#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
i64 a[N];
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n;
    i64 k;
    scanf("%d%lld", &n, &k);
    i64 max_n = LLONG_MIN;
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", a + i);
      max_n = max(max_n, a[i]);
    }
    for (int i = 1; i <= n; ++i) a[i] = max_n - a[i];
    max_n = LLONG_MIN;
    for (int i = 1; i <= n; ++i) max_n = max(max_n, a[i]);
    --k;
    if (k % 2)
      for (int i = 1; i <= n; ++i)
        printf("%lld%c", max_n - a[i], i == n ? '\n' : ' ');
    else
      for (int i = 1; i <= n; ++i) printf("%lld%c", a[i], i == n ? '\n' : ' ');
  }
  return 0;
}
