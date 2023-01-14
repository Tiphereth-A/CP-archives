#include <cstdio>
int main() {
  int kase;
  scanf("%d", &kase);
  for (int cnt = 1; cnt <= kase; ++cnt) {
    i64 n;
    scanf("%lld", &n);
    i64 ans = 0;
    for (i64 l = 1, r = 0; l <= n; l = r + 1) {
      r = n / (n / l);
      ans += (r - l + 1) * (n / l);
    }
    printf("Case %d: %lld\n", cnt, ans);
  }
  return 0;
}
