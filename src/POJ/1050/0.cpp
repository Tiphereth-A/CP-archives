#include <iostream>
using namespace std;
int a[105][105], c[105][105];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) cin >> a[i][j];
  int ans = -1;
  for (int i = 1; i <= n; ++i)
    for (int j = i; j <= n; ++j) {
      int max = -1, sum = 0;
      for (int k = 1; k <= n; ++k) {
        if ((sum += (c[k][j] = c[k][j - 1] + a[k][j]) - c[k][i - 1]) < 0)
          sum = 0;
        if (sum > max) max = sum;
      }
      if (max > ans) ans = max;
    }
  cout << ans;
  return 0;
}
