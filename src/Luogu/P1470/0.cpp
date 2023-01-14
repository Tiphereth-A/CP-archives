#include <bits/stdc++.h>
using namespace std;
int dp[200005], m;
set<string> s[20];
int main() {
  string _;
  while (cin >> _) {
    if (_ == ".") break;
    s[_.size()].insert(_);
    m = max(m, int(_.size()));
  }
  int i, ans = 0;
  dp[0] = 1;
  string n;
  n = " ";
  while (cin >> _) n += _;
  for (i = 1; i < n.size(); i++) {
    for (int j = min(i, m); j >= 1; j--) {
      string tt = n.substr(i - j + 1, j);
      if (s[tt.size()].count(tt) == 1 && dp[i - j] == 1) {
        dp[ans = i] = 1;
        break;
      }
    }
  }
  cout << ans;
}
