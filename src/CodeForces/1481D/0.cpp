#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _run_break(expressions) \
  {                             \
    expressions;                \
    break;                      \
  }
#define _run_continue(expressions) \
  {                                \
    expressions;                   \
    continue;                      \
  }
const int OFFSET = 5;
const int N = 1e3 + OFFSET, M = 2e5 + OFFSET, K = 21;
char maps[N][N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n, m;
    cin >> n >> m;
    _for(i, 1, n)
      _for(j, 1, n) cin >> maps[i][j];
    if (m % 2 == 1)
      _run_continue(cout << "YES\n"; _for(i, 1, m + 1) cout
                                     << (i % 2 ? '1' : '2')
                                     << " \n"[i == m + 1];);
    int x = 0, y = 0, z = 0;
    _for(i, 1, n) {
      bool b = 0;
      _for(j, i + 1, n)
        if (maps[i][j] == maps[j][i]) _run_break(b = 1; x = i; y = j);
      if (b == 1) break;
    }
    if (x && y)
      _run_continue(cout << "YES\n"; _for(i, 1, m + 1) cout
                                     << (i % 2 ? x : y) << " \n"[i == m + 1];);
    if (n == 2) _run_continue(cout << "NO\n");
    _for(i, 1, n) {
      bool b = 0;
      _for(k, i + 1, n) {
        bool _b = 0;
        _for(j, 1, n) {
          if (j == i || j == k) continue;
          if (maps[i][j] == maps[j][k])
            _run_break(b = _b = 1; x = i; y = j; z = k);
        }
        if (_b == 1) break;
      }
      if (b == 1) break;
    }
    cout << "YES\n";
    if (m % 4 == 0)
      _run_continue(_for(i, 1, (m - 1) / 2) cout << (i % 2 ? y : x) << ' ';
                    cout << x << ' ' << y << ' ' << z << ' ';
                    _for(i, 1, (m - 1) / 2) cout << (i % 2 ? y : z)
                                                 << " \n"[i == (m - 1) / 2];);
    _for(i, 1, m + 1)
      cout << (i % 4 == 1 ? x : (i % 2 == 0 ? y : z)) << " \n"[i == m + 1];
  }
}
