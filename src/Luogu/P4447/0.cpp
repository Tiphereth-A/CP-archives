#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
signed main() {
  int n;
  cin >> n;
  vector<int> f(n + 1), q(n + 1), sz(n + 1);
  for (int i = 1; i <= n; ++i) cin >> f[i];
  sort(f.begin() + 1, f.end());
  int top = 0;
  for (int i = 1; i <= n; ++i) {
    int pos = lower_bound(q.begin() + 1, q.begin() + top + 1, f[i]) - q.begin();
    while (q[pos + 1] == f[i] && pos < top) pos++;
    if (pos > top || q[pos] != f[i]) sz[++top] = 1, q[top] = f[i] + 1;
    else sz[pos]++, q[pos]++;
  }
  int ans = 1e9;
  for (int i = 1; i <= top; ++i) ans = min(ans, sz[i]);
  cout << ans << '\n';
  return 0;
}
