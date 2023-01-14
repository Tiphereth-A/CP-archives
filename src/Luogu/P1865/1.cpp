#include <bits/stdc++.h>
#define MAXN 1000010
using namespace std;
bool noprime[MAXN];
int p[MAXN], f[MAXN];
void get_prime(int m) {
  int pnum = 0;
  for (int i = 2; i < m; i++) {
    if (!noprime[i]) p[pnum++] = i;
    for (int j = 0; j < pnum && i * p[j] < m; j++) {
      noprime[i * p[j]] = true;
      if (i % p[j] == 0) break;
    }
  }
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  get_prime(m + 1);
  noprime[1] = 1;
  for (int i = 1; i <= m; i++)
    (!noprime[i]) ? (f[i] = f[i - 1] + 1) : (f[i] = f[i - 1]);
  for (int i = 1; i <= n; i++) {
    int l, r;
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
