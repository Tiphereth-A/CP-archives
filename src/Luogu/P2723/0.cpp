#include <bits/stdc++.h>
using namespace std;
int a[101], b[101];
int s[100001];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  s[0] = 1;
  for (int i = 1, minn; i <= m; ++i) {
    minn = INT_MAX;
    for (int j = 1; j <= n; ++j) {
      while (a[j] * s[b[j]] <= s[i - 1]) ++b[j];
      minn = min(minn, a[j] * s[b[j]]);
    }
    s[i] = minn;
  }
  cout << s[m];
}
