#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a[3];
  cin >> n >> a[0] >> a[1] >> a[2];
  int ans = 0;
  for (int i = 0; i * a[0] <= n; ++i)
    for (int j = 0; i * a[0] + j * a[1] <= n; ++j) {
      if ((n - (i * a[0] + j * a[1])) % a[2] == 0)
        ans = max(ans, i + j + (n - (i * a[0] + j * a[1])) / a[2]);
    }
  cout << ans << '\n';
  return 0;
}
