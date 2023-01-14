#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  int a[100010] = {0}, b[100010] = {0}, g[100010] = {0}, k[100010] = {0};
  for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> g[i] >> k[i];
  int x, y;
  cin >> x >> y;
  int i;
  for (i = n; i >= 1; i--) {
    if (a[i] <= x && a[i] + g[i] >= x && b[i] <= y && b[i] + k[i] >= y) break;
  }
  if (i != 0) cout << i;
  else cout << -1;
  return 0;
}
