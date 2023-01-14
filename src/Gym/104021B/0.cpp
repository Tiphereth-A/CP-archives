#include <bits/stdc++.h>
using namespace std;
int n, m, posx, posy, a[1010][1010];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cin >> a[i][j];
      if (a[i][j] == -1) posx = i, posy = j;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (i == posx) continue;
    int mn = 0x3f3f3f3f;
    for (int j = 1; j <= n; ++j) { mn = min(mn, a[i][j]); }
    for (int j = 1; j <= n; ++j) a[i][j] -= mn;
  }
  for (int i = 1; i <= n; ++i) {
    if (i == posy) continue;
    int mn = 0x3f3f3f3f;
    for (int j = 1; j <= n; ++j) { mn = min(mn, a[j][i]); }
    for (int j = 1; j <= n; ++j) a[j][i] -= mn;
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (a[posx][i] != -1) {
      ans += a[posx][i];
      break;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (a[i][posy] != -1) {
      ans += a[i][posy];
      break;
    }
  }
  cout << ans << "\n";
  return 0;
}
