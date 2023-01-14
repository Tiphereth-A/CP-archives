#include <bits/stdc++.h>
using namespace std;
int main() {
#define __(x, y)   \
  {                \
    _ = min(x, y); \
    x -= _;        \
    y -= _;        \
  }
  int kase;
  cin >> kase;
  while (kase--) {
    long long a[3], b[3];
    cin >> a[0] >> a[1] >> a[2] >> b[0] >> b[1] >> b[2];
    long long ans = 2 * min(a[2], b[1]);
    long long _;
    __(a[2], b[1]);
    __(a[2], b[2]);
    __(a[2], b[0]);
    __(a[1], b[1]);
    __(a[1], b[0]);
    __(a[0], b[2]);
    __(a[0], b[1]);
    __(a[0], b[0]);
    ans -= 2 * a[1];
    cout << ans << endl;
  }
  return 0;
}
