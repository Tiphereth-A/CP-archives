#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 2e4 + 5;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
i64 a[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  if (n == 1) {
    cout << a[1];
    return 0;
  }
  a[0] = a[n];
  i64 ans = 0, sum = 0;
  _for(i, 1, n) ans = max(ans, a[i] + a[i - 1]);
  _for(i, 1, n) sum += a[i];
  cout << max(ans, (sum + (n / 2) - 1) / (n / 2));
  return 0;
}
