#include <bits/stdc++.h>
#define _for(num, end) for (int i##num = 1; i##num <= end; ++i##num)
const int N = 130;
int n, sum[N][N], ans = 0x80000000;
int max(int a, int b) { return a > b ? a : b; }
int main() {
  scanf("%d", &n);
  for (int a, i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      scanf("%d", &a);
      sum[i][j] = a + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    }
  _for(1, n)
    _for(2, n)
      _for(3, i1)
        _for(4, i2)
          ans = max(ans,
                    sum[i1][i2] - sum[i3 - 1][i2] - sum[i1][i4 - 1] +
                      sum[i3 - 1][i4 - 1]);
  printf("%d", ans);
  return 0;
}
