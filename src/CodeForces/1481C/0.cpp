#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (decltype(l + r) i = (r); i >= (l); --i)
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
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
const int OFFSET = 5;
const int N = 1e5 + OFFSET, M = 1e5 + OFFSET, K = 21;
int a[N], b[N], c[M], ans[N];
vector<int> cnt[M];
int vis[M];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n, m;
    cin >> n >> m;
    _for(i, 1, max(n, m)) cnt[i].clear();
    _set_nul_n(ans, max(n, m) + 1);
    _set_nul_n(vis, max(n, m) + 1);
    _for(i, 1, n) cin >> a[i];
    _for(i, 1, n) cin >> b[i];
    _for(i, 1, m) cin >> c[i];
    int tot = 0;
    _for(i, 1, n) vis[b[i]] = i;
    _for(i, 1, n)
      if (b[i] != a[i]) {
        tot += cnt[b[i]].empty();
        cnt[b[i]].push_back(i);
      }
    int pre = 0;
    _rfor(i, m, 1) {
      if (!cnt[c[i]].empty())
        _run_continue(pre = ans[i] = cnt[c[i]].back(); cnt[c[i]].pop_back();
                      tot -= cnt[c[i]].empty());
      if (pre) _run_continue(ans[i] = pre);
      if (!vis[c[i]]) _run_break(tot = INT_MAX);
      pre = ans[i] = vis[c[i]];
    }
    if (tot) _run_continue(cout << "NO\n");
    cout << "YES\n";
    _for(i, 1, m) cout << ans[i] << " \n"[i == m];
  }
}
