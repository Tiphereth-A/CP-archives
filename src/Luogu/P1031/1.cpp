#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a[110] = {0}, ave = 0, ans = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ave += a[i];
  }
  ave /= n;
  for (int i = 1; i <= n; i++) a[i] -= ave;
  for (int i = 1; i <= n; i++) {
    if (a[i] == 0) continue;
    a[i + 1] += a[i];
    ans++;
  }
  cout << ans;
  return 0;
}
