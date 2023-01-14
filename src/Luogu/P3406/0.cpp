#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int N = 1e5 + 5;
int a[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m, x;
  cin >> n >> m >> x;
  _for(i, 2, m, y) {
    cin >> y;
    a[min(x, y)]++;
    a[max(x, y)]--;
    x = y;
  }
  i64 sum = 0, ans = 0;
  _for(i, 1, n, y, z) {
    cin >> x >> y >> z;
    sum += a[i];
    ans += min(sum * y + z, sum * x);
  }
  cout << ans;
  return 0;
}
