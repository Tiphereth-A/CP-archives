#include <cstdio>
int main() {
  i64 n, k;
  while (~scanf("%lld%lld", &n, &k) && (n || k)) {
    i64 ans = 1;
    n - k < k ? k = n - k : 0;
    for (i64 i = 1; i <= k; ++i) (ans *= n - i + 1) /= i;
    printf("%lld\n", ans);
  }
}
