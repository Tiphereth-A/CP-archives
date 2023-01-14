#include <bits/stdc++.h>
#define N 1000100
int a[N], b[N], c[N], n, m, len;
int max(int a, int b) { return a > b ? a : b; }
void up(int x) {
  while (c[x]) {
    c[x] = c[x - 1] = 0;
    c[x + 1]++;
    x += 2;
  }
}
void trans(int x) {
  if (c[x] < 2) return;
  int k = x - 2;
  if (x == 2) k = 1;
  c[x + 1]++;
  if (x != 1) c[k]++;
  c[x] -= 2;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
  len = max(n, m);
  for (int i = len; i >= 1; i--) {
    c[i] += a[i] + b[i];
    if (c[i] >= 2) {
      trans(i);
      trans(i + 1);
      if (i == 1) trans(1);
    }
    if (c[i]) up(i + 1);
    if (c[i + 1]) up(i + 2);
    if (c[i + 2]) up(i + 3);
  }
  while (c[len + 1]) len++;
  if (c[len + 2]) len += 2;
  while (c[len + 1]) len++;
  printf("%d", len);
  for (int i = 1; i <= len; i++) printf(" %d", c[i]);
}
