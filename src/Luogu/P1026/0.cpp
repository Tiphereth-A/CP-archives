#include <bits/stdc++.h>
using namespace std;
const int mod = 100003;
int n, m, p, K, f[210][210], s[210][210];
bool vis[mod], v[210];
char a[210], d[10][210];
int hs(char *str) {
  int k = 0, ln = strlen(str + 1);
  for (int i = 1; i <= ln; i++) {
    k = k * 29 + str[i];
    if (k >= mod) k %= mod;
  }
  return k;
}
int main() {
  scanf("%d%d", &p, &K);
  for (int i = 1, c = 1; i <= p; i++) {
    scanf("%s", &a[c]);
    c += 20;
  }
  n = p * 20;
  scanf("%d", &m);
  for (int i = 1, h; i <= m; i++) {
    scanf("%s", &d[i][1]);
    h = hs(d[i]);
    if (vis[h]) {
      i--;
      m--;
    } else vis[h] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      memset(v, 0, sizeof v);
      for (int k = 1; k <= m; k++) {
        int ln = strlen(d[k] + 1);
        for (int l = i; l + ln - 1 <= j; l++) {
          if (v[l]) continue;
          bool flag = 0;
          for (int r = 1; r <= ln; r++) {
            if (a[l + r - 1] != d[k][r]) {
              flag = 1;
              break;
            }
          }
          if (!flag) s[i][j]++, v[l] = 1;
        }
      }
    }
  }
  for (int k = 1; k <= K; k++)
    for (int i = 1; i <= n; i++)
      for (int j = k - 1; j <= i - 1; j++)
        f[i][k] = max(f[i][k], f[j][k - 1] + s[j + 1][i]);
  printf("%d\n", f[n][K]);
  return 0;
}
