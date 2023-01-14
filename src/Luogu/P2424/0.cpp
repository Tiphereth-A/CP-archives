#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
i64 sum(i64 n) {
  i64 ans = 0;
  for (i64 l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans += (n / l) * (l + r) * (r - l + 1) / 2;
  }
  return ans;
}
int main() {
  i64 x, y;
  cin >> x >> y;
  cout << sum(y) - sum(x - 1);
  return 0;
}
