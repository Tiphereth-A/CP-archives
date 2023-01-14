#include <bits/stdc++.h>
using namespace std;
int main() {
  i64 ans = 0, _;
  while (cin >> _) ans += _;
  string s = to_string(ans);
  for (char ch : s) cout << (string(ch, '+') + ".>");
  return 0;
}
