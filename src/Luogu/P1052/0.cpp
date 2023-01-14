#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int N = 100 + 5, M = 2e4 + 5;
int a[N], b[N];
int f[M];
bool vis[M];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  memset(f + 1, 0x3f, sizeof(f) - sizeof(f[0]));
  int l;
  cin >> l;
  int s, t, m;
  cin >> s >> t >> m;
  int u = s / __gcd(s, t) * t;
  _for(i, 1, m) cin >> a[i];
  sort(a + 1, a + m + 1);
  if (s == t) {
    int cnt = 0;
    _for(i, 1, m) cnt += a[i] % s == 0;
    cout << cnt;
    return 0;
  }
  _for(i, 1, m) b[i] = b[i - 1] + min(a[i] - a[i - 1], u);
  l = b[m] + u;
  _for(i, 1, m) vis[b[i]] = 1;
  _for(i, 1, l)
    _for(j, s, t) {
      if (i - j < 0) continue;
      f[i] = min(f[i], f[i - j] + vis[i]);
    }
  int ans = INT32_MAX;
  _for(i, 0, u) ans = min(ans, f[b[m] + i]);
  cout << ans;
  return 0;
}
