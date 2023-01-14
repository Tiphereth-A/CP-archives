#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
void qread(int &xx) {
  xx = 0;
  int ch = getchar();
  while (ch < '0' || ch > '9') ch = getchar();
  while (ch >= '0' && ch <= '9') {
    xx = xx * 10 + ch - '0';
    ch = getchar();
  }
}
int n, m, a[N], b[N], ans;
void solve() {
  ans = 0;
  qread(n);
  qread(m);
  for (int i = 1; i <= n; i++) qread(a[i]);
  for (int i = 1; i <= m; i++) qread(b[i]);
  b[m + 1] = 0x3f3f3f3f;
  sort(a + 1, a + n + 1);
  sort(b + 1, b + m + 1);
  for (int i = 0, l, r; i <= m; i++)
    if (b[i] ^ b[i + 1]) {
      l = upper_bound(a + 1, a + n + 1, b[i]) - a;
      r = lower_bound(a + 1, a + n + 1, b[i + 1]) - a;
      ans = max(ans, r - l);
    }
  if (ans) printf("%d\n", ans);
  else printf("Impossible\n");
}
int main() {
  int _t;
  scanf("%d", &_t);
  while (_t--) solve();
  return 0;
}
