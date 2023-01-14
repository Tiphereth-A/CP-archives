#include <bits/stdc++.h>
using namespace std;
int64_t b[1005];
int main() {
  int n;
  scanf("%d", &n);
  if (((1 + n) * n / 2) & 1) puts("0");
  else {
    for (int i = 0; i < (1 << (n / 2)); ++i) {
      int cur = 0;
      for (int j = 0; (i >> j) > 0; ++j)
        if ((i >> j) & 1) cur += (j + 1);
      b[cur]++;
    }
    int64_t ans = 0;
    for (int i = 0; i < (1 << (n - n / 2)); ++i) {
      int cur = 0;
      for (int j = 0; (i >> j) > 0; ++j)
        if ((i >> j) & 1) cur += j + n / 2 + 1;
      if ((1 + n) * n / 4 >= cur) ans += b[(1 + n) * n / 4 - cur];
    }
    printf("%lld\n", ans / 2);
  }
  return 0;
}
