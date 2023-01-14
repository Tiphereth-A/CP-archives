#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _all(a) (a).begin(), (a).end()
#define _set_nul_n(a, n) memset(a, 0, sizeof(*(a)) * (n))
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
int a[N], cnt[N];
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  _set_nul_n(cnt, n + 1);
  vector<int> b;
  b.reserve(n);
  _for(i, 1, n) b.push_back(a[i]);
  sort(_all(b));
  b.erase(unique(_all(b)), b.end());
  _for(i, 1, n) a[i] = lower_bound(_all(b), a[i]) - b.begin() + 1;
  _for(i, 1, n)
    if (cnt[a[i]] < 2) ++cnt[a[i]];
  int ans = 0;
  _for(i, 1, n) ans += cnt[i];
  cout << (ans + 1) / 2 << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
