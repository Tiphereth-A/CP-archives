#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 1e3 + OFFSET, M = 2e5 + OFFSET, K = 21;
int h[N];
bool f1[N], f2[N];
void solve() {
  int n, m;
  cin >> n >> m;
  if (n >= m) {
    cout << "YES\n";
    return;
  }
  _for(i, 1, n) {
    cin >> h[i];
    h[i] %= m;
  }
  bool *now = f1, *next = f2;
  _for(i, 1, n) {
    _set_nul_n(now, m + 1);
    now[h[i]] = 1;
    _for(v, 1, m)
      if (next[v]) now[v] = now[(v + h[i]) % m] = 1;
    if (*now) {
      cout << "YES\n";
      return;
    }
    swap(now, next);
  }
  cout << "NO\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
