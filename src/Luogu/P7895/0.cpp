#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int OFFSET = 5;
const int N = 5e5 + OFFSET;
#define _dis(a, b) cout << "dis " << a << " " << b << endl
#define _del cout << "del" << endl
#define _ans(a)                \
  {                            \
    cout << "! " << a << endl; \
    return;                    \
  }
#define _read_and_exit \
  {                    \
    int __a;           \
    cin >> __a;        \
    _ans(__a);         \
  }
int d[N];
int is_chrysanthemun(int n) {
  int root = 0, maxd = 0;
  _for(i, 1, n)
    if (d[i] > maxd) maxd = d[root = i];
  _for(i, 1, n)
    if (i != root && d[i] > 2) return 0;
  return root;
}
void solve() {
  _for(__, 0, 99, n) {
    cin >> n;
    _for(i, 1, n) cin >> d[i];
    int cnt_leaves = 0;
    _for(i, 1, n) cnt_leaves += d[i] == 1;
    if (n == 1) _ans(0);
    if (n == 2) {
      _dis(1, 2);
      _read_and_exit;
    }
    if (n == 3) {
      _del;
      _ans(0);
    }
    if (n == 4) {
      _del;
      if (cnt_leaves == 3) _ans(0);
      int a = 0, b = 0;
      _for(i, 1, n)
        if (d[i] > 1) (a ? b : a) = i;
      _dis(a, b);
      _read_and_exit;
    }
    if (cnt_leaves == 2) {
      int a = 0, b = 0;
      _for(i, 1, n)
        if (d[i] == 1) (a ? b : a) = i;
      _dis(a, b);
      _read_and_exit;
    }
    if (int root = is_chrysanthemun(n); root && cnt_leaves <= (141 - __) * 2) {
      int a = 0, b = 0;
      int ans = 0;
      _for(i, 1, n, _)
        if (d[i] == 1) {
          if (a) {
            b = i;
            _dis(a, b);
            cin >> _;
            ans += _;
            a = b = 0;
            continue;
          }
          a = i;
        }
      if (a) {
        _dis(root, a);
        int _;
        cin >> _;
        ans += _;
      }
      _ans(ans);
    }
    _del;
  }
  while (1);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
