#include <bits/stdc++.h>
const int M = 10001;
int x, x1, a[M], b[M], c, t = 1, i, j, s, f1, f2, n1, n2, f;
bool cmp(int a, int b) { return a > b; }
int main() {
  scanf("%d%d%d", &x, &a[0], &b[0]);
  while (a[t - 1] != -1) {
    scanf("%d%d", &a[t], &b[t]);
    t++;
  }
  t--;
  std::sort(a, a + t);
  std::sort(b, b + t, cmp);
  scanf("%d", &c);
  s = t;
  for (i = 1; i < t; i++)
    if (a[i] - a[i - 1] > 1)
      for (j = a[i - 1] + 1; j < a[i]; j++) {
        a[s] = j;
        b[s] =
          b[i - 1] - (b[i - 1] - b[i]) / (a[i] - a[i - 1]) * (j - a[i - 1]);
        s++;
      }
  std::sort(a, a + s);
  std::sort(b, b + s, cmp);
  for (i = 1; i < s; i++)
    if (a[i] == x) {
      x1 = b[i];
      f = 1;
    }
  if (f == 0) x1 = b[s - 1] - (x - a[s - 1]) * c;
  for (i = 0;; i++) {
    f1 = 0;
    f2 = 0;
    n1 = (x - a[0] + i) * x1;
    n2 = (x - a[0] - i) * x1;
    for (j = 1;; j++) {
      if (j >= s) {
        b[j] = b[j - 1] - c;
        a[j] = a[j - 1] + 1;
      }
      if (b[j] <= 0) break;
      if (n1 < (a[j] - a[0] + i) * b[j]) f1 = 1;
      if (n2 < (a[j] - a[0] - i) * b[j] || n2 <= 0) f2 = 1;
    }
    if (f1 == 0 && f2 == 1) break;
    else if (f1 == 1 && f2 == 0) break;
    else if (f1 == 0 && f2 == 0) break;
    else if (i == b[0] * 10) {
      f1 = -2;
      break;
    }
  }
  if (f1 == 1 && f2 == 0) printf("-%d", i);
  else if (f1 == 0 && f2 == 1) printf("%d", i);
  else if (f1 == 0 && f2 == 0) printf("%d", i);
  else if (f1 == -2) printf("NO SOLUTION");
  return 0;
}
