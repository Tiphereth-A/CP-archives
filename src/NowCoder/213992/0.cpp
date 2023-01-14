#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 105;
int d[MAXN][MAXN];
bool check(int a, int b, int c) {
  long long sum = 0;
  for (int i = 1; i <= b; i++) {
    sum += pow(a, i);
    if (sum > c) return false;
  }
  return true;
}
int main() {
  int n, m, q;
  cin >> n >> m;
  memset(d, 0x3f, sizeof(d));
  for (int i = 1; i <= n; i++) d[i][i] = 0;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    d[u][v] = d[v][u] = 1;
  }
  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  cin >> q;
  while (q--) {
    int s, t, b;
    cin >> s >> t >> b;
    int tmp = d[s][t];
    int l = 0, r = b;
    bool flag = false;
    while (r - l > 5) {
      int m = (l + r) >> 1;
      if (check(m, tmp, b)) l = m;
      else r = m - 1;
    }
    for (int i = r; i >= l; i--) {
      if (check(i, tmp, b)) {
        cout << i << endl;
        flag = true;
        break;
      }
    }
    if (!flag) cout << 0 << endl;
  }
  return 0;
}
