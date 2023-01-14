#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1000005;
int a[N], q1[N], q2[N], n, m;
int main() {
  scanf("%d%d", &n, &m);
  _for(i, 1, n) scanf("%d", a + i);
  int h = 1, t = 0;
  for (int i = 1; i <= n; i++) {
    while (h <= t && q1[h] + m <= i) ++h;
    while (h <= t && a[i] < a[q1[t]]) --t;
    q1[++t] = i;
    if (i >= m) printf("%d ", a[q1[h]]);
  }
  putchar('\n');
  h = 1, t = 0;
  for (int i = 1; i <= n; i++) {
    while (h <= t && q2[h] + m <= i) ++h;
    while (h <= t && a[i] > a[q2[t]]) --t;
    q2[++t] = i;
    if (i >= m) printf("%d ", a[q2[h]]);
  }
  return 0;
}
