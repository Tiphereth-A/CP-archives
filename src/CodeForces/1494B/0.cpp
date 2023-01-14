#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n, u, r, d, l;
    cin >> n >> u >> r >> d >> l;
    bool flag = 0;
    _for(i, 0, 15) {
      int _u = u, _r = r, _d = d, _l = l;
      if (i & 1) {
        --_u;
        --_r;
      }
      if (i & 2) {
        --_u;
        --_l;
      }
      if (i & 4) {
        --_d;
        --_r;
      }
      if (i & 8) {
        --_d;
        --_l;
      }
      if (min(min(_u, _r), min(_d, _l)) >= 0 &&
          max(max(_u, _r), max(_d, _l)) <= n - 2) {
        flag = 1;
        break;
      }
    }
    cout << (flag ? "YES" : "NO") << '\n';
  }
  return 0;
}
