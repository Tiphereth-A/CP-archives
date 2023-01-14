#include <bits/stdc++.h>
using namespace std;
int f[205][205], a[205];
int main() {
  int n, k;
  cin >> n >> k;
  if (k > 2 * n - 1) {
    cout << '0';
    return 0;
  }
  for (int i = 1; i < n; ++i) a[2 * i - 1] = a[2 * i] = 2 * i - 1;
  a[2 * n - 1] = 2 * n - 1;
  for (int i = 0; i <= 2 * n - 1; ++i) f[i][0] = 1;
  for (int i = 1; i <= 2 * n - 1; ++i)
    for (int j = 1; j <= a[i]; ++j)
      f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * (a[i] - j + 1)) % 504;
  cout << f[2 * n - 1][k];
  return 0;
}
