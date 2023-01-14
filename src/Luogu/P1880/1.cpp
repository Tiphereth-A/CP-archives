#include <bits/stdc++.h>
int n, a[200 + 5], sum[200 + 5], f[200 + 5][200 + 5];
int max(int x, int y) {
  int m = (x - y) >> 31;
  return y & m | x & ~m;
}
int min(int x, int y) {
  int m = (x - y) >> 31;
  return x & m | y & ~m;
}
int get_ans(int func(int, int), int ans) {
  memset(f, 0, sizeof f);
  for (int delta = 1; delta < n; ++delta) {
    for (int l = 1, r = l + delta; r < 2 * n; ++l, ++r) {
      f[l][r] = ans;
      for (int k = l; k < r; ++k)
        f[l][r] = func(f[l][r], f[l][k] + f[k + 1][r] + sum[r] - sum[l - 1]);
    }
  }
  for (int i = 1; i <= n; (ans = func(ans, f[i][i + n - 1])), ++i);
  return ans;
}
int main() {
  std::cin >> n;
  for (int i = 1; i <= n; (a[i + n] = a[i]), ++i) std::cin >> a[i];
  for (int i = 1; i <= 2 * n; sum[i] = sum[i - 1] + a[i], ++i);
  std::cout << get_ans(min, 0x3f3f3f3f) << std::endl << get_ans(max, 0);
  return 0;
}
