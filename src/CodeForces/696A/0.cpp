#include <bits/stdc++.h>
using namespace std;
map<i64, i64> m;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  i64 op, u, v, w;
  while (kase--) {
    cin >> op >> u >> v;
    if (op == 1) {
      cin >> w;
      while (u != v) {
        if (u > v) u ^= v ^= u ^= v;
        m[v] += w;
        v /= 2;
      }
    } else {
      i64 ans = 0;
      while (u != v) {
        if (u > v) u ^= v ^= u ^= v;
        ans += m[v];
        v /= 2;
      }
      cout << ans << endl;
    }
  }
  return 0;
}
