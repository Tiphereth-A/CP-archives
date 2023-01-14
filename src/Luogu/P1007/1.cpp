#include <bits/stdc++.h>
using namespace std;
int main() {
  int l, n, a, maxvalue = 0, minvalue = 0;
  cin >> l >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a;
    maxvalue = max(maxvalue, max(a, l + 1 - a));
    minvalue = max(minvalue, min(a, l + 1 - a));
  }
  cout << minvalue << ' ' << maxvalue;
  return 0;
}
