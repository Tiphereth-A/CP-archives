#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _rfor(i, r, l, vals...) \
  for (decltype(r - l) i = (r), ##vals; i >= (l); --i)
const int OFFSET = 5;
const int N = 5e5 + OFFSET;
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
i64 a[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    int n;
    cin >> n;
    _for(i, 1, n) cin >> a[i];
    i64 sum = 0;
    _for(i, 1, n) sum += a[i];
    i64 sum1 = 0, sum2 = 0;
    _for(i, 1, n) {
      sum1 += i * a[i];
      sum2 += (n - i + 1) * a[i];
    }
    i64 ans = INT64_MAX;
    _rfor(i, n, 1) chkmin(ans, sum1 += sum - n * a[i]);
    _for(i, 1, n) chkmin(ans, sum2 += sum - n * a[i]);
    cout << ans << '\n';
  }
  return 0;
}
