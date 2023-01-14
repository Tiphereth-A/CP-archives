#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  string s;
  cin >> s;
  int ans = 0;
  for (int i = 0, j, k; i < s.size();) {
    j = i;
    k = i + 1;
    while (k < s.size() && s[j] <= s[k]) {
      j = (s[j] == s[k]) ? j + 1 : i;
      ++k;
    }
    while (i <= j) ans ^= (i += k - j);
  }
  cout << ans;
  return 0;
}
