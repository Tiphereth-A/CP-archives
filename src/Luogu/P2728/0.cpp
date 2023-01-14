#include <bits/stdc++.h>
using namespace std;
int x[6][6], y[6][6];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<int> v(6), s(6);
  for (int i = 1; i <= 5; i++) {
    cin >> v[i] >> s[i];
    for (int j = 1; j <= s[i]; j++) cin >> x[i][j] >> y[i][j];
  }
  vector<int> a(361);
  for (int t = 0; t <= 360; t++) {
    a.clear();
    a.resize(361);
    for (int i = 1; i <= 5; i++) {
      for (int j = 1; j <= s[i]; j++) {
        for (int k = x[i][j]; k <= x[i][j] + y[i][j]; k++) ++a[k % 360];
        (x[i][j] += v[i]) %= 360;
      }
    }
    for (int i = 0; i <= 359; i++)
      if (a[i] == 5) {
        cout << t;
        return 0;
      }
  }
  cout << "none";
  return 0;
}
