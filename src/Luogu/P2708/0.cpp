#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
using namespace std;
int main() {
  string s;
  cin >> s;
  int len = s.size(), ans = s.size() - 1;
  _for(i, 1, len - 1)
    if (s[i] == s[i - 1]) ans--;
  if (s[len - 1] == '0') ans++;
  cout << ans;
  return 0;
}
