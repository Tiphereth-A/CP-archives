#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 1e5 + OFFSET;
int a[N], f[N];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  f[1] = a[1];
  int cnt = 1;
  for (int i = 2; i <= n; ++i)
    if (f[cnt] >= a[i]) f[++cnt] = a[i];
    else f[upper_bound(f + 1, f + cnt + 1, a[i], greater<int>()) - f] = a[i];
  cout << cnt;
  return 0;
}
