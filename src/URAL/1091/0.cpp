#include <cstdio>
const int pri[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
long long c[55][55];
int main() {
  for (int i = 0; i <= 50; ++i) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; ++j) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
  }
  int k, s;
  scanf("%d%d", &k, &s);
  long long ans = 0;
  for (int i = 0; i < sizeof(pri) / sizeof(pri[0]) && s >= pri[i]; ++i)
    ans += c[s / pri[i]][k];
  for (int i = 0; i < sizeof(pri) / sizeof(pri[0]) && s >= pri[i]; ++i)
    for (int j = i + 1;
         j < sizeof(pri) / sizeof(pri[0]) && s >= pri[i] * pri[j];
         ++j)
      ans -= c[s / (pri[i] * pri[j])][k];
  printf("%lld\n", ans > 10000 ? 10000 : ans);
}
