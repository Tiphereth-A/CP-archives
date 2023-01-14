#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 2e5 + OFFSET;
int a[N], b[N], ans[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  int cnt = 0;
  for (int i = n, sum; i; --i) {
    sum = 0;
    for (int j = 2 * i; j <= n; j += i) sum += b[j];
    if ((sum & 1) != a[i]) b[ans[++cnt] = i] = 1;
  }
  cout << cnt << endl;
  for (int i = 1; i <= cnt; ++i) cout << ans[i] << " \n"[i == cnt];
  return 0;
}
