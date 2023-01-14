#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  while ((cin >> n), n) {
    map<int, int> mp;
    for (int i = 1, x, y; i <= n; ++i) {
      cin >> x >> y;
      ++mp[x];
      --mp[y];
    }
    for (auto const &p : mp) {
      if (p.second) {
        cout << "NO\n";
        goto l1;
      }
    }
    cout << "YES\n";
  l1:;
  }
  return 0;
}
