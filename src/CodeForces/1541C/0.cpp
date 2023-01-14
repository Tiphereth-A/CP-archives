#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
i64 d[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    _for(i, 1, n) cin >> d[i];
    sort(d + 1, d + n + 1);
    i64 ans = 0;
    _for(i, 2ll, n) ans -= ((n - i + 1) * (i - 1) - 1) * (d[i] - d[i - 1]);
    cout << ans << '\n';
  }
  return 0;
}
