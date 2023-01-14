#include <bits/stdc++.h>
using namespace std;
int a[10005];
int main() {
  int n, q, kase = 0;
  while (cin >> n >> q, n && q) {
    cout << "CASE# " << ++kase << ":" << endl;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1, x, pos; i <= q; ++i) {
      cin >> x;
      if ((pos = lower_bound(a + 1, a + n + 1, x) - a), a[pos] != x)
        cout << x << " not found" << endl;
      else cout << x << " found at " << pos << endl;
    }
  }
}
