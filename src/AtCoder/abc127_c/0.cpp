#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 1e5 + OFFSET;
int d[N];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; ++i) {
    cin >> x >> y;
    ++d[x];
    --d[y + 1];
  }
  int now = 0, ans = 0;
  for (int i = 1; i <= n; ++i)
    if ((now += d[i]) == m) ++ans;
  cout << ans;
  return 0;
}
