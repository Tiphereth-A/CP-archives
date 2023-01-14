#include <bits/stdc++.h>
using namespace std;
int a[3010];
int ans, sum;
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    ans = i <= m ? sum += a[i] : min(ans, sum += a[i] - a[i - m]);
  }
  cout << ans;
  return 0;
}
