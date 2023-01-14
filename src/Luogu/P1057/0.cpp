#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
using namespace std;
int f[35][35];
int main() {
  ios::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  f[1][0] = 1;
  _for(i, 1, m) {
    f[1][i] = f[2][i - 1] + f[n][i - 1];
    _for(j, 2, n - 1) f[j][i] = f[j - 1][i - 1] + f[j + 1][i - 1];
    f[n][i] = f[n - 1][i - 1] + f[1][i - 1];
  }
  cout << f[1][m];
  return 0;
}
