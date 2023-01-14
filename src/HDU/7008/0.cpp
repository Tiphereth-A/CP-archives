#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t_ = 0;
  cin >> t_;
  while (t_--) {
    int n;
    cin >> n;
    int cnt = 0;
    for (int i = 1, x; i <= n; ++i) {
      cin >> x;
      if (x == i) ++cnt;
    }
    cout << (cnt < 50 ? "Second" : "First") << '\n';
  }
  return 0;
}
