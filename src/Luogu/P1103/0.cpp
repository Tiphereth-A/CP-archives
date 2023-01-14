#include <bits/stdc++.h>
const int N = 1005;
struct book {
  int h, w;
  bool operator<(book &a) { return this->h < a.h; }
} b[N];
int n, k, ans = 0x3f3f3f3f;
int f[N][N];
int min(int a, int b) { return a < b ? a : b; }
int abs(int a) { return a < 0 ? -a : a; }
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) scanf("%d%d", &b[i].h, &b[i].w);
  std::sort(b + 1, b + n + 1);
  memset(f, 0x3f, sizeof(f));
  for (int i = 1; i <= n; ++i) f[i][1] = 0;
  k = n - k;
  for (int i = 2; i <= n; ++i)
    for (int j = 1; j < i; ++j)
      for (int l = 2, end = min(k, i); l <= end; ++l)
        f[i][l] = min(f[i][l], f[j][l - 1] + abs(b[i].w - b[j].w));
  for (int i = k; i <= n; ++i) ans = min(ans, f[i][k]);
  printf("%d", ans);
}
