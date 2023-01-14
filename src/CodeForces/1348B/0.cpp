#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
const int N = 1e4 + 5;
int a[N], b[N];
bool vis[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n, len = 0, k;
    cin >> n >> k;
    _set_nul_n(vis, n + 1);
    _for(i, 1, n) {
      cin >> a[i];
      if (!vis[a[i]]) vis[b[++len] = a[i]] = 1;
    }
    if (len > k) {
      cout << "-1\n";
      continue;
    }
    _for(i, len + 1, k) b[i] = b[i - len];
    cout << n * k << '\n';
    _for(i, 1, n)
      _for(j, 1, k) cout << b[j] << " \n"[i == n && j == k];
  }
  return 0;
}
