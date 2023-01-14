#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
i64 a[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    _for(i, 1, n) cin >> a[i];
    i64 ans = 0;
    _for(i, 1ll, n)
      for (i64 j = a[i] - i % a[i]; j <= n; j += a[i]) {
        if (j >= i) continue;
        ans += a[i] * a[j] == i + j;
      }
    cout << ans << '\n';
  }
  return 0;
}
