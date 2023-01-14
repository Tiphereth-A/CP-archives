#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
char b[128];
int main() {
  int n;
  string s;
  cin >> n >> s;
  _for(i, '1', '9') cin >> b[i];
  for (auto it1 = s.begin(); it1 != s.end(); ++it1)
    if (*it1 < b[*it1]) {
      for (auto it = it1; it != s.end() && *it <= b[*it]; ++it) *it = b[*it];
      break;
    }
  cout << s;
  return 0;
}
