#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, ans = 0;
  cin >> n;
  for (int i = 1, t; i <= n; ++i) {
    double a;
    cin >> a >> t;
    for (int j = 1; j <= t; ++j) ans ^= int(j * a);
  }
  cout << ans;
  return 0;
}
