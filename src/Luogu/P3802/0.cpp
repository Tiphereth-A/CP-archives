#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
int a[8];
int main() {
  int sum = 0;
  _for(i, 1, 7) {
    cin >> a[i];
    sum += a[i];
  }
  double ans = 1;
  _for(i, 1, 6) ans *= 1.0 * i * a[i] / (sum + 1 - i);
  ans *= a[7] * 7.0;
  cout << fixed << setprecision(3) << ans;
  return 0;
}
