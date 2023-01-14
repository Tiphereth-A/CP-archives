#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _run_break(expressions) \
  {                             \
    expressions;                \
    break;                      \
  }
const int OFFSET = 5;
const int N = 100 + OFFSET, M = 2e5 + OFFSET, K = 21;
int h[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n, k;
    cin >> n >> k;
    _for(i, 1, n) cin >> h[i];
    int ans = 0;
    _for(i, 1, k) {
      int pos = 0;
      _for(j, 1, n - 1)
        if (h[j] < h[j + 1]) _run_break(pos = j);
      if (!pos) _run_break(ans = -1);
      ++h[ans = pos];
    }
    cout << ans << '\n';
  }
}
