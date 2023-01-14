#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _all(a) (a).begin(), (a).end()
#define _run_continue(expressions) \
  {                                \
    expressions;                   \
    continue;                      \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  vector<pii> l;
  _for(i, 1, m, x) {
    cout << "? ";
    _for(j, 1, m) cout << "01"[j == i];
    cout << endl;
    cin >> x;
    l.emplace_back(x, i);
  }
  sort(_all(l));
  vector<bool> q(m + 1);
  i64 ans = 0;
  for (auto &&[v, k] : l) {
    q[k] = 1;
    cout << "? ";
    _for(j, 1, m) cout << "01"[q[j]];
    cout << endl;
    int _;
    cin >> _;
    if (_ != ans + v) _run_continue(q[k] = 0);
    ans += v;
  }
  cout << "! " << ans << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
