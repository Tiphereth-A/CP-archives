#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
int main() {
  i64 n, m, p;
  cin >> n >> n >> m >> p;
  i64 ans = 1;
  _for(i, 1, m) (ans *= n - m + 2 - i) %= p;
  cout << ans;
  return 0;
}
