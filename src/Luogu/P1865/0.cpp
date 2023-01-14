#include <bits/stdc++.h>
bool noprime[1000010] = {1, 1};
int p[1000010], f[1000010];
void get_prime(int m) {
  int cnt_prime = 0;
  for (int i = 2; i < m; i++) {
    if (!noprime[i]) p[cnt_prime++] = i;
    for (int j = 0; j < cnt_prime && i * p[j] < m; j++) {
      noprime[i * p[j]] = true;
      if (i % p[j] == 0) break;
    }
  }
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  get_prime(m + 1);
  for (int i = 1; i <= m; i++) f[i] = noprime[i] ? f[i - 1] : f[i - 1] + 1;
  for (int i = 1, l, r; i <= n; i++) {
    scanf("%d%d", &l, &r);
    if (l < 1 || r > m) {
      printf("Crossing the line\n");
      continue;
    }
    int ans = f[r] - f[l];
    if (!noprime[l]) ans++;
    printf("%d\n", ans);
  }
  return 0;
}
