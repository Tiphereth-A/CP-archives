#include <bits/stdc++.h>
using namespace std;
int a[8005];
bool vis[8005];
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    memset(vis, 0, sizeof(vis));
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, _; i <= n; ++i) {
      _ = a[i];
      for (int j = i + 1; j <= n; ++j) {
        _ += a[j];
        if (_ > 8000) break;
        vis[_] = 1;
      }
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) cnt += vis[a[i]];
    cout << cnt << endl;
  }
  return 0;
}
