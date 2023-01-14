#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int N = 1005;
int t[N][N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  _for(k, 1, m, x1, x2, y1, y2) {
    cin >> x1 >> y1 >> x2 >> y2;
    _for(i, x1, x2)
      _for(j, y1, y2) ++t[i][j];
  }
  _for(i, 1, n)
    _for(j, 1, n) cout << t[i][j] << " \n"[j == n];
}
