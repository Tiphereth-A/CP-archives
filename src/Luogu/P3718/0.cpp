#include <bits/stdc++.h>
const int N = 1e5 + 5;
int n, k, len[N], cnt;
bool light[N];
int max(int x, int y) {
  int m = (x - y) >> 31;
  return (y & m) | (x & ~m);
}
bool ok(int l) {
  int ans = 0;
  for (int i = 1; i <= cnt; ++i)
    if (len[i] > l) ans += len[i] / (l + 1);
  return ans <= k;
}
int main() {
  scanf("%d %d\n", &n, &k);
  char c = getchar();
  int l = 1, r, mid, tmp = 1;
  if (c == 'N') light[1] = 1;
  c = getchar();
  for (int i = 2; i <= n; ++i, c = getchar()) {
    if (c == 'N') light[i] = 1;
    if (light[i - 1] ^ light[i]) {
      r = max(r, len[++cnt] = tmp);
      tmp = 1;
    } else ++tmp;
  }
  r = max(r, len[++cnt] = tmp);
  while (l < r) {
    mid = (l + r) >> 1;
    if (mid == 1) {
      bool f = light[1];
      int ans = 0;
      for (int i = 2; i <= n; ++i, f = !f)
        if (f ^ light[i]) ++ans;
      if (ans <= k || n - ans <= k) {
        putchar('1');
        return 0;
      } else l = 2;
    } else if (ok(mid)) r = mid;
    else l = mid + 1;
  }
  printf("%d", l);
  return 0;
}
