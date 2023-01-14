#include <bits/stdc++.h>
const int N = 1005;
int b[N];
int n, k, ans = 0x3f3f3f3f;
int f[N][N];
int min(int a, int b) { return a < b ? a : b; }
short abs(short a) { return a < 0 ? -a : a; }
int main() {
  scanf("%d%d", &n, &k);
  int tmp1, tmp2;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &tmp1, &tmp2);
    b[i] = (tmp1 << 16) ^ tmp2;
  }
  std::sort(b + 1, b + n + 1);
  memset(f, 0x3f, sizeof(f));
  for (int i = 1; i <= n; ++i) f[i][1] = 0;
  k = n - k;
  for (int i = 2; i <= n; ++i)
    for (int j = 1; j < i; ++j)
      for (int l = 2, end = min(k, i); l <= end; ++l)
        f[i][l] = min(f[i][l], f[j][l - 1] + abs(short(b[i]) - short(b[j])));
  for (int i = k; i <= n; ++i) ans = min(ans, f[i][k]);
  printf("%d", ans);
}
