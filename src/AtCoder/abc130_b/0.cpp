#include <bits/stdc++.h>
using namespace std;
int l[105];
int main() {
  int n, x;
  cin >> n >> x;
  for (int i = 1; i <= n; ++i) cin >> l[i];
  int d = 0, ans = 1;
  for (int i = 1; i <= n; ++i) {
    if ((d += l[i]) > x) break;
    ++ans;
  }
  cout << ans;
  return 0;
}
