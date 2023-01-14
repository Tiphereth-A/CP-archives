#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _rfor(i, r, l, vals...) \
  for (decltype(r - l) i = (r), ##vals; i >= (l); --i)
int a[10];
int main() {
  int n;
  cin >> n;
  n /= 8;
  int b = 2, cnt = 0;
  _for(i, 1, n, x) {
    cin >> x;
    _rfor(j, 8, 1) {
      a[j] = x % 2;
      x /= 2;
    }
    _for(j, 1, 8)
      if (b != a[j]) {
        if (b != 2) cout << cnt + 128 * b << ' ';
        b = a[j];
        cnt = 1;
      } else {
        ++cnt;
      }
  }
  cout << cnt + 128 * b << ' ';
  return 0;
}
