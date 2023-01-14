#include <bits/stdc++.h>
#define MAXN 100010
using namespace std;
int a[MAXN];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  int sum = 0, ans = 0;
  for (int i = 1; i <= n; i++) {
    sum += a[i];
    if (sum > m) {
      ans++;
      sum = a[i];
    } else if (sum == m) {
      ans++;
      sum = 0;
    }
  }
  if (sum) ans++;
  cout << ans;
  return 0;
}
