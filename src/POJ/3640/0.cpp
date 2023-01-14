#include <algorithm>
#include <cstdio>
#include <cstring>
const i64 MOD = 1e5 + 7;
i64 hash_n[MOD], pos[MOD], pop[MOD], a[6];
int hash(i64 num) {
  int _ = num % MOD;
  while (~hash_n[_] && hash_n[_] != num) _ = (_ + 1) % MOD;
  return _;
}
int main() {
  int n;
  while (scanf("%d", &n), n) {
    i64 ans = 0;
    memset(pop, 0, sizeof(pop));
    memset(hash_n, 0xff, sizeof(hash_n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 5; ++j) scanf("%lld", &a[j]);
      std::sort(a, a + 5);
      i64 _ = 0;
      for (int j = 0; j < 5; ++j) (_ *= 1000) += a[j];
      int ps = hash(_);
      hash_n[ps] = _;
      ans = std::max(ans, ++pop[pos[i] = ps]);
    }
    int cnt = 0;
    for (int j = 0; j < n; ++j)
      if (pop[pos[j]] == ans) ++cnt;
    printf("%d\n", cnt);
  }
  return 0;
}
