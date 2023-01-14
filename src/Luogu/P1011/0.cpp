#include <bits/stdc++.h>
int aa[25] = {0, 1, 1, 2}, bb[25] = {0, 0, 0, 0};
int main() {
  int a, n, m, x;
  scanf("%d%d%d%d", &a, &n, &m, &x);
  for (int i = 4; i < n; ++i) {
    aa[i] = aa[i - 2] + aa[i - 1] - 1;
    bb[i] = bb[i - 2] + bb[i - 1] + 1;
  }
  int b = (m - a * aa[n - 1]) / bb[n - 1];
  printf("%d", a * aa[x] + b * bb[x]);
  return 0;
}
