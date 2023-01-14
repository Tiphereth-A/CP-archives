#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, x1, y1, x2, y2;
  cin >> n;
  vector<int> x(n), y(n), r(n);
  for (int i = 0; i < n; ++i) cin >> x[i];
  for (int i = 0; i < n; ++i) cin >> y[i];
  for (int i = 0; i < n; ++i) cin >> r[i];
  cin >> x1 >> y1 >> x2 >> y2;
  int ans = 0;
  for (int i = 0; i < n; ++i)
    ans += ((hypot(x1 - x[i], y1 - y[i]) < r[i]) ^
            ((hypot(x2 - x[i], y2 - y[i])) < r[i]));
  cout << ans;
  return 0;
}
