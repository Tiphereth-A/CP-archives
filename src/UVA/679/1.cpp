#include <cstdio>
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int d, i;
    scanf("%d%d", &d, &i);
    int ans = 1;
    for (int j = 2; j <= d; ++j) {
      ans = (ans << 1) | (!(i & 1));
      i = (i + (i & 1)) >> 1;
    }
    printf("%d\n", ans);
  }
  scanf("%d", &kase);
  return 0;
}
