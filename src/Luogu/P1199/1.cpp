#include <bits/stdc++.h>
using namespace std;
const int N = 500 + 5;
int a[N][N];
bool choose[N];
int main() {
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 1; i < n; ++i)
    for (int j = i + 1; j <= n; ++j) {
      cin >> a[i][j];
      a[j][i] = a[i][j];
    }
  for (int i = 1; i <= n; ++i) {
    sort(a[i] + 1, a[i] + n + 1, greater<int>());
    if (a[i][2] > ans) ans = a[i][2];
  }
  cout << 1 << endl << ans;
  return 0;
}
