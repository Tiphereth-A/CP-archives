#include <bits/stdc++.h>
int a[7], f[1010], tot;
int main() {
  for (int i = 1; i <= 6; ++i) scanf("%d", a + i);
  for (int t1 = 0; t1 <= a[1]; ++t1)
    for (int t2 = 0; t2 <= a[2]; ++t2)
      for (int t3 = 0; t3 <= a[3]; ++t3)
        for (int t4 = 0; t4 <= a[4]; ++t4)
          for (int t5 = 0; t5 <= a[5]; ++t5)
            for (int t6 = 0; t6 <= a[6]; ++t6)
              f[t1 + t2 * 2 + t3 * 3 + t4 * 5 + t5 * 10 + t6 * 20]++;
  for (int i = 1; i <= 1000; i++)
    if (f[i]) tot++;
  printf("Total=%d", tot);
  return 0;
}
