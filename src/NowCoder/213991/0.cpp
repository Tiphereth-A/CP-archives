#include <bits/stdc++.h>
using namespace std;
const int M = 22505, N = 155;
int sg[N][N];
int f(int m, int n) {
  if (~sg[m][n]) return sg[m][n];
  bool vis[M];
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= m - i; ++i) {
    if ((i == 1 && n == 1) || (m - i == 1 && n == 1)) continue;
    vis[f(i, n) ^ f(m - i, n)] = 1;
  }
  for (int i = 1; i <= n - i; ++i) {
    if ((i == 1 && m == 1) || (n - i == 1 && m == 1)) continue;
    vis[f(m, i) ^ f(m, n - i)] = 1;
  }
  for (int i = 0; i < M; ++i)
    if (!vis[i]) return sg[m][n] = i;
}
int main() {
  int m, n;
  memset(sg, 0xff, sizeof(sg));
  sg[1][1] = sg[1][2] = sg[2][1] = sg[1][3] = sg[3][1] = 0;
  while (cin >> m >> n) cout << (f(m, n) ? "Alice" : "Bob") << endl;
  return 0;
}
