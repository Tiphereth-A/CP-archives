#include <bits/stdc++.h>
using namespace std;
#define MAXAI 25005
#define MAXN 105
int f[MAXAI];
int a[MAXN];
int main() {
  int i, j, n, T, ans;
  scanf("%d", &T);
  while (T--) {
    memset(f, 0, sizeof(f));
    scanf("%d", &n);
    ans = n;
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    f[0] = 1;
    for (i = 1; i <= n; i++) {
      if (f[a[i]]) {
        ans--;
        continue;
      }
      for (j = a[i]; j <= a[n]; j++) { f[j] = f[j] | f[j - a[i]]; }
    }
    printf("%d\n", ans);
  }
  return 0;
}
