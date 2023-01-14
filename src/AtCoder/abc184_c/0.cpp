#include <bits/stdc++.h>
using namespace std;
int main() {
#define _END(ans) \
  {               \
    cout << ans;  \
    return 0;     \
  }
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  if (a == c && b == d) _END(0);
  if (abs(a - c) + abs(b - d) <= 3 || a + b == c + d || a - b == c - d) _END(1);
  if ((a + b + c + d) % 2 == 0) _END(2);
  for (int i = -3, a1, b1; i <= 3; ++i)
    for (int j = -3; j <= 3; ++j) {
      if (i + j > 3) continue;
      a1 = a + i;
      b1 = b + j;
      if (abs(a1 - c) + abs(b1 - d) <= 3 || a1 + b1 == c + d ||
          a1 - b1 == c - d)
        _END(2);
    }
  _END(3);
}
