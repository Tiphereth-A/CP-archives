#include <cstdio>
int main() {
  int d, i, kase;
  scanf("%d", &kase);
  while (kase--) {
    scanf("%d%d", &d, &i);
    int ans = 1;
    for (int j = 2; j <= d; ++j) {
      ans <<= 1;
      if (!(i & 1)) ans |= 1;
      if (i & 1) i = (i + 1) >> 1;
      else i >>= 1;
    }
    printf("%d\n", ans);
  }
  scanf("%d", &kase);
  return 0;
}
