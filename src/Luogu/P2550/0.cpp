#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  int ans[8] = {0};
  multiset<int> a;
  for (int i = 0, _; i < 7; ++i) {
    cin >> _;
    a.insert(_);
  }
  for (int i = 1; i <= n; ++i) {
    int cnt = 0;
    for (int j = 0, _; j < 7; ++j) {
      cin >> _;
      cnt += a.count(_);
    }
    ++ans[cnt];
  }
  for (int i = 7; i; --i) cout << ans[i] << " ";
  return 0;
}
