#include <bits/stdc++.h>
using namespace std;
const i64 MOD = 1000000007;
i64 a[55];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> a[i];
  sort(a, a + n);
  i64 ans = 1;
  for (int i = 0; i < n; ++i) (ans *= a[i] - i) %= MOD;
  cout << ans;
  return 0;
}
