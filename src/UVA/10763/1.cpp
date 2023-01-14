#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  while (cin >> n) {
    if (n == 0) break;
    map<int, int> a;
    for (int i = 1; i <= n; ++i) {
      int x, y;
      cin >> x >> y;
      a[x]++;
      a[y]--;
    }
    bool f = 0;
    for (auto p : a) {
      if (p.second != 0) {
        cout << "NO" << '\n';
        f = 1;
        break;
      }
    }
    if (!f) cout << "YES" << '\n';
  }
  return 0;
}
