#include <cstdio>
int a[20005];
int main() {
  int b;
  while (~scanf("%d", &b))
    for (int t = 1, s; t <= b; ++t) {
      scanf("%d", &s);
      for (int i = 1; i < s; ++i) scanf("%d", &a[i]);
      int max = -1, sum = 0;
      int s1 = 1, e1 = 1, s2 = 1;
      for (int i = 1; i < s; ++i) {
        if (sum < 0) {
          sum = 0;
          s2 = i;
        }
        sum += a[i];
        if (max == sum && i - s2 > e1 - s1 || max < sum) {
          max = sum;
          s1 = s2;
          e1 = i;
        }
      }
      if (~max)
        printf("The nicest part of route %d is between stops %d and %d\n",
               t,
               s1,
               e1 + 1);
      else printf("Route %d has no nice parts\n", t);
    }
  return 0;
}
