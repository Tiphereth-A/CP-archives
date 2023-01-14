#include <bits/stdc++.h>
const int N = 200 + 5;
int n, a[N], sum[N], f[N][N];
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }
int get_ans(int func(int, int), int ans) {
  memset(f, 0, sizeof f);
  for (int delta = 1; delta < n; ++delta) {
    for (int l = 1, r = l + delta; r < 2 * n; ++l, ++r) {
      f[l][r] = ans;
      for (int k = l; k < r; ++k)
        f[l][r] = func(f[l][r], f[l][k] + f[k + 1][r] + sum[r] - sum[l - 1]);
    }
  }
  for (int i = 1; i <= n; ++i) ans = func(ans, f[i][i + n - 1]);
  return ans;
}
int main() {
  std::cin >> n;
  for (int i = 1; i <= n; (std::cin >> a[i]), (a[i + n] = a[i]), ++i);
  for (int i = 1; i <= 2 * n; sum[i] = sum[i - 1] + a[i], ++i);
  std::cout << get_ans(min, 0x3f3f3f3f) << std::endl << get_ans(max, 0);
  return 0;
}
