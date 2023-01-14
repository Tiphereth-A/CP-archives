#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N];
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    a[n + 1] = INT_MAX;
    int now = a[1];
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
      if (a[i] < a[i + 1]) {
        ans += now - a[i];
        now = a[i + 1];
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
