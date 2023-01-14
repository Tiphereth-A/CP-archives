#include <bits/stdc++.h>
#define N 505
#define _for(i, l, r) for (int(i) = (l); (i) <= (r); ++(i))
#define memax(a) memset((a), 63, sizeof(a))
int min(const int &a, const int &b) { return (a > b) ? b : a; }
int n, m, a[N], s[N], dis[N][N], f[N][N];
int main() {
  scanf("%d%d", &n, &m);
  _for(i, 2, n) {
    scanf("%d", a + i);
    s[i] = s[i - 1] + a[i];
  }
  _for(l, 1, n)
    _for(r, l, n) {
      int mid = (r + l) >> 1;
      int *tmp = &dis[l][r];
      int tmps = s[mid];
      _for(k, l, mid - 1) (*tmp) += tmps - s[k];
      _for(k, mid + 1, r) (*tmp) += s[k] - tmps;
    }
  memax(f);
  f[0][0] = 0;
  _for(i, 1, n)
    _for(j, 1, m) {
      if (j > i) {
        f[i][j] = 0;
        continue;
      }
      int *tmp = &f[i][j];
      _for(k, j - 1, i - 1) (*tmp) = min(*tmp, f[k][j - 1] + dis[k + 1][i]);
    }
  printf("%d\n", f[n][m]);
  return 0;
}
