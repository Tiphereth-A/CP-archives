#include <bits/stdc++.h>
void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}
int min(int a, int b) { return a < b ? a : b; }
int main() {
  int n, a[3], b[3];
  scanf("%d", &n);
  for (int i = 0; i < 3; ++i) scanf("%d", a + i);
  for (int i = 0; i < 3; ++i) scanf("%d", b + i);
  if (n < 5) {
    printf("%d\n", n * n * n);
    return 0;
  }
  int ans = 1;
  for (int i = 0; i < 3; ++i) {
    if (a[i] > b[i]) swap(a[i], b[i]);
    int k = min(b[i] - a[i], a[i] + n - b[i]);
    if (k < 5) ans *= (5 - k);
    else ans = 0;
  }
  printf("%d\n", 250 - ans);
  return 0;
}
