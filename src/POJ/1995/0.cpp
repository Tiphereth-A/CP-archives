#include <cstdio>
long long qpow(long long a, long long b, int m) {
  long long res = 1;
  for (; b; b >>= 1, (a *= a) %= m)
    if (b & 1) (res *= a) %= m;
  return res;
}
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int m;
    scanf("%d", &m);
    int k;
    scanf("%d", &k);
    long long a, b, ans = 0;
    while (k--) {
      scanf("%lld%lld", &a, &b);
      (ans += qpow(a, b, m)) %= m;
    }
    printf("%d\n", ans);
  __end_kase:;
  }
  return 0;
}
